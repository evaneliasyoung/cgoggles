/**
*  @file      storagelist.cpp
*  @brief     The implementation for the StorageList class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storagelist.h"
#include "storage.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new StorageList object
*/
StorageList::StorageList()
{
  drives = std::make_unique<std::vector<Storage>>();
}

/**
* @brief Construct a new StorageList object with help from the assistants
*
* @param plt The platform of the system
*/
StorageList::StorageList(std::uint8_t plt)
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

/**
* @brief Construct a new StorageList object from another StorageList object
*
* @param o The StorageList object to copy from
*/
StorageList::StorageList(const StorageList &o)
{
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*o.drives);
}

/**
* @brief Destroy the StorageList object
*/
StorageList::~StorageList()
{
  drives.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the StorageList information for Darwin systems
*/
void StorageList::GetMac()
{
  std::vector<std::string> eachDrive;
  std::vector<std::string> allDrives;
  Storage tempDrive;
  std::string key;
  std::string val;
  std::string tempName = "";
  std::string tempIdentifier = "";
  std::string tempType = "Disk";
  std::string tempFilesystem = "";
  std::string tempMount = "";
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
    tempType = "Disk";
    tempFilesystem = "";
    tempMount = "";
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
      splitKeyValuePair(eachDrive[j], &key, &val);
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
    tempDrive = (new Storage(tempName, tempIdentifier, tempType, tempFilesystem, tempMount, tempTotal, tempPhysical, tempUuid, tempLabel, tempModel, tempSerial, tempRemovable, tempProtocol));
    drives->push_back(tempDrive);
  }
}

/**
* @brief Fills in the StorageList information for Windows systems
*/
void StorageList::GetWin()
{
  std::string wmic = getWmicPath();
  std::vector<std::string> eachDrive;
  std::vector<std::map<std::string, std::string>> allDrives = runListMultiWmic("logicaldisk get Caption, DriveType, FileSystem, Name, Size, VolumeName, VolumeSerialNumber", &wmic);
  std::string driveTypes[7] = {"Unknown", "NoRoot", "Removable", "Local", "Network", "CD/DVD", "RAM"};
  Storage tempDrive;
  std::string tempName = "";
  std::string tempIdentifier = "";
  std::string tempType = "Disk";
  std::string tempFilesystem = "";
  std::string tempMount = "";
  std::uint64_t tempTotal = 0;
  std::string tempPhysical = "HDD";
  std::string tempUuid = "";
  std::string tempLabel = "";
  std::string tempModel = "";
  std::string tempSerial = "";
  bool tempRemovable = false;
  std::string tempProtocol = "";

  for (std::size_t i = 0; i < allDrives.size(); i++)
  {
    if ((allDrives[i]["DriveType"] == ""))
    {
      continue;
    }

    tempName = allDrives[i]["Name"];
    tempIdentifier = allDrives[i]["Caption"];
    tempFilesystem = allDrives[i]["FileSystem"];
    tempMount = allDrives[i]["Caption"];
    tempTotal = allDrives[i]["Size"] == "" ? 0 : std::stoull(allDrives[i]["Size"]) / pow(1024, 3) * pow(10, 9);
    tempPhysical = std::uint32_t(std::stoi(allDrives[i]["DriveType"])) <= 6 ? driveTypes[std::stoi(allDrives[i]["DriveType"])] : driveTypes[0];
    tempUuid = allDrives[i]["VolumeSerialNumber"];
    tempLabel = allDrives[i]["VolumeName"] == "" ? allDrives[i]["Caption"] : allDrives[i]["VolumeName"];
    tempSerial = allDrives[i]["VolumeSerialNumber"];
    tempRemovable = allDrives[i]["DriveType"] == "2";

    tempDrive = (new Storage(tempName, tempIdentifier, tempType, tempFilesystem, tempMount, tempTotal, tempPhysical, tempUuid, tempLabel, tempModel, tempSerial, tempRemovable, tempProtocol));
    drives->push_back(tempDrive);
  }
}

