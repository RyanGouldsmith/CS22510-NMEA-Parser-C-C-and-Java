#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED
#include "GGA.h"
#include "model.h"
/*!
 * \file InputHandler.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This contains the function prototypes for the compiler and any other .c file can use and check against the type values.
 * The functions in here are implemented in the InputHandler.c file.
 */
void read_file_one(char *);
int read_file_two(GGA*, model*);
void set_ptr(GGA*);
GGA* get_ptr();
#endif // INPUTHANDLER_H_INCLUDED
