/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-15
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "requests.h"
#include "utils.h"

void filterRequests()
{
  for (int i = requests.size() - 1; i >= 0; i--)
  {
    if (requests[i] != "cpu")
    {
      requests.erase(requests.begin() + i);
    }
  }
  removeDuplicates(&requests);
}

void parseRequests()
{
  splitStringVector(request, ",", &requests);
  filterRequests();
}