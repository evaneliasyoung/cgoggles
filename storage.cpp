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
