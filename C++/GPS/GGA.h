#ifndef GGA_H_INCLUDED
#define GGA_H_INCLUDED
#include <vector>
#include <string.h>
/*!
 * \file GGA.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This header file stores the class for the GGA sentence informaation. It sets the lat and long and converts the lat and long to proper decimal values.
 */
class GGA
{
private:
    float time;
    float lat;
    float lng;
    float convertLongToDecimal(std::string, std::string);
    float convertLatToDecimal(std::string);
public:
    GGA(std::vector<char*>);
    ~GGA();
    void set_time(float);
    void set_lat(float);
    void set_lng(float);
    float get_time(void);
    float get_lat(void);
    float get_lng(void);
};


#endif // GGA_H_INCLUDED
