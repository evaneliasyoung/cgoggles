/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-19
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "requests.h"
#include "utils.h"

/**
* @brief Filters out any unsupported requests from the queue
*/
void filterRequests()
{
  std::string valids[10] = {
      "os.all",
      "os.Platform",
      "os.Caption",
      "os.Serial",
      "os.Bit",
      "os.InstallTime",
      "os.BootTime",
      "os.CurTime",
      "os.Kernel",
      "os.Version"};

  for (int i = requests.size() - 1; i >= 0; i--)
  {
    if (std::find(std::begin(valids), std::end(valids), requests[i]) == std::end(valids))
    {
      requests.erase(requests.begin() + i);
    }
  }
  removeDuplicates(&requests);
}

/**
* @brief Turns the raw request string into a collection of requests
*
* @param request A pointer to the raw request
*/
void parseRequests(std::string *request)
{
  splitStringVector((*request), ",", &requests);
  filterRequests();
}

/**
* @brief Turns the list of requests into a list of data
*/
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals)
{
  if (contains(&requests, "os.all") || contains(&requests, "os.Platform"))
  {
    keys->push_back("os.Platform");
    vals->push_back(compOS.Platform());
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.Caption"))
  {
    keys->push_back("os.Caption");
    vals->push_back(compOS.Caption());
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.Serial"))
  {
    keys->push_back("os.Serial");
    vals->push_back(compOS.Serial());
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.Bit"))
  {
    keys->push_back("os.Bit");
    vals->push_back(std::to_string(compOS.Bit()));
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.InstallTime"))
  {
    keys->push_back("os.InstallTime");
    vals->push_back(compOS.InstallTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.BootTime"))
  {
    keys->push_back("os.BootTime");
    vals->push_back(compOS.BootTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.CurTime"))
  {
    keys->push_back("os.CurTime");
    vals->push_back(compOS.CurTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.Kernel"))
  {
    keys->push_back("os.Kernel");
    vals->push_back(compOS.Kernel().Pretty());
  }
  if (contains(&requests, "os.all") || contains(&requests, "os.Version"))
  {
    keys->push_back("os.Version");
    vals->push_back(compOS.Version().Pretty());
  }
}

/**
* @brief Outputs all of the requests
*/
void outputRequests()
{
  std::unique_ptr<std::vector<std::string>> keys = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::vector<std::string>> vals = std::make_unique<std::vector<std::string>>();
  gatherRequests(keys.get(), vals.get());

  for (std::size_t i = 0; i < keys->size(); i++)
  {
    std::cout << (*keys)[i];
    if (style == OutputStyle::Default)
    {
      std::cout << std::endl;
    }
    else
    {
      std::cout << '=';
    }

    std::cout << (*vals)[i] << std::endl;
  }
}
