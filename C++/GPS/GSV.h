#ifndef GSV_H_INCLUDED
#define GSV_H_INCLUDED
#include <vector>
/*!
 * \file GSV.h
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This header file stores the class for the GSV object. This stores the SNR values of the sentence and checks to see if it's a good enough fix
 */
class GSV
{
private:
    std::vector<int> snrValues;
public:
    GSV(std::vector<char*>);
    void getSNRNumber(char*);
    bool isFixGood();
    std::vector<char*> addValuesToVector(char*);
};
#endif // GSV_H_INCLUDED
