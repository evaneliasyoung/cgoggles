/**
*  @file      ramlist.cpp
*  @brief     The implementation for the RAMList class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "ramlist.h"
#include "ram.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new RAMList object
*/
RAMList::RAMList()
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);
}

/**
* @brief Construct a new RAMList object with help from the assistants
*
* @param plt The platform of the system
*/
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

/**
* @brief Construct a new RAMList object from another RAMList object
*
* @param o The RAMList object to copy from
*/
RAMList::RAMList(const RAMList &o)
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*o.chips);
  (*total) = (*o.total);
}

/**
* @brief Destroy the RAMList object
*/
RAMList::~RAMList()
{
  chips.reset();
  total.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the RAMList information for Darwin systems
*/
void RAMList::GetMac()
{
  std::map<std::string, std::string> manufMap = {
      {"0x014F", "Transcend Information"},
      {"0x2C00", "Micron Technology Inc."},
      {"0x802C", "Micron Technology Inc."},
      {"0x80AD", "Hynix Semiconductor Inc."},
      {"0x80CE", "Samsung Electronics Inc."},
      {"0xAD00", "Hynix Semiconductor Inc."},
      {"0xCE00", "Samsung Electronics Inc."},
      {"0x02FE", "Elpida"},
      {"0x5105", "Qimonda AG i. In."},
      {"0x8551", "Qimonda AG i. In."},
      {"0x859B", "Crucial"}};
  std::vector<std::string> allChips;
  RAM tempChip;
  std::uint64_t tempSize = 0;
  std::string tempBank = "";
  std::string tempType = "";
  std::uint64_t tempSpeed = 0;
  std::string tempFormFactor = "";
  std::string tempManufacturer = "";
  std::string tempPart = "";
  std::string tempSerial = "";
  float tempVoltageConfigured = 0;
  float tempVoltageMin = 0;
  float tempVoltageMax = 0;
  std::string key;
  std::string val;
  splitStringVector(runCommand("system_profiler SPMemoryDataType"), "\n", &allChips);

  for (std::size_t i = 0; i < allChips.size(); ++i)
  {
    if (trim(allChips[i]).empty())
    {
      continue;
    }
    if (splitKeyValuePair(trim(allChips[i]), &key, &val))
    {
      if (key == "Size")
      {
        tempSize = std::stoull(val.substr(0, val.size() - 3)) * pow(10, 9);
      }
      else if (startswith(key, "BANK "))
      {
        tempBank = key.substr(key.find_first_of("/") + 1);
      }
      else if (key == "Type")
      {
        tempType = val;
      }
      else if (key == "Speed")
      {
        tempSpeed = std::stof(val.substr(0, val.size() - 4)) * pow(10, 6);
      }
      else if (key == "Manufacturer")
      {
        tryGetValue(manufMap, val, &tempManufacturer);
      }
      else if (key == "Part Number")
      {
        tempPart = val;
      }
      else if (key == "Serial Number")
      {
        tempSerial = val;
      }

      if (i == allChips.size() - 3 || (i > 7 && i < allChips.size() - 3 && startswith(trim(allChips[i + 2]), "BANK ")))
      {
        tempChip = (new RAM(tempSize, tempBank, tempType, tempSpeed, tempFormFactor, tempManufacturer, tempPart, tempSerial, tempVoltageConfigured, tempVoltageMin, tempVoltageMax));
        chips->push_back(tempChip);
      }
    }
  }
}

/**
* @brief Fills in the RAMList information for Windows systems
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
  std::uint64_t tempSpeed = 0;
  std::string tempFormFactor = "";
  std::string tempManufacturer = "";
  std::string tempPart = "";
  std::string tempSerial = "";
  float tempVoltageConfigured = 0;
  float tempVoltageMin = 0;
  float tempVoltageMax = 0;

  for (std::size_t i = 0; i < allChips.size(); ++i)
  {
    tempSize = !allChips[i]["Capacity"].empty() ? std::stoull(allChips[i]["Capacity"]) / pow(1024, 3) * pow(1000, 3) : 0;
    (*total) += tempSize;
    tempBank = !allChips[i]["BankLabel"].empty() ? allChips[i]["BankLabel"] : allChips[i]["DeviceLocator"];
    tempType = memoryTypes[std::stoi(allChips[i]["MemoryType"])];
    tempSpeed = !allChips[i]["ConfiguredClockSpeed"].empty() ? std::stoull(allChips[i]["ConfiguredClockSpeed"]) : !allChips[i]["Speed"].empty() ? std::stoull(allChips[i]["Speed"]) : 0;
    tempSpeed *= pow(10, 6);
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
* @brief Fills in the RAMList information for Linux systems
*/
void RAMList::GetLux()
{
  std::vector<std::string> lines;
  std::string line;
  std::string key;
  std::string val;
  RAM tempChip;
  std::uint64_t tempSize = 0;
  std::string tempBank = "";
  std::string tempType = "";
  std::uint64_t tempSpeed = 0;
  std::string tempFormFactor = "";
  std::string tempManufacturer = "";
  std::string tempPart = "";
  std::string tempSerial = "";
  float tempVoltageConfigured = 0;
  float tempVoltageMin = 0;
  float tempVoltageMax = 0;
  splitStringVector(runCommand("export LC_ALL=C; dmidecode -t memory 2>/dev/null | grep -iE \"Size:|Type|Speed|Manufacturer|Form Factor|Locator|Memory Device|Serial Number|Voltage|Part Number\"; unset LC_ALL"), "\n", &lines);

  if (lines.size() <= 1)
  {
    return;
  }

  for (std::size_t i = 3; i < lines.size(); ++i)
  {
    // While in range and NOT starting a new RAM chip
    while (i < lines.size() && !startswith(lines[i], "Handle 0x"))
    {
      line = trim(lines[++i]);
      // Residual header for new RAM chip
      if (startswith(line, "Memory Device"))
      {
        continue;
      }
      // No module in the slot, skip it
      if (endswith(line, "No Module Installed"))
      {
        break;
      }

      splitKeyValuePair(line, &key, &val);

      if (key == "Size")
      {
        tempSize = std::stoull(val.substr(0, val.size() - 3));
        tempSize *= pow(1024, endswith(val, "MB") ? 2 : 3);
        (*total) += tempSize;
      }
      if (key == "Locator")
      {
        tempBank = val;
      }
      if (key == "Type")
      {
        tempType = val;
      }
      if (key == "Speed")
      {
        tempSpeed = std::stoull(val.substr(0, val.size() - 4)) * pow(1024, 2);
      }
      if (key == "Form Factor")
      {
        tempFormFactor = val;
      }
      if (key == "Manufacturer")
      {
        tempManufacturer = val;
      }
      if (key == "Part Number")
      {
        tempPart = val;
      }
      if (key == "Serial Number")
      {
        tempSerial = val;
      }
    }

    // New RAM chip beginning
    if (startswith(lines[i], "Handle 0x") && tempManufacturer != "FFFFFFFFFFFF")
    {
      tempChip = (new RAM(tempSize, tempBank, tempType, tempSpeed, tempFormFactor, tempManufacturer, tempPart, tempSerial, tempVoltageConfigured, tempVoltageMin, tempVoltageMax));
      chips->push_back(tempChip);
    }
  }
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new RAM object
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
* @brief Sets equal two RAM objects
*
* @param o The RAM object to copy from
*/
void RAMList::operator=(const RAMList &o)
{
  if (&o == this)
  {
    return;
  }
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*o.chips);
  (*total) = (*o.total);
}

/**
* @brief Sets equal two RAM objects
*
* @param o The RAM object to copy from
*/
void RAMList::operator=(RAMList *o)
{
  chips = std::make_unique<std::vector<RAM>>();
  total = std::make_unique<std::uint64_t>(0);

  (*chips) = (*o->chips);
  (*total) = (*o->total);
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
