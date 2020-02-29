/**
*  @file      graphicslist.cpp
*  @brief     The implementation for the GraphicsList class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "graphicslist.h"
#include "graphics.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new GraphicsList object
*/
GraphicsList::GraphicsList()
{
  controllers = std::vector<Graphics>();
}

/**
* @brief Construct a new GraphicsList object with help from the assistants
*
* @param plt The platform of the system
*/
GraphicsList::GraphicsList(std::uint8_t plt)
{
  controllers = std::vector<Graphics>();

  switch (plt)
  {
  case OS_WIN:
    GetWin();
    break;
  case OS_MAC:
    GetMac();
    break;
  case OS_LUX:
    GetLux();
    break;
  }
}

/**
* @brief Construct a new GraphicsList object from another GraphicsList object
*
* @param o The GraphicsList object to copy from
*/
GraphicsList::GraphicsList(const GraphicsList &o)
{
  controllers = o.controllers;
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the GraphcsList information for Darwin systems
*/
void GraphicsList::GetMac()
{
  std::vector<std::string> allControllers;
  std::vector<std::string> eachController;
  Graphics tempController;
  std::string tempVendor = "";
  std::string tempModel = "";
  std::string tempBus = "";
  std::uint32_t tempVRAM = 0;
  bool tempDynamic = false;
  std::string line;
  std::string key;
  std::string val;

  splitStringVector(runCommand("system_profiler SPDisplaysDataType | grep -A 5 'Chipset Model:'"), "--", &allControllers);

  for (std::size_t i = 0; i < allControllers.size(); ++i)
  {
    splitStringVector(allControllers[i], "\n", &eachController);
    tempVendor = "";
    tempModel = "";
    tempBus = "";
    tempVRAM = 0;
    tempDynamic = false;

    for (std::size_t j = 0; j < eachController.size(); ++j)
    {
      if (eachController[j] == "")
      {
        continue;
      }
      line = trim(eachController[j]);
      key = trim(line.substr(0, line.find(':')));
      val = trim(line.substr(line.find(':') + 1));
      std::transform(key.begin(), key.end(), key.begin(), toupper);

      if (key == "VENDOR")
      {
        tempVendor = std::regex_replace(val, std::regex(" (.*)"), "");
      }
      else if (key == "CHIPSET MODEL")
      {
        tempModel = val;
      }
      else if (key == "BUS")
      {
        tempBus = val;
      }
      else if (key.substr(0, 4) == "VRAM")
      {
        tempVRAM = std::stoi(val.substr(0, val.length() - 3));
        tempVRAM *= pow(10, endswith(val, "GB") ? 9 : 6);
        if (key.substr(6, 7) == "DYNAMIC")
        {
          tempDynamic = true;
        }
      }
    }
    tempController = new Graphics(tempVendor, tempModel, tempBus, tempVRAM, tempDynamic);
    controllers.push_back(tempController);
  }
}

/**
* @brief Fills in the GraphcsList information for Windows systems
*/
void GraphicsList::GetWin()
{
  std::string wmic = getWmicPath();
  std::vector<std::map<std::string, std::string>> gpuList = runListMultiWmic("path win32_VideoController get AdapterCompatibility, AdapterRAM, PNPDeviceID, Name, VideoMemoryType", &wmic);
  Graphics tempController;
  std::string tempVendor = "";
  std::string tempModel = "";
  std::string tempBus = "";
  std::uint64_t tempVRAM = 0;
  bool tempDynamic = false;

  for (std::size_t i = 0; i < gpuList.size(); ++i)
  {
    tempVendor = gpuList[i]["AdapterCompatibility"];
    tempModel = gpuList[i]["Name"];
    tempBus = gpuList[i]["PNPDeviceID"].substr(0, 3) == "PCI" ? "PCIe" : "";
    tempVRAM = gpuList[i]["AdapterRAM"] == "" ? 0 : std::stoull(gpuList[i]["AdapterRAM"]);
    tempDynamic = gpuList[i]["VideoMemoryType"] == "2";

    tempController = new Graphics(tempVendor, tempModel, tempBus, tempVRAM, tempDynamic);
    controllers.push_back(tempController);
  }
}

/**
* @brief Fills in the GraphcsList information for Linux systems
*/
void GraphicsList::GetLux()
{
  std::string temp;
  std::vector<std::string> lines;
  Graphics tempController;
  std::string tempVendor = "";
  std::string tempModel = "";
  std::string tempBus = "";
  std::uint64_t tempVRAM = 0;
  bool tempDynamic = false;

  temp = runCommand("");
  splitStringVector(temp, "\n", &lines);

  bool found = false;

  std::smatch m;
  for (std::size_t i = 0; i < lines.size(); ++i)
  {
    if (lines[i].find(" VGA ") != std::string::npos)
    {
      if (std::regex_search(lines[i], m, std::regex(R"(\[(.*?)\])", std::regex_constants::ECMAScript)))
      {
        tempVendor = m[1];
      }
      lines[i] = m.suffix();
      if (std::regex_search(lines[i], m, std::regex(R"(\[(.*?)\])", std::regex_constants::ECMAScript)))
      {
        tempModel = m[1];
      }
      found = true;
    }
    if (found)
    {
      if (std::regex_search(lines[i], m, std::regex(R"(\[size=(\d+)M\])", std::regex_constants::ECMAScript)))
      {
        tempVRAM = std::stoull(m[1]) * pow(1000, 3);
      }
      if (lines[++i][0] != '\t')
      {
        tempController = Graphics(tempVendor, tempModel, tempBus, tempVRAM, tempDynamic);
        controllers.push_back(tempController);
        found = false;
        continue;
      }
    }
  }
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new GraphicsList object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *GraphicsList::operator new(std::size_t size)
{
  void *o = ::new (GraphicsList);
  return o;
}

/**
* @brief Sets equal two GraphicsList objects
*
* @param o The GraphicsList object to copy from
*/
void GraphicsList::operator=(const GraphicsList &o)
{
  if (&o == this)
  {
    return;
  }
  controllers = o.controllers;
}

/**
* @brief Sets equal two GraphicsList objects
*
* @param o The GraphicsList object to copy from
*/
void GraphicsList::operator=(GraphicsList *o)
{
  controllers = o->controllers;
}
#pragma endregion "Operators"
