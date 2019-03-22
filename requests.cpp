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
  valids->push_back("All");
  valids->push_back("os.All");
  valids->push_back("os.Platform");
  valids->push_back("os.Caption");
  valids->push_back("os.Serial");
  valids->push_back("os.Bit");
  valids->push_back("os.InstallTime");
  valids->push_back("os.BootTime");
  valids->push_back("os.CurTime");
  valids->push_back("os.Kernel");
  valids->push_back("os.Version");
  valids->push_back("cpu.All");
  valids->push_back("cpu.Manufacturer");
  valids->push_back("cpu.Architecture");
  valids->push_back("cpu.SocketType");
  valids->push_back("cpu.Brand");
  valids->push_back("cpu.Family");
  valids->push_back("cpu.Model");
  valids->push_back("cpu.Stepping");
  valids->push_back("cpu.Cores");
  valids->push_back("cpu.Threads");

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
  std::unique_ptr<bool> allAll = std::make_unique<bool>(contains(&requests, "All"));
  std::unique_ptr<bool> osAll = std::make_unique<bool>((*allAll) || contains(&requests, "os.All"));
  std::unique_ptr<bool> cpuAll = std::make_unique<bool>((*allAll) || contains(&requests, "cpu.All"));

  if ((*osAll) || contains(&requests, "os.Platform"))
  {
    keys->push_back("os.Platform");
    vals->push_back(compOS.Platform());
  }
  if ((*osAll) || contains(&requests, "os.Caption"))
  {
    keys->push_back("os.Caption");
    vals->push_back(compOS.Caption());
  }
  if ((*osAll) || contains(&requests, "os.Serial"))
  {
    keys->push_back("os.Serial");
    vals->push_back(compOS.Serial());
  }
  if ((*osAll) || contains(&requests, "os.Bit"))
  {
    keys->push_back("os.Bit");
    vals->push_back(std::to_string(compOS.Bit()));
  }
  if ((*osAll) || contains(&requests, "os.InstallTime"))
  {
    keys->push_back("os.InstallTime");
    vals->push_back(compOS.InstallTime("%Y-%m-%dT%H:%M:%S"));
  }
  if ((*osAll) || contains(&requests, "os.BootTime"))
  {
    keys->push_back("os.BootTime");
    vals->push_back(compOS.BootTime("%Y-%m-%dT%H:%M:%S"));
  }
  if ((*osAll) || contains(&requests, "os.CurTime"))
  {
    keys->push_back("os.CurTime");
    vals->push_back(compOS.CurTime("%Y-%m-%dT%H:%M:%S"));
  }
  if ((*osAll) || contains(&requests, "os.Kernel"))
  {
    keys->push_back("os.Kernel");
    vals->push_back(compOS.Kernel().Pretty());
  }
  if ((*osAll) || contains(&requests, "os.Version"))
  {
    keys->push_back("os.Version");
    vals->push_back(compOS.Version().Pretty());
  }

  if ((*cpuAll) || contains(&requests, "cpu.Manufacturer"))
  {
    keys->push_back("cpu.Manufacturer");
    vals->push_back(compCPU.Manufacturer());
  }
  if ((*cpuAll) || contains(&requests, "cpu.Architecture"))
  {
    keys->push_back("cpu.Architecture");
    vals->push_back(compCPU.Architecture());
  }
  if ((*cpuAll) || contains(&requests, "cpu.SocketType"))
  {
    keys->push_back("cpu.SocketType");
    vals->push_back(compCPU.SocketType());
  }
  if ((*cpuAll) || contains(&requests, "cpu.Brand"))
  {
    keys->push_back("cpu.Brand");
    vals->push_back(compCPU.Brand());
  }
  if ((*cpuAll) || contains(&requests, "cpu.Family"))
  {
    keys->push_back("cpu.Family");
    vals->push_back(std::to_string(compCPU.Family()));
  }
  if ((*cpuAll) || contains(&requests, "cpu.Model"))
  {
    keys->push_back("cpu.Model");
    vals->push_back(std::to_string(compCPU.Model()));
  }
  if ((*cpuAll) || contains(&requests, "cpu.Stepping"))
  {
    keys->push_back("cpu.Stepping");
    vals->push_back(std::to_string(compCPU.Stepping()));
  }
  if ((*cpuAll) || contains(&requests, "cpu.Cores"))
  {
    keys->push_back("cpu.Cores");
    vals->push_back(std::to_string(compCPU.Cores()));
  }
  if ((*cpuAll) || contains(&requests, "cpu.Threads"))
  {
    keys->push_back("cpu.Threads");
    vals->push_back(std::to_string(compCPU.Threads()));
  }
}

/**
* @brief Outputs all of the requests
*/
void outputRequests()
{
  std::unique_ptr<std::vector<std::string>> keys = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::vector<std::string>> vals = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<char> delChar = std::make_unique<char>(style == OutputStyle::Default ? '\n' : '=');
  gatherRequests(keys.get(), vals.get());

  for (std::size_t i = 0; i < keys->size(); i++)
  {
    std::cout << (*keys)[i] << *delChar << (*vals)[i] << std::endl;
  }
}
