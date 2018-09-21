/* 
 * File:   Util.h
 * Author: Kapil Thakkar
 
 */

#ifndef UTIL_H
#define	UTIL_H

#include "string.h"
#include <vector>
using namespace std;

/**
 * Utility Function to split string message, using give delimiter. The result is stored in result[] array.
 * 
 * @param message string to be splitted
 * @param delimter delimiter used to split string
 * @param result result will be stored in this array
 * @param expcted length of the result
 */
void splitString(string message, string delimiter, vector <string>& result) {
    int pos = 0, length = 0, temp;
    temp = message.find ( delimiter.c_str ( ), pos );
    while ( temp != -1 )
    {
        length = temp - pos;
        result.push_back(message.substr ( pos, length ));
        pos = temp + delimiter.size ( );
        temp = message.find ( delimiter.c_str ( ), pos );
    }
    result.push_back(message.substr ( pos ));
}


#endif	/* UTIL_H */

