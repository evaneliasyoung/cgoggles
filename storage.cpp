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
}

Storage::Storage(std::string cpt, std::string fs, std::uint64_t use, std::uint64_t tot)
{
  caption = std::make_unique<std::string>(cpt);
  filesystem = std::make_unique<std::string>(fs);
  used = std::make_unique<std::uint64_t>(use);
  total = std::make_unique<std::uint64_t>(tot);
}

Storage::Storage(const Storage &s)
{
  caption = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();

  (*caption) = (*s.caption);
  (*filesystem) = (*s.filesystem);
  (*used) = (*s.used);
  (*total) = (*s.total);
}

Storage::~Storage()
{
  caption.reset();
  filesystem.reset();
  used.reset();
  total.reset();
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new Storage object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Storage::operator new(std::size_t size)
{
  void *o = ::new (Storage);
  return o;
}

/**
* @brief Sets equal two Storage objects
*
* @param v The Storage object to copy from
*/
void Storage::operator=(const Storage &s)
{
  if (&s == this)
  {
    return;
  }
  caption = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();

  (*caption) = (*s.caption);
  (*filesystem) = (*s.filesystem);
  (*used) = (*s.used);
  (*total) = (*s.total);
}

/**
* @brief Sets equal two Storage objects
*
* @param v The Storage object to copy from
*/
void Storage::operator=(Storage *s)
{
  caption = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();

  (*caption) = (*s->caption);
  (*filesystem) = (*s->filesystem);
  (*used) = (*s->used);
  (*total) = (*s->total);
}
#pragma endregion "Operators"

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

#pragma region "Static Methods"
/**
* @brief Fills in the storage information for Darwin systems
*/
std::vector<Storage> getStorageMac()
{
}

/**
* @brief Fills in the storage information for Windows systems
*/
std::vector<Storage> getStorageWin()
{
  std::unique_ptr<std::string> wmic = std::make_unique<std::string>(getWmicPath());
  std::unique_ptr<std::vector<std::map<std::string, std::string>>> drives = std::make_unique<std::vector<std::map<std::string, std::string>>>(runListMultiWmic("logicaldisk get Caption,FileSystem,FreeSpace,Size", wmic.get()));
  std::unique_ptr<std::string> temp = std::make_unique<std::string>();
  std::unique_ptr<Storage> tempSto = std::make_unique<Storage>();
  std::unique_ptr<std::vector<Storage>> ret = std::make_unique<std::vector<Storage>>();

  for (std::size_t i = 0; i < drives->size(); i++)
  {
    (*tempSto) = Storage((*drives)[i]["Caption"],
                         (*drives)[i]["FileSystem"],
                         ((*drives)[i]["FreeSpace"].empty() ? 0 : std::stoull((*drives)[i]["FreeSpace"])),
                         ((*drives)[i]["Size"].empty() ? 0 : std::stoull((*drives)[i]["FreeSpace"])));
    ret->push_back(*tempSto);
  }

  return (*ret);
}

/**
* @brief Fills in the storage information for Linux systems
*/
std::vector<Storage> getStorageLux()
{
}

std::vector<Storage> getStorage(std::uint8_t plt)
{
  switch (plt)
  {
  case OS_WIN:
    return getStorageWin();
  case OS_MAC:
    return getStorageMac();
  case OS_LUX:
    return getStorageLux();
  }
}
#pragma endregion "Static Methods"
