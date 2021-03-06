/**
*  @file      fslist.cpp
*  @brief     The implementation for the FileSystemList class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "fslist.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new FileSystemList object
*/
FileSystemList::FileSystemList()
{
  fsList = std::vector<FileSystem>();
}

/**
* @brief Construct a new FileSystemList object with help from the assistants
*
* @param plt The platform of the system
*/
FileSystemList::FileSystemList(std::uint8_t plt)
{
  fsList = std::vector<FileSystem>();

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

/**
* @brief Construct a new FileSystemList object from another FileSystemList object
*
* @param o The FileSystemList object to copy from
*/
FileSystemList::FileSystemList(const FileSystemList &o)
{
  fsList = std::vector<FileSystem>();

  fsList = o.fsList;
}
#pragma endregion "Contructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the storage list information for Darwin systems
*/
void FileSystemList::GetMac()
{
  std::vector<std::string> eachFS;
  std::vector<std::string> allFS;
  FileSystem tempFileSystem;
  std::string tempFS = "";
  std::string tempType = "";
  std::uint64_t tempSize = 0;
  std::uint64_t tempUsed = 0;
  std::string tempMount = "";

  splitStringVector(runCommand("df -lkP | grep ^/"), "\n", &allFS);

  for (std::size_t i = 0; i < allFS.size(); ++i)
  {
    if (allFS[i] == "")
    {
      break;
    }
    splitStringVector(std::regex_replace(allFS[i], std::regex(R"(  +)"), " "), " ", &eachFS);
    tempFS = eachFS[0];
    tempType = "HFS";
    tempSize = std::stoull(eachFS[1]) * 1024;
    tempUsed = std::stoull(eachFS[2]) * 1024;
    tempMount = eachFS[eachFS.size() - 1];

    tempFileSystem = FileSystem(tempFS, tempType, tempSize, tempUsed, tempMount);
    fsList.push_back(tempFileSystem);
  }
}

/**
* @brief Fills in the storage list information for Windows systems
*/
void FileSystemList::GetWin()
{
  std::string wmic = getWmicPath();
  std::vector<std::map<std::string, std::string>> allFS = runListMultiWmic("logicaldisk get Caption, FileSystem, FreeSpace, Size", &wmic);
  FileSystem tempFileSystem;
  std::string tempFS = "";
  std::string tempType = "";
  std::uint64_t tempSize = 0;
  std::uint64_t tempUsed = 0;
  std::string tempMount = "";

  for (std::size_t i = 0; i < allFS.size(); ++i)
  {
    tempFS = allFS[i]["Caption"];
    tempType = allFS[i]["FileSystem"];
    tempSize = allFS[i]["Size"] == "" ? 0 : std::stoull(allFS[i]["Size"]) / pow(1024, 3) * pow(10, 9);
    tempUsed = allFS[i]["FreeSpace"] == "" ? 0 : std::stoull(allFS[i]["FreeSpace"]);
    tempMount = allFS[i]["Caption"];

    tempFileSystem = FileSystem(tempFS, tempType, tempSize, tempUsed, tempMount);
    fsList.push_back(tempFileSystem);
  }
}

/**
* @brief Fills in the storage list information for Linux systems
*/
void FileSystemList::GetLux()
{
  std::vector<std::string> eachFS;
  std::vector<std::string> allFS;
  FileSystem tempFileSystem;
  std::string tempFS = "";
  std::string tempType = "";
  std::uint64_t tempSize = 0;
  std::uint64_t tempUsed = 0;
  std::string tempMount = "";

  splitStringVector(runCommand("df -lkP | grep ^/"), "\n", &allFS);

  for (std::size_t i = 0; i < allFS.size(); ++i)
  {
    if (allFS[i] == "")
    {
      break;
    }
    splitStringVector(std::regex_replace(allFS[i], std::regex(R"(  +)"), " "), " ", &eachFS);
    tempFS = eachFS[0];
    tempType = eachFS[1];
    tempSize = std::stoull(eachFS[2]) * 1000;
    tempUsed = std::stoull(eachFS[3]) * 1000;
    tempMount = eachFS[eachFS.size() - 1];

    tempFileSystem = FileSystem(tempFS, tempType, tempSize, tempUsed, tempMount);
    fsList.push_back(tempFileSystem);
  }
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new File System object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *FileSystemList::operator new(std::size_t size)
{
  void *o = ::new (FileSystemList);
  return o;
}

/**
* @brief Sets equal two File System objects
*
* @param o The File System object to copy from
*/
void FileSystemList::operator=(const FileSystemList &o)
{
  if (&o == this)
  {
    return;
  }
  fsList = std::vector<FileSystem>();

  fsList = o.fsList;
}

/**
* @brief Sets equal two File System objects
*
* @param o The File System object to copy from
*/
void FileSystemList::operator=(FileSystemList *o)
{
  fsList = std::vector<FileSystem>();

  fsList = o->fsList;
}
#pragma endregion "Operators"
