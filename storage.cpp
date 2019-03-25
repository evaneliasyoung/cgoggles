/**
*  @file      storage.cpp
*  @brief     The implementation for the storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storage.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
Storage::Storage()
{
  caption = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();

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
  default:
    break;
  }
}

Storage::~Storage()
{
  caption.reset();
  filesystem.reset();
  used.reset();
  total.reset();
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the storage information for Darwin systems
*/
void Storage::GetMac()
{
}

/**
* @brief Fills in the storage information for Windows systems
*/
void Storage::GetWin()
{
  std::unique_ptr<std::string> wmic = std::make_unique<std::string>(getWmicPath());
  std::unique_ptr<std::vector<std::map<std::string, std::string>>> drives = std::make_unique<std::vector<std::map<std::string, std::string>>>(runListMultiWmic("logicaldisk get Caption,FileSystem,FreeSpace,Size", wmic.get()));
  std::unique_ptr<std::string> temp = std::make_unique<std::string>();

  (*drives)
}

/**
* @brief Fills in the storage information for Linux systems
*/
void Storage::GetLux()
{
}
#pragma endregion

#pragma region "Accessors"
std::string Storage::Caption()
{
  return (*caption);
}

std::string Storage::FileSystem()
{
  return (*filesystem);
}

std::uint64_t Storage::Used()
{
  return (*used);
}

std::uint64_t Storage::Total()
{
  return (*total);
}
#pragma endregion "Accessors"
