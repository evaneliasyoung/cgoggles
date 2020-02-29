/**
*  @file      fs.cpp
*  @brief     The implementation for the FileSystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
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
  fs = "";
  type = "";
  size = 0;
  used = 0;
  mount = "";
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
  fs = f;
  type = tp;
  size = sz;
  used = us;
  mount = mnt;
}

/**
* @brief Construct a new FileSystem object from another FileSystem object
*
* @param o The FileSystem object to copy from
*/
FileSystem::FileSystem(const FileSystem &o)
{
  fs = o.fs;
  type = o.type;
  size = o.size;
  used = o.used;
  mount = o.mount;
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

  fs = o.fs;
  type = o.type;
  size = o.size;
  used = o.used;
  mount = o.mount;
}

/**
* @brief Sets equal two fs objects
*
* @param o The fs object to copy from
*/
void FileSystem::operator=(FileSystem *o)
{
  fs = o->fs;
  type = o->type;
  size = o->size;
  used = o->used;
  mount = o->mount;
}
#pragma endregion "Operators"
