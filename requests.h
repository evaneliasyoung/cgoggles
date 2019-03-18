/**
*  @file      requests.h
*  @brief     The interface for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-15
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_REQUESTS_H_
#define CGOGGLES_REQUESTS_H_

#include "pch.h"

void filterRequests();
void parseRequests(std::string* request);

#endif // CGOGGLES_REQUESTS_H_
