#ifndef GPSPARSER_H_INCLUDED
#define GPSPARSER_H_INCLUDED
#include <string>
#include "GGA.h"
#include "Model.h"
using namespace std;
/*!
 * \file GPSParser.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * this header file contains the class object of a GPSParser. It stores all the values that is parsed. See GPSParser.cpp for the full implmentation
 */
class GPSParser
{
private:
    float time;
    float lat;
    float lng;
    float lat_offset;
    float lng_offset;
    float offset;
    GGA *gga;
    GGA *gga_two;
public:
    GPSParser(string);
    ~GPSParser();
    void set_time(float);
    void set_lat(float);
    void set_lng(float);
    void set_lat_offset(float);
    void set_lng_offset(float);
    void parse_line(string);
    float get_time(void);
    float get_lat(void);
    float get_lng(void);
    float get_lng_offset(void);
    float get_lat_offset(void);
    void work_out_offset(GGA*,GGA*, Model*);
    GGA* get_current_GGA(void);
    GGA* get_current_GGA_two(void);
    void set_current_GGA_two(GGA);
};

#endif // GPSPARSER_H_INCLUDED
