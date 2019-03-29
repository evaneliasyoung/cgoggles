/**
*  @file      storage.h
*  @brief     The interface for the storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-28
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_STORAGE_H_
#define CGOGGLES_STORAGE_H_

#include "pch.h"

class Storage
{
private:
  std::unique_ptr<std::string> name;
  std::unique_ptr<std::string> identifier;
  std::unique_ptr<std::string> type;
  std::unique_ptr<std::string> filesystem;
  std::unique_ptr<std::string> mount;
  std::unique_ptr<std::uint64_t> used;
  std::unique_ptr<std::uint64_t> total;
  std::unique_ptr<std::string> physical;
  std::unique_ptr<std::string> uuid;
  std::unique_ptr<std::string> label;
  std::unique_ptr<std::string> model;
  std::unique_ptr<std::string> serial;
  std::unique_ptr<bool> removable;
  std::unique_ptr<std::string> protocol;

  void GetMac();
  void GetWin();
  void GetLux();

public:
  Storage();
  Storage(std::string nm, std::string id, std::string tp, std::string fs, std::string mnt, std::uint64_t us, std::uint64_t ttl, std::string psy, std::string uid, std::string lbl, std::string mdl, std::string srl, bool rmv, std::string prt);
  Storage(const Storage &s);
  ~Storage();
  void *operator new(std::size_t size);
  void operator=(const Storage &s);
  void operator=(Storage *s);
  std::string Name();
  std::string Identifier();
  std::string Type();
  std::string FileSystem();
  std::string Mount();
  std::uint64_t Used();
  std::uint64_t Total();
  std::string Physical();
  std::string UUID();
  std::string Label();
  std::string Model();
  std::string Serial();
  bool Removable();
  std::string Protocol();
};

#endif // CGOGGLES_STORAGE_H_
