#include "Markup.h"
#include "Model.h"
#include "Exporter.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
/*!
 * \file Exporter.cpp
 *
 * \author Ryan Gouldsmih
 * \date 28th March
 *
 * This stores the information for the exporter, with a single method called write_to_xml which, writes the model to the XML file.
 */

/**
* Uses the Library of CMarkup from http://www.firstobject.com/fast-start-to-xml-in-c++.htm
* This is the writing to the external file it writes out the root element and all the way point elements
* @param model is a pointer to the current model.
*/
void Exporter::write_to_xml(Model *model)
{
    CMarkup xml;
    xml.AddElem("GPX");
    xml.SetAttrib("version", "1.0");
    xml.SetAttrib("creator", "GPSFix - Ryan Gouldsmith (ryg1@aber.ac.uk)");
    xml.SetAttrib("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    xml.SetAttrib("xmlns", "http://www.topografix.com/GPX/1/0");
    xml.SetAttrib("xsi:schemaLocation", "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd");
    xml.IntoElem();
    unsigned int i =0;
    //loops over the size of the lat values and sets an element and attribute
    for (i = 0; i < model->get_lat_values().size(); i++)
    {
        xml.AddElem("wpt");
        xml.SetAttrib("lat", to_string(model->get_lat_values().at(i)));
        xml.SetAttrib("lon", to_string(model->get_lng_values().at(i)));
    }
    xml.Save("C++.gpx");
}
/**
* Rerence http://www.cplusplus.com/reference/sstream/ostringstream/str/
* Used to convert a float to a string
* @param value is the float in which is being converted to a string
* @returns a string representention
*/
std::string Exporter::to_string(float value)
{
    std::ostringstream buffer;
    buffer << value;
    std::string str = buffer.str();
    return str;
}


