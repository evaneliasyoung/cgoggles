/**
*  @file      storage.h
*  @brief     The interface for the Storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_STORAGE_H_
#define CGOGGLES_STORAGE_H_

#include "pch.h"

/**
* @brief Represents a computer's storage drive
*/
class Storage
{
public:
  Storage();
  Storage(std::string nm, std::string id, std::string tp, std::string fs, std::string mnt, std::uint64_t ttl, std::string psy, std::string uid, std::string lbl, std::string mdl, std::string srl, bool rmv, std::string prt);
  Storage(const Storage &o);
  void *operator new(std::size_t size);
  void operator=(const Storage &o);
  void operator=(Storage *o);
  std::string name;
  std::string identifier;
  std::string type;
  std::string filesystem;
  std::string mount;
  std::uint64_t total;
  std::string physical;
  std::string uuid;
  std::string label;
  std::string model;
  std::string serial;
  bool removable;
  std::string protocol;
};

#endif // CGOGGLES_STORAGE_H_
