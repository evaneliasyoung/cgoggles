/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-03-19
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_UTILS_H_
#define CGOGGLES_UTILS_H_

#include "pch.h"

extern std::vector<std::string> requests;
extern bool jsonExport;

void splitStringVector(const std::string &s, const std::string &d, std::vector<std::string> *v);
void removeDuplicates(std::vector<std::string> *v);
std::string getWmicPath();

#endif // CGOGGLES_UTILS_H_
