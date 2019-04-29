/**
*  @file      fs.h
*  @brief     The interface for the FileSystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_FS_H_
#define CGOGGLES_FS_H_

#include "pch.h"

/**
* @brief Represents a computer's file system
*/
class FileSystem
{
private:
  std::unique_ptr<std::string> fs;
  std::unique_ptr<std::string> type;
  std::unique_ptr<std::uint64_t> size;
  std::unique_ptr<std::uint64_t> used;
  std::unique_ptr<std::string> mount;

public:
  FileSystem();
  FileSystem(std::string f, std::string tp, std::uint64_t sz, std::uint64_t us, std::string mnt);
  FileSystem(const FileSystem &o);
  ~FileSystem();
  void *operator new(std::size_t size);
  void operator=(const FileSystem &o);
  void operator=(FileSystem *o);
  std::string FS();
  std::string Type();
  std::uint64_t Size();
  std::uint64_t Used();
  std::string Mount();
};

#endif // CGOGGLES_FS_H_
