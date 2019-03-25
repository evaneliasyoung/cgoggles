/**
*  @file      storage.h
*  @brief     The implementation for the storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_STORAGE_H_
#define CGOGGLES_STORAGE_H_

#include "pch.h"

class Storage
{
private:
  std::unique_ptr<std::string> caption;
  std::unique_ptr<std::string> filesystem;
  std::unique_ptr<std::uint64_t> used;
  std::unique_ptr<std::uint64_t> total;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  Storage();
  ~Storage();
  std::string Caption();
  std::string FileSystem();
  std::uint64_t Used();
  std::uint64_t Total();
};

#endif // CGOGGLES_STORAGE_H_
