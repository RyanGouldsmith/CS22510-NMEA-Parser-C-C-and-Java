#include <iostream>
#include "InputReader.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include "regex.h"
#include "GGA.h"
#include "GPSParser.h"
#include "GSV.h"
#include <stdlib.h>
#include "Model.h"
#include "Markup.h"
#include "Exporter.h"
/*!
 * \file Exporter.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This reads in the information from both the, and passes it the the parser. It checks the times are right and finally outputs the result.
 */
using namespace std;
//CONSTRUCTORS DESTRUCTORS
/**
* The implementation of the InputReader Constructor. It sets the files names to be the attributes in the InputReader class
* Calls read_file_one and the application begins.
* @param file_one is the first file entered
* @param file_two is the second file entered.
*/
InputReader::InputReader(string file_one, string file_two)
{
    this->file_one = file_one;
    this->file_two = file_two;
    std::cout << "Reading in files .... " << this->file_one << this->file_two << endl;
    read_file_one("gps_1.dat");
}
/**
* The destructor for the InputReader
*/
InputReader::~InputReader()
{
}
/**
* This reads in file one, finds a GGA or GSV sentences it and parses the data.
* It checks to see if there is a file, if there is then it will update the current offset and export to the filewriter
* It then checks to see if there isn't a fix, to which is ammends to the lat and long based on the offset value
* It then loops over the second file
* Finally, the function checks for GSV and puts the sentence ready for parsing the data
* @param name is the name of the first file.
*/
void InputReader::read_file_one(string name)
{
    //REFERENCE : http://www.cplusplus.com/forum/general/4422/
    char *a=new char[name.size()+1];
    //create a new Model
    Model* model = new Model();
    //create a new fileExport
    Exporter* export_file = new Exporter();
    a[name.size()]=0;
    //copy the string to a temp char* array
    memcpy(a,name.c_str(),name.size());
    // creates a stream
    ifstream reader(a);

    string line;
    //loops over the file
    while(getline(reader, line))
    {
        //npos is the rreturn value ?
        if (line.find("$GPGGA") != std::string::npos)
        {
            //read_second_file
            GPSParser* parser_one = new GPSParser(line);
            //check to see if the return of read_second file is true
            if (read_second_file(parser_one->get_current_GGA()))
            {
                //check to see if the current fix is true
                if (this->InputReader::fix)
                {
                    //update the from the current GGA and the other GGA from the second file
                    parser_one->work_out_offset(parser_one->get_current_GGA(), this->get_parser_two()->get_current_GGA(), model);
                    //set Lat values to the Vector
                    model->set_lat_values(parser_one->get_current_GGA()->get_lat());
                    //Set Lng values to the Vector
                    model->set_lng_values(parser_one->get_current_GGA()->get_lng());
                    //check to see if there isn't a fix
                }
                else if (!this->InputReader::fix)
                {
                    float lat,lng;
                    //Update the offset
                    parser_one->work_out_offset(parser_one->get_current_GGA(), this->get_parser_two()->get_current_GGA(), model);
                    //store the lat offset temporarily
                    lat = parser_one->get_lat_offset();
                    //store the lng offset temporarily
                    lng = parser_one->get_lng_offset();
                    //reset the new lat and long values, after minusing the offset.
                    this->get_parser_two()->get_current_GGA()->set_lng(this->get_parser_two()->get_current_GGA()->get_lng()- lng);
                    this->get_parser_two()->get_current_GGA()->set_lat(this->get_parser_two()->get_current_GGA()->get_lat()- lat);
                    //set the model
                    model->set_lat_values(this->get_parser_two()->get_current_GGA()->get_lat());
                    model->set_lng_values(this->get_parser_two()->get_current_GGA()->get_lng());
                }
            }

            //delete the memory for parser one
            delete(parser_one);
            //check to see if the line is a GSV
        }
        else if (line.find("$GPGSV") != std::string::npos)
        {
            //create a temp char* vector.
            vector<char*> array_gsv;
            string temp;
            int i;
            //shallow copy the line to the temp
            temp = line;
            //loop over the number of sentences labeled in the GSV sentence
            for (i = 0; i < atoi(line.substr(7,7).c_str()); i++)
            {
                if(line.find("$GPGSV")!= std::string::npos)
                {
                    char *line_v = new char[temp.size() + 1];
                    //copy the vale over
                    strcpy(line_v, temp.c_str());
                    //add to the temp vector
                    array_gsv.push_back(line_v);
                }
                //loop over the other lines
                getline(reader, temp);
            }
            GSV* gsv = new GSV(array_gsv);
            //update the fix based one the SNR values
            this->InputReader::fix = gsv->isFixGood();
        }
    }
    //export to file
    export_file->write_to_xml(model);
    //delete the pointer a
    delete (a);
}
/**
* This reads the second file, it looks to find the next sentences that's a GGA and match them up via the time.
* It then checks to see the GSV sentence and see how many sentences it has. It then checks the fix and updates it.
* @param gga is the GGA object in the first function, used to compare the times.
* @return a bool on whether it's found the resultant or not
*/
bool  InputReader::read_second_file(GGA* gga)
{
    //creates a new reader
    ifstream reader("gps_2.dat");
    string line_2;
    bool is_found = false;
    //reads in a single line at a time
    while(getline(reader, line_2))
    {
        //checks to see if the line beginds with GPGGA
        if (line_2.find("$GPGGA") != std::string::npos)
        {
            //create a new parser
            GPSParser* parser_two = new GPSParser(line_2);
            //set the parser
            this->InputReader::set_parser_two(*parser_two);
            //check the time values, and return true from the method if they match
            if(gga->get_time() == parser_two->get_current_GGA()->get_time())
            {
                return true;
            }
            //check the lines beginning with GPGSV
        }
        else if (line_2.find("$GPGSV") != std::string::npos)
        {
            vector<char*> array_gsv;
            string temp;
            int i;
            temp = line_2;
            //loops over the number of GSV sentences
            for (i = 0; i < atoi(line_2.substr(7,7).c_str()); i++)
            {
                if(line_2.find("$GPGSV")!= std::string::npos)
                {
                    char *line_v = new char[temp.size() + 1];
                    //copies them over
                    strcpy(line_v, temp.c_str());
                    //adds to the vector
                    array_gsv.push_back(line_v);
                }
                //reads in the remaining lines
                getline(reader, temp);
            }
            GSV* gsv = new GSV(array_gsv);
            //update the fix
            this->InputReader::fix = gsv->isFixGood();
        }
    }
    return is_found;
}
/**
* sets the parser one instance
* @param one is the parser one
*/
void InputReader::set_parser_one(GPSParser one)
{
    this->InputReader::parser_one = &one;
}
/**
* Sets the parser two instance
* @param two is the parser two which is to be set
*/
void InputReader::set_parser_two(GPSParser two)
{
    this->InputReader::parser_two = &two;
}
/**
* @returns the pointer  to the parser one
*/
GPSParser* InputReader::get_parser_one()
{
    return this->InputReader::parser_one;
}
/**
*@returns the pointer to parser two
*/
GPSParser* InputReader::get_parser_two()
{
    return this->InputReader::parser_two;
}


