#ifndef GGA_H_INCLUDED
#define GGA_H_INCLUDED
/*!
 * \file GGA.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This is the GGA header file, it stores the struct for the a single GGA sentence.
 * The Struct contains a time, lat, longitude and the sign value for the direction
 */
typedef struct
{
    float time;
    float lat;
    float lng;
    char* sign;
} GGA;


#endif // GGA_H_INCLUDED