/**
* @brief Fills in the StorageList information for Linux systems
*/
void StorageList::GetLux()
{
  std::vector<std::string> eachDrive;
  std::vector<std::string> allDrives;
  std::map<std::string, std::string> dataMap;
  Storage tempDrive;
  std::string line;
  std::string key;
  std::string val;
  std::string tempName = "";
  std::string tempIdentifier = "";
  std::string tempType = "Disk";
  std::string tempFilesystem = "";
  std::string tempMount = "";
  std::uint64_t tempTotal = 0;
  std::string tempPhysical = "HDD";
  std::string tempUuid = "";
  std::string tempLabel = "";
  std::string tempModel = "";
  std::string tempSerial = "";
  bool tempRemovable = false;
  std::string tempProtocol = "";

  splitStringVector(runCommand("lsblk -bPo NAME,TYPE,SIZE,FSTYPE,MOUNTPOINT,UUID,ROTA,RO,RM,TRAN,SERIAL,LABEL,MODEL,OWNER"), "\n", &allDrives);
  for (std::size_t i = 0; i < allDrives.size(); i++)
  {
    dataMap.clear();                // Reset the data collection
    if (trim(allDrives[i]).empty()) // If the line is empty, skip
    {
      continue;
    }

    splitStringVector(allDrives[i], R"(" )", &eachDrive);
    for (std::size_t j = 0; j < eachDrive.size(); j++)
    {
      splitKeyValuePair(std::regex_replace(eachDrive[j], std::regex(R"(")"), ""), &key, &val, true, '=');
      dataMap[key] = val;
    }

    tempName = tryGetValue<std::string, std::string>(dataMap, "NAME", &val) ? val : "";
    tempType = tryGetValue<std::string, std::string>(dataMap, "TYPE", &val) ? val : "Unknown";
    tempFilesystem = tryGetValue<std::string, std::string>(dataMap, "FSTYPE", &val) ? val : "Unknown";
    tempMount = tryGetValue<std::string, std::string>(dataMap, "MOUNTPOINT", &val) ? val : "";
    tempLabel = tryGetValue<std::string, std::string>(dataMap, "LABEL", &val) ? val : "";
    tempUuid = tryGetValue<std::string, std::string>(dataMap, "UUID", &val) ? val : "";
    tempModel = tryGetValue<std::string, std::string>(dataMap, "MODEL", &val) ? val : "";
    tempSerial = tryGetValue<std::string, std::string>(dataMap, "SERIAL", &val) ? val : "";
    tempRemovable = tryGetValue<std::string, std::string>(dataMap, "RM", &val) && val == "1";
    tempProtocol = tryGetValue<std::string, std::string>(dataMap, "TRAN", &val) ? val : "";
    if (tryGetValue<std::string, std::string>(dataMap, "ROTA", &val))
    {
      tempPhysical = tempType == "disk" ? (val == "0" ? "SSD" : "HDD") : (tempType == "rom" ? "CD/DVD" : "");
    }

    if (tryGetValue<std::string, std::string>(dataMap, "SIZE", &val))
    {
      if (val.empty())
      {
        tempTotal = 0;
      }
      else
      {
        tempTotal = std::stof(val);
      }
    }

    tempDrive = (new Storage(tempName, tempIdentifier, tempType, tempFilesystem, tempMount, tempTotal, tempPhysical, tempUuid, tempLabel, tempModel, tempSerial, tempRemovable, tempProtocol));
    drives->push_back(tempDrive);
  }
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new Storage System object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *StorageList::operator new(std::size_t size)
{
  void *o = ::new (StorageList);
  return o;
}

/**
* @brief Sets equal two Storage System objects
*
* @param o The Storage System object to copy from
*/
void StorageList::operator=(const StorageList &o)
{
  if (&o == this)
  {
    return;
  }
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*o.drives);
}

/**
* @brief Sets equal two Storage System objects
*
* @param o The Storage System object to copy from
*/
void StorageList::operator=(StorageList *o)
{
  drives = std::make_unique<std::vector<Storage>>();

  (*drives) = (*o->drives);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns the a copy of the storage list
*
* @return std::vector<Storage> The storage list
*/
std::vector<Storage> StorageList::Drives()
{
  return (*drives);
}
#pragma endregion "Accessors"
