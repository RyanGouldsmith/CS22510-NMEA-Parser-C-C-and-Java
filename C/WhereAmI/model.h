#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#define ARR_MAX_SIZE 10
/*!
 * \file model.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * this stores the current model information in a structre, inside here is attributes for the offset values.
 */
typedef struct
{
    float lat_off_set;
    float lng_off_set;
    float lat_off_set_values[ARR_MAX_SIZE];
    float lng_off_set_values[ARR_MAX_SIZE];
    int fix;
} model;

#endif // MODEL_H_INCLUDED
