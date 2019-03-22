/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-22
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
  std::unique_ptr<std::vector<std::string>> valids = std::make_unique<std::vector<std::string>>();
  valids->push_back("os.all");
  valids->push_back("os.Platform");
  valids->push_back("os.Caption");
  valids->push_back("os.Serial");
  valids->push_back("os.Bit");
  valids->push_back("os.InstallTime");
  valids->push_back("os.BootTime");
  valids->push_back("os.CurTime");
  valids->push_back("os.Kernel");
  valids->push_back("os.Version");

  for (int i = requests.size() - 1; i >= 0; i--)
  {
    if (!contains(valids.get(), requests[i]))
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
  std::unique_ptr<std::map<std::string, std::string>> reqKP = std::make_unique<std::map<std::string, std::string>>();
  (*reqKP)["os.Platform"] = compOS.Platform();
  (*reqKP)["os.Caption"] = compOS.Caption();
  (*reqKP)["os.Serial"] = compOS.Serial();
  (*reqKP)["os.Bit"] = std::to_string(compOS.Bit());
  (*reqKP)["os.InstallTime"] = compOS.InstallTime("%Y-%m-%dT%H:%M:%S");
  (*reqKP)["os.BootTime"] = compOS.BootTime("%Y-%m-%dT%H:%M:%S");
  (*reqKP)["os.CurTime"] = compOS.CurTime("%Y-%m-%dT%H:%M:%S");
  (*reqKP)["os.Kernel"] = compOS.Kernel().Pretty();
  (*reqKP)["os.Version"] = compOS.Version().Pretty();

  for (auto kp : (*reqKP))
  {
    if (contains(&requests, "os.all") || contains(&requests, kp.first))
    {
      keys->push_back(kp.first);
      vals->push_back(kp.second);
    }
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
