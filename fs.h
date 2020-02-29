/**
*  @file      fs.h
*  @brief     The interface for the FileSystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_FS_H_
#define CGOGGLES_FS_H_

#include "pch.h"
#include "utils.h"

extern OutputStyle style;
extern bool pretty;

/**
* @brief Represents a computer's file system
*/
class FileSystem
{
public:
  FileSystem();
  FileSystem(std::string f, std::string tp, std::uint64_t sz, std::uint64_t us, std::string mnt);
  FileSystem(const FileSystem &o);
  void *operator new(std::size_t size);
  void operator=(const FileSystem &o);
  void operator=(FileSystem *o);
  std::string fs;
  std::string type;
  std::uint64_t size;
  std::uint64_t used;
  std::string mount;
};

#endif // CGOGGLES_FS_H_
