/**
*  @file      requests.h
*  @brief     The interface for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-19
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_REQUESTS_H_
#define CGOGGLES_REQUESTS_H_

#include "pch.h"
#include "utils.h"
#include "os.h"

extern std::vector<std::string> requests;
extern OutputStyle style;
extern OperatingSystem compOS;

void filterRequests();
void parseRequests(std::string* request);
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals);
void outputRequests();

#endif // CGOGGLES_REQUESTS_H_
