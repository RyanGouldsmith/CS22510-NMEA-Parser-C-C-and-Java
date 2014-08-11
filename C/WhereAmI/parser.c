#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
#include "GGA.h"
#include "GSV.h"
#include "string.h"
#include "model.h"
#include <math.h>
/*!
 * \file parser.c
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This parsers different values and creates pointers to the structures based on the sentence type. It also works out the offset values in here 
 * It also gets all the SNR values from a sentence and checks to see whether they are a good fix or not.
 */

//creates two index values
int index_val=0;
int index_val_two =0;
/**
* This works out the offset for each of the two lat and longs received from file one and file two
* Checks to see which lat and longitude is smaller than the other and subtracts that away from the other
* @param one is the first GGA pointer created in the file_one function
* @param two is the second GGA pointer created in the file_two function
* @returns a pointer to the current model.
*/
model* work_out_offset(GGA* one, GGA* two, model *model)
{
    //checks to see if lat one is smaller than lat two
    if (one->lat < two->lat)
    {
        //set the offset to the be the difference of two from one
        model->lat_off_set = (two->lat - one->lat);
    }
    //checks to see if lat two is smaller than lat one
    else if (two->lat < one->lat)
    {
        //sets the offset to be the difference of one and two
        model->lat_off_set = (one->lat - two->lat);
    }
    //checks to see if the longitude of one is less than that of two
    if (one->lng < two->lng)
    {
        //sets the offset to be the difference of two from one
        model->lng_off_set = (two->lng - one->lng);
    }
    //checks to see if longitude of two is less than longitude of one
    else if (two->lng < one->lng)
    {
        //sets the longitude offset to be the difference of one from two
        model->lng_off_set = (one->lng - two->lng);
    }
    //returns the pointer to the model
    return model;
}
/**
* This updates the latitude array with the latest latitude
* @param lat is the current latitude values
* @param mod is the pointer to the current model instance from file_one function
* @returns a pointer to the model.
*/
model* update_lat_array(float lat, model *mod)
{
    //checks the size of the array whether it's empty
    if(sizeof(mod->lat_off_set_values) == 0)
    {
        //if so instansitate the first item with the lat value
        mod->lat_off_set_values[0] = lat;
    }
    else
    {
        //updates the value of the array with the current latitude value
        mod->lat_off_set_values[index_val] = lat;
        index_val++;
    }
    //return the model.
    return mod;
}
/**
* This updates the longitude array with the latest longitude values
* @param lng is the current longitude values
* @param mod is the pointer to the current model instance from file_one function
* @returns a pointer to the model.
*/
model* update_lng_array(float lng, model *mod)
{
    //checks to see if the array size is empty
    if(sizeof(mod->lng_off_set_values) == 0)
    {
        //set the first element to be the longitude value
        mod->lng_off_set_values[0] = lng;
    }
    else
    {
        //set the index value to be the longitude value
        mod->lng_off_set_values[index_val] = lng;
        index_val++;
    }
    //return the model
    return mod;
}
/**
* This parses a GGA sentence by splitting the values accoridingly and storing them in the GGA structs attribute
* It then calls the functions for converting to lat and long to decimal, to convert them to a proper time
* @param *line is a pointer to the line that is wanting to be parsed.
* @returns a pointer to a GGA structure.
*/
GGA* create_GGA_sentence(char *line)
{
    //creates a new pointer
    GGA *gga = (GGA*)malloc(sizeof(GGA));
    char* token = NULL;
    char *temp = line;
    //copy the line into a temp char*
    strcpy(temp, line);
    //split the  temp char * by the delimeter comma/
    token = strtok(temp, ",");
    char* array_value[10000];
    int i=0;
    //loops over the tokens and stores them in an array
    // REFERENCE http://answers.yahoo.com/question/index?qid=20090201223830AA4G1Du
    while(token !=NULL)
    {
        //allocates memory for the array value index
        array_value[i] = malloc(strlen(token) + 1);
        //copies the tokento the array values index
        strcpy(array_value[i], token);
        i++;
        token = strtok(NULL, ",");
    }
    //sets the lat, longitude, sign and time according to the places in the array. Converts some of the values to floats.
    gga->lat = atof(array_value[2]);
    gga->lng = atof(array_value[4]);
    gga->sign = array_value[5];
    gga->time = atof(array_value[1]);
    //Convers the lat and longitude values to the decimal equivelant.
    gga->lng = convert_long_to_decimal(gga);
    gga->lat = convert_lat_to_decimal(gga);
    //return the gga pointer
    return gga;
}
/**
* Checks to see whether the fix is good enough over a a number of GSV sentences.
* Determines if it's a good signal by if it's > 35 and if the accepted value is >= 3.
* @param *gsv is the pointer to the current gsv structure being comparing
* @param *model is the pointer to the current model that is being used.
* @returns an int where it's accepted or not. 0 = true, 1 = false.
*/
int is_good_fix(GSV *gsv, model *model)
{
    unsigned int accepted =0;
    unsigned int i;
    //loops over the SNR values
    for(i = 0; i < sizeof(gsv->snrValues); i++)
    {
        //checks to see if the SNR value at i is > 35
        if(gsv->snrValues[i] > 35)
        {
            //increment accepted
            accepted++;
        }
    }
    //if there's 3 SNR values over 35 then return 0, else return 1
    if (accepted >=3)
    {
        return 0;
    }

    return 1;
}
/**
* This extracts all the SNR numbers from a series of GSV sentenves.
* It then assigns the values to the SNR array of numbers, which can be checked against whether they're a good fix
* @param *line is the GSV sentence we're currently parsing for all the SNR numbers
* @param *gsv is the GSV pointer we're using to keep track of the current GSV.
* @return the a pointer to the modified GSV struct.
*/
GSV* get_SNR_number(char *line, GSV* gsv)
{
    char* token = NULL;
    //creates a temp line the length of the line we're reading in
    char *temp = malloc(sizeof(char) + strlen(line));
    //copy the line to the temp char pointer
    strcpy(temp, line);
    //split the line at the comma delimeter
    token = strtok(temp, ",");
    char* array_value[10000];
    unsigned int i = 0;
    // REFERENCE http://answers.yahoo.com/question/index?qid=20090201223830AA4G1Du
    while(token !=NULL)
    {
        //creates enough memory for the token size and the escape character
        array_value[i] = malloc(strlen(token) + 1);
        //copies the token over to the array
        strcpy(array_value[i], token);
        i++;
        token = strtok(NULL, ",");
    }
    unsigned int j;
    //loops over to every 4th item in the GSV sentence
    for (j = 4; j+3 < sizeof(line); j +=4)
    {
        //checks to see if the array value contains a *
        if(strstr(array_value[j+3], "*") != NULL)
        {

            char* token = NULL;
            char *temp = malloc(sizeof(char) + strlen(line));
            //copy the array item to thetemp char *
            strcpy(temp, array_value[j+3]);
            //split the temp line at the astrik
            token = strtok(temp, "*");
            char* delimeter_array[10000];
            unsigned int i = 0;
            // REFERENCE http://answers.yahoo.com/question/index?qid=20090201223830AA4G1Du
            while(token !=NULL)
            {
                //allocates enough memory for the array index
                delimeter_array[i] = malloc(strlen(token) + 1);
                //copt the token to the index
                strcpy(delimeter_array[i], token);
                i++;
                token = strtok(NULL, "*");
            }
            //copy the delimeter from position 0 without the astrik
            strcpy(array_value[j+3],delimeter_array[0]);
        }
        // add the values to the array
        int i = atoi(array_value[j+3]);
        //seg faulting here
        //gsv->snrValues[index_val_two] = i;
        index_val_two++;
    }
    //return the pointer to the GSV struct
    return gsv;
}
/**
* This creates a new GSV sentence. It gets the index  of the array of lines passed in and gets the SNR value and updates the SNR pointer
* @param is the number of lines read from the file input reader for a set of GSV sentences
*/
GSV* create_GSV_sentence(char **line)
{
    //creates a new GSV pointer
    GSV *gsv = (GSV*)malloc(sizeof(GSV));
    unsigned int i =0;
    //loops over the array
    for (i = 0; i < sizeof(line) /2; i++)
    {
        //checks to make sure the index isn't null
        if (line[i] != NULL)
        {
            //gets the SNR number for the line
            gsv = get_SNR_number(line[i], gsv);
        }
    }
    //returns the pointer
    return gsv;
}
/**
* Converts a NMEA long speak into a decimal representation
* REFERENCE: http://code.google.com/p/gpsd-nmea/source/browse/trunk/src/nmeaparser/nmea_parse.c?r=2
* It checks to see if the sign value means that the latitude sign needs changing
* @param *gga is the current pointer to the current GGA struct
* @returns the float value of the latitude
*/
float convert_long_to_decimal(GGA* gga)
{
    double degrees;
    float minutes= (float)100.0 * modf((double)gga->lng / 100.0, &degrees);
    float longitude = degrees + minutes/ 60.0;
    if(strcmp(gga->sign, "W") == 0)
    {
        longitude =-longitude;
    }
    return longitude;
}
/**
* Converts a NMEA lat speak into a decimal representation
* REFERENCE: http://code.google.com/p/gpsd-nmea/source/browse/trunk/src/nmeaparser/nmea_parse.c?r=2
* @param *gga is the current pointer to the current GGA struct
* @returns the float value of the latitude
*/
float convert_lat_to_decimal(GGA* gga)
{
    double degrees;
    float minutes= (float)100.0 * modf((double)gga->lat / 100.0, &degrees);
    float lat = degrees + minutes/ 60.0;
    return lat;
}
