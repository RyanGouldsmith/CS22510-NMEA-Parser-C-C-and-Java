#include <stdio.h>
#include <stdlib.h>
#include "InputHandler.h"
/*!
 * \file main.c
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This is where the main application runs.
 */

/**
* This is where the main application runs
* It called the read_file_one function and this runs the remainder of the application
* @returns whether it executes successfully or not
*/
int main()
{
    printf("LOADING FILE ONE AND TWO...");
    //loads the first file
    read_file_one("GPS_1.dat");
    printf("All Data has been processed correctly, and outputted to in a GPSX format");
    return 0;
}
