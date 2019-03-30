/**
*  @file      fs.cpp
*  @brief     The implementation for the fs class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-03-30
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "fs.h"
#include "utils.h"

#pragma region "Contructors"
FileSystem::FileSystem()
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();
}

FileSystem::FileSystem(std::string f, std::string tp, std::uint64_t sz, std::uint64_t us, std::string mnt)
{
  fs = std::make_unique<std::string>(f);
  type = std::make_unique<std::string>(tp);
  size = std::make_unique<std::uint64_t>(sz);
  used = std::make_unique<std::uint64_t>(us);
  mount = std::make_unique<std::string>(mnt);
}

FileSystem::FileSystem(const FileSystem &s)
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*s.fs);
  (*type) = (*s.type);
  (*size) = (*s.size);
  (*used) = (*s.used);
  (*mount) = (*s.mount);
}

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
* @param v The fs object to copy from
*/
void FileSystem::operator=(const FileSystem &s)
{
  if (&s == this)
  {
    return;
  }
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*s.fs);
  (*type) = (*s.type);
  (*size) = (*s.size);
  (*used) = (*s.used);
  (*mount) = (*s.mount);
}

/**
* @brief Sets equal two fs objects
*
* @param v The fs object to copy from
*/
void FileSystem::operator=(FileSystem *s)
{
  fs = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  size = std::make_unique<std::uint64_t>();
  used = std::make_unique<std::uint64_t>();
  mount = std::make_unique<std::string>();

  (*fs) = (*s->fs);
  (*type) = (*s->type);
  (*size) = (*s->size);
  (*used) = (*s->used);
  (*mount) = (*s->mount);
}
#pragma endregion "Operators"

#pragma region "Accessors"
std::string FileSystem::FS()
{
  return (*fs);
}

std::string FileSystem::Type()
{
  return (*type);
}

std::uint64_t FileSystem::Size()
{
  return (*size);
}

std::uint64_t FileSystem::Used()
{
  return (*used);
}

std::string FileSystem::Mount()
{
  return (*mount);
}
#pragma endregion "Accessors"
