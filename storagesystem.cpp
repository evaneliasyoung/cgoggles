/**
*  @file      storagesystem.cpp
*  @brief     The implementation for the storagesystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-28
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storagesystem.h"
#include "storage.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
StorageSystem::StorageSystem()
{
  drives = std::make_unique<std::vector<Storage>>();
}

StorageSystem::StorageSystem(std::uint8_t plt)
{
  drives = std::make_unique<std::vector<Storage>>();

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

StorageSystem::StorageSystem(const StorageSystem &s)
{
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*s.drives);
}

StorageSystem::~StorageSystem()
{
  drives.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the storage system information for Darwin systems
*/
void StorageSystem::GetMac()
{
  std::vector<std::string> eachDrive;
  std::vector<std::string> allDrives;
  Storage tempDrive;
  std::string line;
  std::string key;
  std::string val;
  std::string tempName = "";
  std::string tempIdentifier = "";
  std::string tempType = "disk";
  std::string tempFilesystem = "";
  std::string tempMount = "";
  std::uint64_t tempUsed = 0;
  std::uint64_t tempTotal = 0;
  std::string tempPhysical = "HDD";
  std::string tempUuid = "";
  std::string tempLabel = "";
  std::string tempModel = "";
  std::string tempSerial = "";
  bool tempRemovable = false;
  std::string tempProtocol = "";

  splitStringVector(runCommand("diskutil info -all"), "**********", &allDrives);

  for (std::size_t i = 0; i < allDrives.size(); i++)
  {
    tempName = "";
    tempIdentifier = "";
    tempType = "disk";
    tempFilesystem = "";
    tempMount = "";
    tempUsed = 0;
    tempTotal = 0;
    tempPhysical = "HDD";
    tempUuid = "";
    tempLabel = "";
    tempModel = "";
    tempSerial = "";
    tempRemovable = false;
    tempProtocol = "";
    splitStringVector(allDrives[i], "\n", &eachDrive);

    for (std::size_t j = 0; j < eachDrive.size(); j++)
    {
      line = trim(eachDrive[j]);
      key = trim(line.substr(0, line.find(':')));
      val = trim(line.substr(line.find(':') + 1));
      std::transform(key.begin(), key.end(), key.begin(), toupper);

      if (key == "DEVICE IDENTIFIER")
      {
        tempIdentifier = val;
      }
      else if (key == "DEVICE NODE")
      {
        tempName = val;
      }
      else if (key == "VOLUME NAME")
      {
        if (val.substr(0, 14) != "Not applicable")
        {
          tempLabel = val;
        }
      }
      else if (key == "PROTOCOL")
      {
        tempProtocol = val;
      }
      else if (key == "DISK SIZE")
      {
        tempTotal = std::stoull(trim(val.substr(val.find_first_of("(") + 1, (val.find_first_of("(") + val.find_first_of("B")) - 3)));
      }
      else if (key == "FILE SYSTEM PERSONALITY")
      {
        tempFilesystem = val;
      }
      else if (key == "MOUNT POINT")
      {
        tempMount = val;
      }
      else if (key == "VOLUME UUID")
      {
        tempUuid = val;
      }
      else if (key == "READ-ONLY MEDIA" && val == "Yes")
      {
        tempPhysical = "CD/DVD";
      }
      else if (key == "SOLIDSTATE" && val == "Yes")
      {
        tempPhysical = "SSD";
      }
      else if (key == "VIRTUAL")
      {
        tempType = "Virtual";
      }
      else if (key == "REMOVABLE MEDIA" && val == "Removable")
      {
        tempRemovable = true;
      }
      else if (key == "PARTITION TYPE")
      {
        tempType = "Part";
      }
      else if (key == "DEVICE / MEDIA NAME")
      {
        tempModel = val;
      }
    }
    tempDrive = (new Storage(tempName, tempIdentifier, tempType, tempFilesystem, tempMount, tempUsed, tempTotal, tempPhysical, tempUuid, tempLabel, tempModel, tempSerial, tempRemovable, tempProtocol));
    drives->push_back(tempDrive);
    break;
  }
}

/**
* @brief Fills in the storage system information for Windows systems
*/
void StorageSystem::GetWin()
{
  std::string wmic = getWmicPath();
}

/**
* @brief Fills in the storage system information for Linux systems
*/
void StorageSystem::GetLux()
{
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new Storage System object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *StorageSystem::operator new(std::size_t size)
{
  void *o = ::new (StorageSystem);
  return o;
}

/**
* @brief Sets equal two Storage System objects
*
* @param v The Storage System object to copy from
*/
void StorageSystem::operator=(const StorageSystem &s)
{
  if (&s == this)
  {
    return;
  }
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*s.drives);
}

/**
* @brief Sets equal two Storage System objects
*
* @param v The Storage System object to copy from
*/
void StorageSystem::operator=(StorageSystem *s)
{
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*s->drives);
}
#pragma endregion "Operators"
