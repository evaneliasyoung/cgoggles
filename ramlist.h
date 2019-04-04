/**
*  @file      ramlist.h
*  @brief     The interface for the ramlist class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2019-04-04
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_RAMLIST_H_
#define CGOGGLES_RAMLIST_H_

#include "pch.h"
#include "ram.h"

class RAMList
{
private:
  std::unique_ptr<std::vector<RAM>> chips;
  std::unique_ptr<std::uint64_t> total;

  void GetMac();
  void GetWin();
  void GetLux();

public:
  RAMList();
  RAMList(std::uint8_t plt);
  RAMList(const RAMList &s);
  ~RAMList();
  void *operator new(std::size_t size);
  void operator=(const RAMList &s);
  void operator=(RAMList *s);
  std::vector<RAM> Chips();
  std::uint64_t Total();
};

#endif // CGOGGLES_RAMLIST_H_
