/**
*  @file      graphicslist.cpp
*  @brief     The implementation for the graphicslist class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-22
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "graphicslist.h"
#include "graphics.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
GraphicsList::GraphicsList()
{
  controllers = std::make_unique<std::vector<Graphics>>();
}

GraphicsList::GraphicsList(std::uint8_t plt)
{
  controllers = std::make_unique<std::vector<Graphics>>();

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

GraphicsList::GraphicsList(const GraphicsList &s)
{
  controllers = std::make_unique<std::vector<Graphics>>();

  (*controllers) = (*s.controllers);
}

GraphicsList::~GraphicsList()
{
  controllers.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the storage list information for Darwin systems
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

  for (std::size_t i = 0; i < allControllers.size(); i++)
  {
    splitStringVector(allControllers[i], "\n", &eachController);
    tempVendor = "";
    tempModel = "";
    tempBus = "";
    tempVRAM = 0;
    tempDynamic = false;

    for (std::size_t j = 0; j < eachController.size(); j++)
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
        tempVRAM *= val.substr(val.length() - 2) == "GB" ? 1024 : 1;
        if (key.substr(6, 7) == "DYNAMIC")
        {
          tempDynamic = true;
        }
      }
    }
    tempController = new Graphics(tempVendor, tempModel, tempBus, tempVRAM, tempDynamic);
    controllers->push_back(tempController);
  }
}

/**
* @brief Fills in the storage list information for Windows systems
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

  for (std::size_t i = 0; i < gpuList.size(); i++)
  {
    tempVendor = gpuList[i]["AdapterCompatibility"];
    tempModel = gpuList[i]["Name"];
    tempBus = gpuList[i]["PNPDeviceID"].substr(0, 3) == "PCI" ? "PCIe" : "";
    tempVRAM = gpuList[i]["AdapterRAM"] == "" ? 0 : std::stoull(gpuList[i]["AdapterRAM"]);
    tempDynamic = gpuList[i]["VideoMemoryType"] == "2";

    tempController = new Graphics(tempVendor, tempModel, tempBus, tempVRAM, tempDynamic);
    controllers->push_back(tempController);
  }
}

/**
* @brief Fills in the storage list information for Linux systems
*/
void GraphicsList::GetLux()
{
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new Graphics List object
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
* @brief Sets equal two Graphics List objects
*
* @param v The Graphics List object to copy from
*/
void GraphicsList::operator=(const GraphicsList &s)
{
  if (&s == this)
  {
    return;
  }
  controllers = std::make_unique<std::vector<Graphics>>();

  (*controllers) = (*s.controllers);
}

/**
* @brief Sets equal two Graphics List objects
*
* @param v The Graphics List object to copy from
*/
void GraphicsList::operator=(GraphicsList *s)
{
  controllers = std::make_unique<std::vector<Graphics>>();

  (*controllers) = (*s->controllers);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns the a copy of the drive list
*
* @return std::vector<Graphics> The drive list
*/
std::vector<Graphics> GraphicsList::Controllers()
{
  return (*controllers);
}
#pragma endregion "Accessors"
