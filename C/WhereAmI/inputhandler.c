#include <stdio.h>
#include <stdlib.h>
#include "InputHandler.h"
#include "Parser.h"
#include "model.h"
#include <string.h>
/*!
 * \file inputhandler.c
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * Reads in the file one line by line, checks against the file two for a match. parses the appropriate sentences and applies any offset values
 * It then outputs the values to the file via pointers.
 */

/**
*this is the function definition for the write_to_file since it doesn't have a header
*@param the Parser ponter containing the lat and long values
*/
void write_to_file(Parser*);
//pointer
GGA* snd_ptr = NULL;
/**
* The reads in the first file.
* It checks for the the sentence lines GPGSV and GPGGA and creates new pointers for them
* It then worksout the fix and works out the offset values
* @param is the filename which will be loaded
*/
void read_file_one(char *filename)
{
    //create a new Parser pointer
    Parser *parser = malloc(sizeof(Parser));
    //creates a new model pointer
    model *model = malloc(sizeof(model));
    FILE *fp;
    int position =0;
    //opens the file ready for reading
    fp = fopen("gps_1.dat", "r");
    char line[200];
    if (fp != NULL)
    {
        //reads in a line up to 200 characters
        while (fgets(line, 200,  fp) != NULL)
        {
            //creates a temp value to copy over the read in line
            char *temp = (char*) malloc(sizeof(char) * strlen(line));
            //copies over the line
            strcpy(temp, line);
            char *value;
            //splits it into tokens
            value = strtok(temp, ",");
            while (value != NULL)
            {
                //checks to see if the value is equal to the GPGGA sentence
                if (strcmp(value, "$GPGGA") == 0)
                {
                    GGA *gga_ptr = (GGA*) malloc(sizeof(GGA));
                    //parse the sentence data
                    gga_ptr = create_GGA_sentence(line);
                    //check that the read file returns true
                    if(read_file_two(gga_ptr, model) == 0)
                    {
                        //checks to see if there's a fix
                        if(model->fix == 0)
                        {
                            //work out an offset
                            model = work_out_offset(gga_ptr, get_ptr(), model);
                            //add values to the lat array
                            parser->lat_arr[position] = gga_ptr->lat;
                            //add values to the lng array
                            parser->lng_arr[position] = gga_ptr->lng;
                            position++;
                        }
                        //checks to see if there isn't a fix
                        else if (model->fix == 1)
                        {
                            //works out an offset
                            model = work_out_offset(gga_ptr, get_ptr(), model);
                            float new_lat = get_ptr()->lat;
                            //updates the new latitude by old lat - new lat
                            get_ptr()->lat -= new_lat;
                            float new_lng = get_ptr()->lng;
                            //updates the new long by old lng - new lng
                            get_ptr()->lng -= new_lng;
                            //store the lat and lng values in the array
                            parser->lat_arr[position] = get_ptr()->lat;
                            parser->lng_arr[position] = get_ptr()->lng;
                            position++;
                        }
                    }
                }
                //checks to see if it's a GSGSV sentence
                else if (strcmp(value, "$GPGSV") == 0)
                {
                    unsigned int i =0;
                    char* array_value[1000];
                    //create temporary char arrays the same size as the line read in
                    char* sub = (char*) malloc(sizeof(char) * strlen(line));
                    char* value = (char*) malloc(sizeof(char) * strlen(line));
                    char* sub_par = (char*) malloc(sizeof(char) * strlen(line));
                    strcpy(value, line);

                    //REFERENCE http://www.linuxquestions.org/questions/programming-9/extract-substring-from-string-in-c-432620/
                    //splits the sentence to work out the number of GSV sentences there are
                    strncpy(sub,value+7, 1);
                    //splites to get the first part of the sentence
                    strncpy(sub_par, value,6);
                    //loop over the number of sentences
                    for (i = 0; i < atoi(sub); i++)
                    {
                        //checks to see if the first 6 characters are a GSV sentence.
                        if(strcmp(sub_par, "$GPGSV") == 0)
                        {
                            //create a temp value
                            char *new_line = malloc(1+ strlen(line));
                            //copy over
                            strcpy(new_line, line);
                            //create memory for each index item
                            array_value[i] = malloc(strlen(line) + 1);
                            //copy the line to array index
                            strcpy(array_value[i], new_line);
                        }
                    }
                    //create a new poitner object
                    GSV* gsv = (GSV*) malloc(sizeof(GSV));
                    //create a new GSV sentence
                    gsv = create_GSV_sentence(array_value);
                    //model->fix = is_good_fix(gsv, model);
                    //free(gsv);
                }
                //split
                value = strtok(NULL, ",");
            }
        }

    }
    // write_to_file(parser);
    //fclose(fp);
}
/**
* This loops over the second file and syncs the two streams. It checks for the times and checks that they are equal
* @param gga is the object created in the first read_file_one
* @param model is the model created in the read file one function
* @returns an int representing whether its found a match or not
*/
int read_file_two(GGA *gga, model *model)
{

    FILE *f_new;
    //opens up the second file
    f_new = fopen("gps_2.dat", "r");
    char line[200];
    if (f_new != NULL)
    {
        //loops over 200 characters
        while (fgets(line, 200, f_new) != NULL)
        {
            //dumps the line read in, into a char pointer
            char *temp = strdup(line);
            //splits it based on a comma.
            char *value = strsep(&temp, ",");
            if(value != NULL)
            {
                //checks to see if the split value is a GGA sentence
                if (strcmp(value, "$GPGGA") == 0)
                {
                    //creates a new pointer to a GGA
                    GGA *gga_ptr_two = (GGA*) malloc(sizeof(GGA));
                    //parses the sentence data
                    gga_ptr_two = create_GGA_sentence(line);
                    //sets the value of the current pointer index
                    set_ptr(gga_ptr_two);
                    //checks if the times are equal, if they are return 0 (true)
                    if(gga->time == gga_ptr_two->time)
                    {
                        return 0;
                    }
                }
                //check to see if it's a GSV sentence
                else if (strcmp(value, "$GPGSV") == 0)
                {
                    unsigned int i =0;
                    //array of char*
                    char* array_value[1000];
                    //create temp char pointer values
                    char* sub = (char*) malloc(sizeof(char) * strlen(line));
                    char* value = (char*) malloc(sizeof(char) * strlen(line));
                    char* sub_par = (char*) malloc(sizeof(char) * strlen(line));
                    strcpy(value, line);
                    //http://www.linuxquestions.org/questions/programming-9/extract-substring-from-string-in-c-432620/
                    //splits to get the number of sentences
                    strncpy(sub,value+7, 1);
                    //gets the type of sentence
                    strncpy(sub_par, value,6);
                    //loops over the number of sentences
                    for (i = 0; i < atoi(sub); i++)
                    {
                        //checks the sentence type
                        if(strcmp(sub_par, "$GPGSV") == 0)
                        {
                            //creates a temporary char * value
                            char *new_line = malloc(1+ strlen(line));
                            //copies the line over to the new char *
                            strcpy(new_line, line);
                            //allocates memory for the index value
                            array_value[i] = malloc(strlen(line) + 1);
                            //copy each sentence to that line
                            strcpy(array_value[i], new_line);
                        }
                    }
                    //create a new pointer of size the structure
                    GSV* gsv = (GSV*) malloc(sizeof(GSV));
                    //parse the data
                    gsv = create_GSV_sentence(array_value);
                    //model->fix = is_good_fix(gsv, model);
                    //free(gsv);
                }
            }

        }

    }
    return 1;
}


void set_ptr(GGA* value)
{
    snd_ptr = value;
}
GGA* get_ptr()
{
    return snd_ptr;
}


