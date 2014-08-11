#include <iostream>
#include "GGA.h"
#include <vector>
#include <stdlib.h>
/*!
 * \file GGA.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This is the implementation of the gga class where it converts all the lat and lonitude to decimal values 
 */

using namespace std;
/**
* loops over a list, converts all the latitude and longitude points to decimal values and sets the time
* @param list is a list of lines of GGA
*/
GGA::GGA(vector<char*>list)
{
    for (unsigned int i=0; i < list.size(); i++)
    {
        this->set_lat(convertLatToDecimal(list[2]));
        this->set_lng(convertLongToDecimal(list[4], list[5]));
        this->set_time(atof(list[1]));
    }
}
/**
* The GGA classes Destructor
*/
GGA::~GGA()
{
}
/**
* This method is based on https://gist.github.com/javisantana/1326141
    * Used to convert the NMEA speak's longitude to the Decimal representation
    * @param value is the nmea value for the longitude
    * @param direction is whether it's W OR E
    * @returns a decimal representation of the longitude as a float
    */
float GGA::convertLatToDecimal(string value)
{
    float lat = atof(value.substr(2).c_str())/60.0f;
    lat +=  atof(value.substr(0, 2).c_str());
    return lat;
}
/**
* This method is based on https://gist.github.com/javisantana/1326141
* Used to convert the NMEA speak's longitude to the Decimal representation
* @param value is the nmea value for the longitude
* @param direction is whether it's W OR E
* @returns a decimal representation of the longitude as a float
*/
float GGA::convertLongToDecimal(string value, string direction)
{
    float lng = atof(value.substr(3).c_str())/60.0f;
    lng += atof(value.substr(0, 3).c_str());
    if(strcmp(direction.c_str(), "W") == 0)
    {
        lng = -lng;
    }
    return lng;
}
/**
    * Sets the latitude
    * @param lat is the latitude that is being set
    */
void GGA::set_lat(float lat)
{
    this->lat = lat;
}
/**
    * Sets the longitude
    * @param lng is the longitude that is being set
    */
void GGA::set_lng(float lng)
{
    this->lng = lng;
}
/**
* Sets the time
* @param time is the time that is being set
*/
void GGA::set_time(float time)
{
    this->time = time;
}
/**
* @returns the current latitude  value
*/
float GGA::get_lat()
{
    return this->lat;
}
/**
* @returns the current longitude value
*/
float GGA::get_lng()
{
    return this->lng;
}
/**
* @returns the current time value
*/
float GGA::get_time()
{
    return this->time;
}
