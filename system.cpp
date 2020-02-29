/**
*  @file      system.cpp
*  @brief     The implementation for the System class.
*
*  @author    Evan Elias Young
*  @date      2019-04-03
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "system.h"
#include "os.h"
#include "utils.h"

#pragma region "Constructors"
/**
* @brief Construct a new System object
*/
System::System()
{
  manufacturer = "";
  model = "";
  version = "";
  serial = "";
  uuid = "";
}

/**
* @brief Construct a new System object with help from the assistants
*
* @param plt The platform of the system
*/
System::System(std::uint8_t plt)
{
  switch (CGOGGLES_OS)
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
* @brief Construct a new System object from another System object
*
* @param o The System object to copy from
*/
System::System(const System &o)
{
  manufacturer = o.manufacturer;
  model = o.model;
  version = o.version;
  serial = o.serial;
  uuid = o.uuid;
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void System::GetMac()
{
  std::string temp;
  std::vector<std::string> lines;
  std::string key;
  std::string val;
  splitStringVector(runCommand("ioreg -c IOPlatformExpertDevice -d 2"), "\n", &lines);

  for (std::size_t i = 0; i < lines.size(); ++i)
  {
    if (!(startswith(trim(lines[i]), "\"") && lines[i].find(" = ") != std::string::npos))
    {
      continue;
    }

    splitKeyValuePair(trim(lines[i]), &key, &val, true, '=');
    key = key.substr(1, key.size() - 2);
    val = val.substr(1, val.size() - 2);

    if (key == "manufacturer")
    {
      manufacturer = val.substr(1, val.size() - 2);
    }
    if (key == "model")
    {
      version = val.substr(1, val.size() - 2);
    }
    if (key == "version")
    {
      version = val.substr(1, val.size() - 2);
    }
    if (key == "IOPlatformSerialNumber")
    {
      serial = val;
    }
    if (key == "IOPlatformUUID")
    {
      uuid = val;
    }
  }
}

/**
* @brief Fills in the processor information for Windows systems
*/
void System::GetWin()
{
  std::string wmic = getWmicPath();
  std::map<std::string, std::string> dataMap = runMultiWmic("csproduct get Vendor, Name, Version, IdentifyingNumber, UUID", &wmic);

  manufacturer = dataMap["Vendor"];
  model = dataMap["Name"];
  version = dataMap["Version"];
  serial = dataMap["IdentifyingNumber"];
  uuid = dataMap["UUID"];
}

/**
* @brief Fills in the processor information for Linux systems
*/
void System::GetLux()
{
  std::ifstream tempFile;
  std::string *temp = new std::string;

  manufacturer = readFile("/sys/devices/virtual/dmi/id/sys_vendor", temp) ? trim((*temp)) : "";
  model = readFile("/sys/devices/virtual/dmi/id/product_name", temp) ? trim((*temp)) : "";
  version = readFile("/sys/devices/virtual/dmi/id/product_version", temp) ? trim((*temp)) : "";
  serial = readFile("/sys/devices/virtual/dmi/id/product_serial", temp) ? trim((*temp)) : "";
  uuid = readFile("/sys/devices/virtual/dmi/id/product_uuid", temp) ? trim((*temp)) : "";
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new System object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *System::operator new(std::size_t size)
{
  void *o = ::new (System);
  return o;
}

/**
* @brief Sets equal two System objects
*
* @param o The System object to copy from
*/
void System::operator=(const System &o)
{
  if (&o == this)
  {
    return;
  }
  manufacturer = o.manufacturer;
  model = o.model;
  version = o.version;
  serial = o.serial;
  uuid = o.uuid;
}

/**
* @brief Sets equal two System objects
*
* @param o The System object to copy from
*/
void System::operator=(System *o)
{
  manufacturer = o->manufacturer;
  model = o->model;
  version = o->version;
  serial = o->serial;
  uuid = o->uuid;
}
#pragma endregion "Operators"
