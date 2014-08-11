#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "GGA.h"
#include "GSV.h"
#include "model.h"
/*!
 * \file Parser.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This header file contains the struct used for the Parser structure, which contains a time, lat, long, lat offset value, lngoffset value, a lng array and a lat array.
 * This is to be used when parsing the information to the XML file.
 * it additionally has a list of function prototypes used throughout the program to allow for better compiler checking.
 */
typedef struct
{
    float time;
    float lat;
    float lng;
    float lat_offset;
    float lng_offset;
    float lat_arr[10000];
    float lng_arr[10000];
    float offset;
} Parser;
model* work_out_offset(GGA*, GGA*, model*);
void intepret(char*);
GGA* create_GGA_sentence(char*);
GSV* create_GSV_sentence(char**);
float convert_long_to_decimal(GGA*);
float convert_lat_to_decimal(GGA*);
GSV* get_SNR_number(char*, GSV*);
int is_good_fix(GSV*, model*);
#endif // PARSER_H_INCLUDED
