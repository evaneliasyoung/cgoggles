/**
*  @file      chassis.cpp
*  @brief     The implementation for the Chassis class.
*
*  @author    Evan Elias Young
*  @date      2019-09-11
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "chassis.h"
#include "os.h"

#pragma region "Constructors"
/**
* @brief Construct a new Chassis object
*/
Chassis::Chassis()
{
  manufacturer = "";
  model = "";
  type = "";
  version = "";
  serial = "";
  assetTag = "";
}

/**
* @brief Construct a new Chassis object
*
* @param plt The platform of the system
*/
Chassis::Chassis(std::uint8_t plt)
{
  manufacturer = "";
  model = "";
  type = "";
  version = "";
  serial = "";
  assetTag = "";

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
* @brief Construct a new Chassis object from another Chassis object
*
* @param o The Chassis object to copy from
*/
Chassis::Chassis(const Chassis &o)
{
  manufacturer = o.manufacturer;
  type = o.type;
  model = o.model;
  version = o.version;
  serial = o.serial;
  assetTag = o.assetTag;
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the OS information for Darwin systems
*/
void Chassis::GetMac() {}

/**
* @brief Fills in the OS information for Windows systems
*/
void Chassis::GetWin()
{
  std::string wmic = getWmicPath();
  std::map<std::string, std::string> dataMap = runMultiWmic("path Win32_SystemEnclosure get Manufacturer,Model,ChassisTypes,Version,SerialNumber,PartNumber", &wmic);
  std::smatch mt;
  std::string *cases = new std::string[36]{
      "Other",
      "Unknown",
      "Desktop",
      "Low Profile Desktop",
      "Pizza Box",
      "Mini Tower",
      "Tower",
      "Portable",
      "Laptop",
      "Notebook",
      "Hand Held",
      "Docking Station",
      "All in One",
      "Sub Notebook",
      "Space-Saving",
      "Lunch Box",
      "Main System Chassis",
      "Expansion Chassis",
      "SubChassis",
      "Bus Expansion Chassis",
      "Peripheral Chassis",
      "Storage Chassis",
      "Rack Mount Chassis",
      "Sealed-Case PC",
      "Multi-System Chassis",
      "Compact PCI",
      "Advanced TCA",
      "Blade",
      "Blade Enclosure",
      "Tablet",
      "Concertible",
      "Detachable",
      "IoT Gateway ",
      "Embedded PC",
      "Mini PC",
      "Stick PC"};
  std::string temp = dataMap["ChassisTypes"];

  if (std::regex_search(temp, mt, std::regex(R"((\d+))", std::regex_constants::ECMAScript | std::regex_constants::icase)))
  {
    type = cases[std::stoi(mt[1]) - 1];
  }
  else
  {
    type = "Unknown";
  }

  manufacturer = dataMap["Manufacturer"];
  model = dataMap["Model"];
  version = dataMap["Version"];
  serial = dataMap["SerialNumber"];
  assetTag = dataMap["PartNumber"];
}

/**
* @brief Fills in the OS information for Linux systems
*/
void Chassis::GetLux() {}
#pragma endregion "Constructors' Assistants"

#pragma region "Operators"
/**
* @brief Reserves memory for a new Chassis object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Chassis::operator new(std::size_t size)
{
  void *o = ::new (Chassis);
  return o;
}

/**
* @brief Sets equal two Chassis objects
*
* @param o The Chassis object to copy from
*/
void Chassis::operator=(const Chassis &o)
{
  if (&o == this)
  {
    return;
  }

  manufacturer = o.manufacturer;
  model = o.model;
  type = o.type;
  version = o.version;
  serial = o.serial;
  assetTag = o.assetTag;
}

/**
* @brief Sets equal two Chassis objects
*
* @param o The Chassis object to copy from
*/
void Chassis::operator=(Chassis *o)
{
  manufacturer = o->manufacturer;
  model = o->model;
  type = o->type;
  version = o->version;
  serial = o->serial;
  assetTag = o->assetTag;
}
#pragma endregion "Operators"
