/**
*  @file      storage.cpp
*  @brief     The implementation for the storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "storage.h"
#include "os.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new Graphics object
*/
Storage::Storage()
{
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
  total = std::make_unique<std::uint64_t>();
  physical = std::make_unique<std::string>();
  uuid = std::make_unique<std::string>();
  label = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  removable = std::make_unique<bool>();
  protocol = std::make_unique<std::string>();
}

/**
* @brief Construct a new Graphics object
*
* @param nm  The name
* @param id  The ID
* @param tp  The type
* @param fs  The filesystem
* @param mnt The mount point
* @param ttl The total storage
* @param psy The physical location
* @param uid The UUID
* @param lbl The drive label
* @param mdl The model number
* @param srl The serial number
* @param rmv Whether or not it's removable
* @param prt The drive protocol
*/
Storage::Storage(std::string nm, std::string id, std::string tp, std::string fs, std::string mnt, std::uint64_t ttl, std::string psy, std::string uid, std::string lbl, std::string mdl, std::string srl, bool rmv, std::string prt)
{
  name = std::make_unique<std::string>(nm);
  identifier = std::make_unique<std::string>(id);
  type = std::make_unique<std::string>(tp);
  filesystem = std::make_unique<std::string>(fs);
  mount = std::make_unique<std::string>(mnt);
  total = std::make_unique<std::uint64_t>(ttl);
  physical = std::make_unique<std::string>(psy);
  uuid = std::make_unique<std::string>(uid);
  label = std::make_unique<std::string>(lbl);
  model = std::make_unique<std::string>(mdl);
  serial = std::make_unique<std::string>(srl);
  removable = std::make_unique<bool>(rmv);
  protocol = std::make_unique<std::string>(prt);
}

/**
* @brief Construct a new Storage object from another Storage object
*
* @param s The Storage object to copy from
*/
Storage::Storage(const Storage &s)
{
  name = std::make_unique<std::string>();
  identifier = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  filesystem = std::make_unique<std::string>();
  mount = std::make_unique<std::string>();
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
* @brief Destroy the FileSystemList object
*/
Storage::~Storage()
{
  name.reset();
  identifier.reset();
  type.reset();
  filesystem.reset();
  mount.reset();
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
/**
* @brief Returns a copy of the drive name
*
* @return std::string The drive name
*/
std::string Storage::Name()
{
  return (*name);
}

/**
* @brief Returns a copy of the drive identifier
*
* @return std::string The drive identifier
*/
std::string Storage::Identifier()
{
  return (*identifier);
}

/**
* @brief Returns a copy of the drive type
*
* @return std::string The drive type
*/
std::string Storage::Type()
{
  return (*type);
}

/**
* @brief Returns a copy of the associated file system
*
* @return std::string The associated file system
*/
std::string Storage::FileSystem()
{
  return (*filesystem);
}

/**
* @brief Returns a copy of the mount point
*
* @return std::string The mount point
*/
std::string Storage::Mount()
{
  return (*mount);
}

/**
* @brief Returns a copy of the total storage
*
* @return std::uint64_t The total storage
*/
std::uint64_t Storage::Total()
{
  return (*total);
}

/**
* @brief Returns a copy of the physical drive
*
* @return std::string The physical drive
*/
std::string Storage::Physical()
{
  return (*physical);
}

/**
* @brief Returns a copy of the drive's UUID
*
* @return std::string The drive's UUID
*/
std::string Storage::UUID()
{
  return (*uuid);
}

/**
* @brief Returns a copy of the drive's friendly display-name
*
* @return std::string The drive's friendly display-name
*/
std::string Storage::Label()
{
  return (*label);
}

/**
* @brief Returns a copy of the model number
*
* @return std::string The model number
*/
std::string Storage::Model()
{
  return (*model);
}

/**
* @brief Returns a copy of the serial number
*
* @return std::string The serial number
*/
std::string Storage::Serial()
{
  return (*serial);
}

/**
* @brief Returns a copy of whether or not the drive is removable
*
* @return bool Whether or not the drive is removable
*/
bool Storage::Removable()
{
  return (*removable);
}

/**
* @brief Returns a copy of the drive protocol
*
* @return std::string The drive protocol
*/
std::string Storage::Protocol()
{
  return (*protocol);
}
#pragma endregion "Accessors"
