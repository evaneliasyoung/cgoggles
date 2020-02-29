/**
*  @file      ramlist.h
*  @brief     The interface for the RAMList class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_RAMLIST_H_
#define CGOGGLES_RAMLIST_H_

#include "pch.h"
#include "ram.h"

/**
* @brief Represents a computer's collection of RAM objects
*/
class RAMList
{
private:
  void GetMac();
  void GetWin();
  void GetLux();

public:
  RAMList();
  RAMList(std::uint8_t plt);
  RAMList(const RAMList &o);
  void *operator new(std::size_t size);
  void operator=(const RAMList &o);
  void operator=(RAMList *o);
  std::vector<RAM> chips;
  std::uint64_t total;
};

#endif // CGOGGLES_RAMLIST_H_
