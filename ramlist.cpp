/**
*  @file      ramlist.cpp
*  @brief     The implementation for the ramlist class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2019-04-04
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "ramlist.h"
#include "ram.h"
#include "os.h"

#pragma region "Contructors"
RAMList::RAMList()
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);
}

RAMList::RAMList(std::uint8_t plt)
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

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

RAMList::RAMList(const RAMList &s)
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*s.chips);
  (*total) = (*s.total);
}

RAMList::~RAMList()
{
  chips.reset();
  total.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the storage list information for Darwin systems
*/
void RAMList::GetMac()
{
}

/**
* @brief Fills in the storage list information for Windows systems
*/
void RAMList::GetWin()
{
  std::string wmic = getWmicPath();
  std::vector<std::map<std::string, std::string>> allChips = runListMultiWmic("memorychip get", &wmic);
  std::string memoryTypes[31] = {
      "Unknown", "Other", "DRAM", "Synchronous DRAM",
      "Cache DRAM", "EDO", "EDRAM", "VRAM",
      "SRAM", "RAM", "ROM", "FLASH",
      "EEPROM", "FEPROM", "EPROM", "CDRAM",
      "3DRAM", "SDRAM", "SGRAM", "RDRAM",
      "DDR", "DDR2", "DDR2 FB-DIMM", "Reserved",
      "DDR3", "FBD2", "DDR4", "LPDDR",
      "LPDDR2", "LPDDR3", "LPDDR4"};
  std::string memoryForms[24] = {
      "Unknown", "Other", "SIP", "DIP",
      "ZIP", "SOJ", "Proprietary", "SIMM",
      "DIMM", "TSOP", "PGA", "RIMM",
      "SODIMM", "SRIMM", "SMD", "SSMP",
      "QFP", "TQFP", "SOIC", "LCC",
      "PLCC", "BGA", "FPBGA", "LGA"};
  RAM tempChip;
  std::uint64_t tempSize = 0;
  std::string tempBank = "";
  std::string tempType = "";
  float tempSpeed = 0;
  std::string tempFormFactor = "";
  std::string tempManufacturer = "";
  std::string tempPart = "";
  std::string tempSerial = "";
  float tempVoltageConfigured = 0;
  float tempVoltageMin = 0;
  float tempVoltageMax = 0;

  for (std::size_t i = 0; i < allChips.size(); i++)
  {
    tempSize = !allChips[i]["Capacity"].empty() ? std::stoull(allChips[i]["Capacity"]) : 0;
    (*total) += tempSize;
    tempBank = !allChips[i]["BankLabel"].empty() ? allChips[i]["BankLabel"] : allChips[i]["DeviceLocator"];
    tempType = memoryTypes[std::stoi(allChips[i]["MemoryType"])];
    tempSpeed = !allChips[i]["ConfiguredClockSpeed"].empty() ? std::stof(allChips[i]["ConfiguredClockSpeed"]) : !allChips[i]["Speed"].empty() ? std::stof(allChips[i]["Speed"]) : 0;
    tempFormFactor = memoryForms[!allChips[i]["FormFactor"].empty() ? std::stoi(allChips[i]["FormFactor"]) : 0];
    tempManufacturer = allChips[i]["Manufacturer"];
    tempPart = allChips[i]["PartNumber"];
    tempSerial = allChips[i]["SerialNumber"];
    tempVoltageConfigured = !allChips[i]["ConfiguredVoltage"].empty() ? std::stof(allChips[i]["ConfiguredVoltage"]) / 1000 : 0;
    tempVoltageMin = !allChips[i]["MinVoltage"].empty() ? std::stof(allChips[i]["MinVoltage"]) / 1000 : 0;
    tempVoltageMax = !allChips[i]["MaxVoltage"].empty() ? std::stof(allChips[i]["MaxVoltage"]) / 1000 : 0;

    tempChip = (new RAM(tempSize, tempBank, tempType, tempSpeed, tempFormFactor, tempManufacturer, tempPart, tempSerial, tempVoltageConfigured, tempVoltageMin, tempVoltageMax));
    chips->push_back(tempChip);
  }
}

/**
* @brief Fills in the storage list information for Linux systems
*/
void RAMList::GetLux()
{
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new RAM System object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *RAMList::operator new(std::size_t size)
{
  void *o = ::new (RAMList);
  return o;
}

/**
* @brief Sets equal two RAM System objects
*
* @param v The RAM System object to copy from
*/
void RAMList::operator=(const RAMList &s)
{
  if (&s == this)
  {
    return;
  }
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*s.chips);
  (*total) = (*s.total);
}

/**
* @brief Sets equal two RAM System objects
*
* @param v The RAM System object to copy from
*/
void RAMList::operator=(RAMList *s)
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*s->chips);
  (*total) = (*s->total);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns the a copy of the drive list
*
* @return std::vector<RAM> The drive list
*/
std::vector<RAM> RAMList::Chips()
{
  return (*chips);
}

/**
* @brief Returns the a copy of the total amount of RAM
*
* @return std::uint64_t The total amount of RAM
*/
std::uint64_t RAMList::Total()
{
  return (*total);
}
#pragma endregion "Accessors"
