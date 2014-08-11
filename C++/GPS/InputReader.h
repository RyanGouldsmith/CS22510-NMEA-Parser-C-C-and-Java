#ifndef INPUTREADER_H_INCLUDED
#define INPUTREADER_H_INCLUDED
#include <string>
#include <fstream>
#include "GGA.h"
#include "GPSParser.h"
using namespace std;
/*!
 * \file InputReader.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This class has the private variables and public and private members for the Input Reeader class.
 * This is class is used for reading information from the file.
 * To see the implementation of the public and private members see the inputreader.cpp file.
 */
class InputReader
{
private:
    string file_one;
    string file_two;
    GPSParser* parser_one;
    GPSParser* parser_two;
    bool fix;
public:
    InputReader(string, string);
    ~InputReader();
    void set_parser_one(GPSParser);
    void set_parser_two(GPSParser);
    GPSParser* get_parser_one();
    GPSParser* get_parser_two();
private:
    void add_values_to_parser(string, string);
    void read_file_one(string);
    bool read_second_file(GGA*);
    void set_reader(ifstream);
};


#endif // INPUTREADER_H_INCLUDED
