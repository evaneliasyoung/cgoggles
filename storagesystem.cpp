/**
*  @file      storagesystem.cpp
*  @brief     The implementation for the storagesystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storagesystem.h"
#include "storage.h"
#include "os.h"

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
}

/**
* @brief Fills in the storage system information for Windows systems
*/
void StorageSystem::GetWin()
{
  std::string wmic = getWmicPath();
  std::vector<std::map<std::string, std::string>> tempDrs = runListMultiWmic("logicaldisk get Caption,FileSystem,FreeSpace,Size", &wmic);
  std::string temp;
  Storage tempSto;

  for (std::size_t i = 0; i < tempDrs.size(); i++)
  {
    tempSto = Storage(tempDrs[i]["Caption"],
                      tempDrs[i]["FileSystem"],
                      (tempDrs[i]["FreeSpace"].empty() ? 0 : std::stoull(tempDrs[i]["FreeSpace"])),
                      (tempDrs[i]["Size"].empty() ? 0 : std::stoull(tempDrs[i]["FreeSpace"])));
    drives->push_back(tempSto);
  }
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
