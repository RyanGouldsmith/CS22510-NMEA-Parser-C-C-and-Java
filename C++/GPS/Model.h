#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED
#include <vector>
/*!
 * \file Model.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This is the Model header file where I store all the information relating to a Model class.
 * This acts a place holder for a series of values in my application.
 * I a have a series of private variables  and public functions. To see the implmentation see the Model.cpp file.
 */
class Model
{
private:
    float lat_offset;
    float lng_offset;
    float lat;
    float lng;
    std::vector<float> lat_values;
    std::vector<float> lng_values;
public:
    Model();
    ~Model();
    void set_lat_offset(float);
    void set_lng_offset(float);
    void set_lat(float);
    void set_lng(float);
    float get_lat_offset();
    float get_lng_offset();
    float get_lat();
    float get_lng();
    std::vector<float> get_lat_values();
    std::vector<float> get_lng_values();
    void set_lat_values(float);
    void set_lng_values(float);
};
#endif // MODEL_H_INCLUDED
