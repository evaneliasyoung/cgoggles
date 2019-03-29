/**
*  @file      storage.cpp
*  @brief     The implementation for the storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-03-28
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storage.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
Storage::Storage()
{
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();
  physical = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
  label = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  removable = std::make_unique<bool>();
  protocol = std::make_unique<std::string>();
}

Storage::Storage(std::string nm, std::string id, std::string tp, std::string fs, std::string mnt, std::uint64_t us, std::uint64_t ttl, std::string psy, std::string uid, std::string lbl, std::string mdl, std::string srl, bool rmv, std::string prt)
{
  name = std::make_unique<std::string>(nm);
  identifier = std::make_unique<std::string>(id);
  type = std::make_unique<std::string>(tp);
  filesystem = std::make_unique<std::string>(fs);
  mount = std::make_unique<std::string>(mnt);
  used = std::make_unique<std::uint64_t>(us);
  total = std::make_unique<std::uint64_t>(ttl);
  physical = std::make_unique<std::string>(psy);
  uuid = std::make_unique<std::string>(uid);
  label = std::make_unique<std::string>(lbl);
  model = std::make_unique<std::string>(mdl);
  serial = std::make_unique<std::string>(srl);
  removable = std::make_unique<bool>(rmv);
  protocol = std::make_unique<std::string>(prt);
}

Storage::Storage(const Storage &s)
{
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();
  physical = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
  label = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  removable = std::make_unique<bool>();
  protocol = std::make_unique<std::string>();

  (*name) = (*s.name);
  (*identifier) = (*s.identifier);
  (*type) = (*s.type);
  (*filesystem) = (*s.filesystem);
  (*mount) = (*s.mount);
  (*used) = (*s.used);
  (*total) = (*s.total);
  (*physical) = (*s.physical);
  (*uuid) = (*s.uuid);
  (*label) = (*s.label);
  (*model) = (*s.model);
  (*serial) = (*s.serial);
  (*removable) = (*s.removable);
  (*protocol) = (*s.protocol);
}

Storage::~Storage()
{
  name.reset();
  identifier.reset();
  type.reset();
  filesystem.reset();
  mount.reset();
  used.reset();
  total.reset();
  physical.reset();
  uuid.reset();
  label.reset();
  model.reset();
  serial.reset();
  removable.reset();
  protocol.reset();
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new Storage object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Storage::operator new(std::size_t size)
{
  void *o = ::new (Storage);
  return o;
}

/**
* @brief Sets equal two Storage objects
*
* @param v The Storage object to copy from
*/
void Storage::operator=(const Storage &s)
{
  if (&s == this)
  {
    return;
  }
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();
  physical = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
  label = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  removable = std::make_unique<bool>();
  protocol = std::make_unique<std::string>();

  (*name) = (*s.name);
  (*identifier) = (*s.identifier);
  (*type) = (*s.type);
  (*filesystem) = (*s.filesystem);
  (*mount) = (*s.mount);
  (*used) = (*s.used);
  (*total) = (*s.total);
  (*physical) = (*s.physical);
  (*uuid) = (*s.uuid);
  (*label) = (*s.label);
  (*model) = (*s.model);
  (*serial) = (*s.serial);
  (*removable) = (*s.removable);
  (*protocol) = (*s.protocol);
}

/**
* @brief Sets equal two Storage objects
*
* @param v The Storage object to copy from
*/
void Storage::operator=(Storage *s)
{
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
  used = std::make_unique<std::uint64_t>();
  total = std::make_unique<std::uint64_t>();
  physical = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
  label = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  removable = std::make_unique<bool>();
  protocol = std::make_unique<std::string>();

  (*name) = (*s->name);
  (*identifier) = (*s->identifier);
  (*type) = (*s->type);
  (*filesystem) = (*s->filesystem);
  (*mount) = (*s->mount);
  (*used) = (*s->used);
  (*total) = (*s->total);
  (*physical) = (*s->physical);
  (*uuid) = (*s->uuid);
  (*label) = (*s->label);
  (*model) = (*s->model);
  (*serial) = (*s->serial);
  (*removable) = (*s->removable);
  (*protocol) = (*s->protocol);
}
#pragma endregion "Operators"

#pragma region "Accessors"
std::string Storage::Name() {
  return (*name);
}

std::string Storage::Identifier() {
  return (*identifier);
}

std::string Storage::Type() {
  return (*type);
}

std::string Storage::FileSystem() {
  return (*filesystem);
}

std::string Storage::Mount() {
  return (*mount);
}

std::uint64_t Storage::Used() {
  return (*used);
}

std::uint64_t Storage::Total() {
  return (*total);
}

std::string Storage::Physical() {
  return (*physical);
}

std::string Storage::UUID() {
  return (*uuid);
}

std::string Storage::Label() {
  return (*label);
}

std::string Storage::Model() {
  return (*model);
}

std::string Storage::Serial() {
  return (*serial);
}

bool Storage::Removable() {
  return (*removable);
}

std::string Storage::Protocol() {
  return (*protocol);
}
#pragma endregion "Accessors"
