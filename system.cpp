/**
*  @file      system.cpp
*  @brief     The implementation for the system class.
*
*  @author    Evan Elias Young
*  @date      2019-04-03
*  @date      2019-04-03
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  manufacturer = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  version = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
}

/**
* @brief Construct a new System object with help from the assistants
*
* @param plt The platform of the system
*/
System::System(std::uint8_t plt)
{
  manufacturer = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  version = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();

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
* @brief Destroy the System object
*/
System::~System()
{
  manufacturer.reset();
  model.reset();
  version.reset();
  serial.reset();
  uuid.reset();
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void System::GetMac()
{
}

/**
* @brief Fills in the processor information for Windows systems
*/
void System::GetWin()
{
  std::string wmic = getWmicPath();
  std::map<std::string, std::string> dataMap = runMultiWmic("csproduct get Vendor, Name, Version, IdentifyingNumber, UUID", &wmic);

  (*manufacturer) = dataMap["Vendor"];
  (*model) = dataMap["Name"];
  (*version) = dataMap["Version"];
  (*serial) = dataMap["IdentifyingNumber"];
  (*uuid) = dataMap["UUID"];
}

/**
* @brief Fills in the processor information for Linux systems
*/
void System::GetLux()
{
  std::ifstream tempFile;
  std::string *temp = new std::string;

  (*manufacturer) = readFile("/sys/devices/virtual/dmi/id/sys_vendor", temp) ? trim((*temp)) : "";
  (*model) = readFile("/sys/devices/virtual/dmi/id/product_name", temp) ? trim((*temp)) : "";
  (*version) = readFile("/sys/devices/virtual/dmi/id/product_version", temp) ? trim((*temp)) : "";
  (*serial) = readFile("/sys/devices/virtual/dmi/id/product_serial", temp) ? trim((*temp)) : "";
  (*uuid) = readFile("/sys/devices/virtual/dmi/id/product_uuid", temp) ? trim((*temp)) : "";
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Sets one System equal to another
*
* @param o The System to copy from
*/
void System::operator=(System *s)
{
  (*manufacturer) = (*s->manufacturer);
  (*model) = (*s->model);
  (*version) = (*s->version);
  (*serial) = (*s->serial);
  (*uuid) = (*s->uuid);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the manufacturer
*
* @return std::string The manufacturer
*/
std::string System::Manufacturer()
{
  return (*manufacturer);
}

/**
* @brief Returns a copy of the model
*
* @return std::string The model
*/
std::string System::Model()
{
  return (*model);
}

/**
* @brief Returns a copy of the version
*
* @return std::string The version
*/
std::string System::Version()
{
  return (*version);
}

/**
* @brief Returns a copy of the serial number
*
* @return std::string The serial number
*/
std::string System::Serial()
{
  return (*serial);
}

/**
* @brief Returns a copy of the UUID
*
* @return std::string The UUID
*/
std::string System::UUID()
{
  return (*uuid);
}
#pragma endregion "Accessors"
