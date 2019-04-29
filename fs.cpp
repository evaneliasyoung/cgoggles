/**
*  @file      fs.cpp
*  @brief     The implementation for the FileSystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "fs.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new FileSystem object
*/
FileSystem::FileSystem()
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();
}

/**
* @brief Construct a new FileSystem object
*
* @param f   The filesystem
* @param tp  The type
* @param sz  The total storage
* @param us  The used storage
* @param mnt The mount-point
*/
FileSystem::FileSystem(std::string f, std::string tp, std::uint64_t sz, std::uint64_t us, std::string mnt)
{
  fs = std::make_unique<std::string>(f);
  type = std::make_unique<std::string>(tp);
  size = std::make_unique<std::uint64_t>(sz);
  used = std::make_unique<std::uint64_t>(us);
  mount = std::make_unique<std::string>(mnt);
}

/**
* @brief Construct a new FileSystem object from another FileSystem object
*
* @param o The FileSystem object to copy from
*/
FileSystem::FileSystem(const FileSystem &o)
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*o.fs);
  (*type) = (*o.type);
  (*size) = (*o.size);
  (*used) = (*o.used);
  (*mount) = (*o.mount);
}

/**
* @brief Destroy the FileSystem object
*/
FileSystem::~FileSystem()
{
  fs.reset();
  type.reset();
  size.reset();
  used.reset();
  mount.reset();
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new fs object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *FileSystem::operator new(std::size_t size)
{
  void *o = ::new (FileSystem);
  return o;
}

/**
* @brief Sets equal two fs objects
*
* @param o The fs object to copy from
*/
void FileSystem::operator=(const FileSystem &o)
{
  if (&o == this)
  {
    return;
  }
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*o.fs);
  (*type) = (*o.type);
  (*size) = (*o.size);
  (*used) = (*o.used);
  (*mount) = (*o.mount);
}

/**
* @brief Sets equal two fs objects
*
* @param o The fs object to copy from
*/
void FileSystem::operator=(FileSystem *o)
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*o->fs);
  (*type) = (*o->type);
  (*size) = (*o->size);
  (*used) = (*o->used);
  (*mount) = (*o->mount);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the FS
*
* @return std::string A copy of the FS
*/
std::string FileSystem::FS()
{
  return (*fs);
}

/**
* @brief Returns a copy of the type
*
* @return std::string A copy of the type
*/
std::string FileSystem::Type()
{
  return (*type);
}
/**
* @brief Returns a copy of the total size
*
* @return std::uint64_t A copy of the total size
*/

std::uint64_t FileSystem::Size()
{
  return (*size);
}

/**
* @brief Returns a copy of the used size
*
* @return std::uint64_t A copy of the used size
*/
std::uint64_t FileSystem::Used()
{
  return (*used);
}

/**
* @brief Returns a copy of the model
*
* @return std::string A copy of the model
*/
std::string FileSystem::Mount()
{
  return (*mount);
}
#pragma endregion "Accessors"
