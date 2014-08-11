#ifndef GSV_H_INCLUDED
#define GSV_H_INCLUDED
/*!
 * \file Gsv.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This is the GSV struct which stores an array of SNRValues which will be used to check the quality of a signal
 */
typedef struct
{
    int snrValues[80000];
} GSV;

#endif // GSV_H_INCLUDED
