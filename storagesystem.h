/**
*  @file      storagesystem.h
*  @brief     The interface for the storagesystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_STORAGESYSTEM_H_
#define CGOGGLES_STORAGESYSTEM_H_

#include "pch.h"
#include "storage.h"

class StorageSystem
{
private:
  std::unique_ptr<std::vector<Storage>> drives;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  StorageSystem();
  StorageSystem(std::uint8_t plt);
  StorageSystem(const StorageSystem &s);
  ~StorageSystem();
  void *operator new(std::size_t size);
  void operator=(const StorageSystem &s);
  void operator=(StorageSystem *s);
};

#endif // CGOGGLES_STORAGESYSTEM_H_
