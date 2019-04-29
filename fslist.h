/**
*  @file      fslist.h
*  @brief     The interface for the FileSystemList class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_FSLIST_H_
#define CGOGGLES_FSLIST_H_

#include "pch.h"
#include "fs.h"

/**
* @brief Represents a computer's collection of FileSystem objects
*/
class FileSystemList
{
private:
  std::unique_ptr<std::vector<FileSystem>> fsList;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  FileSystemList();
  FileSystemList(std::uint8_t plt);
  FileSystemList(const FileSystemList &o);
  ~FileSystemList();
  void *operator new(std::size_t size);
  void operator=(const FileSystemList &o);
  void operator=(FileSystemList *o);
  std::vector<FileSystem> FileSystems();
};

#endif // CGOGGLES_FSLIST_H_
