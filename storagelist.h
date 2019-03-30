/**
*  @file      storagelist.h
*  @brief     The interface for the storagelist class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_STORAGELIST_H_
#define CGOGGLES_STORAGELIST_H_

#include "pch.h"
#include "storage.h"

class StorageList
{
private:
  std::unique_ptr<std::vector<Storage>> drives;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  StorageList();
  StorageList(std::uint8_t plt);
  StorageList(const StorageList &s);
  ~StorageList();
  void *operator new(std::size_t size);
  void operator=(const StorageList &s);
  void operator=(StorageList *s);
  std::vector<Storage> Drives();
};

#endif // CGOGGLES_STORAGELIST_H_
