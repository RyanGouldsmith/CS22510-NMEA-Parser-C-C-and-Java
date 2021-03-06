#include <iostream>
#include "GPSParser.h"
#include <string.h>
#include <vector>
#include "GGA.h"
#include "Model.h"
#include "GSV.h"
/*!
 * \file GPsParser.cpp
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This parses the individual sentences creating appropriate objects based on the sentence type. It also updates the offset
 */
using namespace std;
/**
* The GPSParser constructor splits the sentence into tokens, and checks the sentence type for GPGGA and GPGSV
* @param line is the string in which has just been parsed.
*/
GPSParser::GPSParser(string line)
{
    char *tokens;
    char *delimeter = ",";
    char *line_char = new char[line.size() + 1];
    strcpy(line_char, line.c_str());
    //split into tokens on the delimeter
    tokens = strtok(line_char, delimeter);
    vector<char*> sentence;
    //add the tokens to a sentence vector
    while (tokens != NULL)
    {
        sentence.push_back(tokens);
        tokens = strtok(NULL, delimeter);
    }
    //check to see if the sentence is a GPGGA sentence
    if (strcmp(sentence.front(), "$GPGGA") == 0)
    {
        //create a new GGA sentence object
        gga = new GGA(sentence);
        //check fro GPSGSV sentence
    }
    else if (strcmp(sentence.front(), "$GPGSV") == 0)
    {
        GSV* gsv = new GSV(sentence);
    }
    delete(line_char);
}
/**
* The destuctor for the GPSParser object
*/
GPSParser::~GPSParser()
{
}
/**
* sets the time for the current instance of GPSParser
* @param time is the current time
*/
void GPSParser::set_time(float time)
{
    this->time = time;
}
/**
* sets the lat for the current instance of GPSParser
* @param lat is the current lat
*/
void GPSParser::set_lat(float lat)
{
    this->lat = lat;
}
/**
* sets the lng for the current instance of GPSParser
* @param lng is the current lng
*/
void GPSParser::set_lng(float lng)
{
    this->lng = lng;
}
/**
* sets the lat offset value for the current instance of GPSParser
* @param offset is the current offset calculation
*/
void GPSParser::set_lat_offset(float offset)
{
    this->lat_offset = offset;
}
/**
* sets the longitude offset value for the current instance of GPSParser
* @param offset is the current offset calculation
*/
void GPSParser::set_lng_offset(float offset)
{
    this->lng_offset = offset;
}
float GPSParser::get_time()
{
    return this->time;
}
/**
* @returns the current value of the latitude
*/
float GPSParser::get_lat()
{
    return this->lat;
}
/**
* @returns the current value of longitude
*/
float GPSParser::get_lng()
{
    return this->lng;
}
/**
* @returns the current value of the lat offset
*/
float GPSParser::get_lat_offset()
{
    return this->lat_offset;
}
/**
* @returns the current value of longitude offset
*/
float GPSParser::get_lng_offset()
{
    return this->lng_offset;
}
/**
* @returns a pointer to a GGA object from fileOne
*/
GGA* GPSParser::get_current_GGA()
{
    return GPSParser::gga;
}
/**
* @returns a poitner to the GGA object from fileTwo
*/
GGA* GPSParser::get_current_GGA_two()
{
    return GPSParser::gga_two;
}
/**
* This sets the current instance of the second GGA object
* @param is a GGA object from fileTwo
*/
void GPSParser::set_current_GGA_two(GGA two)
{
    this->GPSParser::gga_two = &two;
}
/**
* This works out the offset for each lat and long values, based on the
*TOODO
*/
void GPSParser::work_out_offset(GGA* one, GGA* two, Model *model)
{
    //Model* model = new Model();
    //checks the offset
    if(one->get_lat() < two->get_lat())
    {
        model->set_lat_offset(two->get_lat() - one->get_lat());
    }
    else if (two->get_lat() < one->get_lat())
    {
        model->set_lat_offset(one->get_lat() - two->get_lat());
    }
    if (one->get_lng() < two->get_lng())
    {
        model->set_lng_offset(two->get_lng() - one->get_lng());
    }
    else if (two->get_lng() < one->get_lng())
    {
        model->set_lng_offset(one->get_lng() - two->get_lng());
    }
}
