/**
*  @file      storage.cpp
*  @brief     The implementation for the Storage class.
*
*  @author    Evan Elias Young
*  @date      2019-03-25
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
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
  name = "";
  identifier = "";
  type = "";
  filesystem = "";
  mount = "";
  total = 0;
  physical = "";
  uuid = "";
  label = "";
  model = "";
  serial = "";
  removable = false;
  protocol = "";
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
  name = nm;
  identifier = id;
  type = tp;
  filesystem = fs;
  mount = mnt;
  total = ttl;
  physical = psy;
  uuid = uid;
  label = lbl;
  model = mdl;
  serial = srl;
  removable = rmv;
  protocol = prt;
}

/**
* @brief Construct a new Storage object from another Storage object
*
* @param o The Storage object to copy from
*/
Storage::Storage(const Storage &o)
{
  name = o.name;
  identifier = o.identifier;
  type = o.type;
  filesystem = o.filesystem;
  mount = o.mount;
  total = o.total;
  physical = o.physical;
  uuid = o.uuid;
  label = o.label;
  model = o.model;
  serial = o.serial;
  removable = o.removable;
  protocol = o.protocol;
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
* @param o The Storage object to copy from
*/
void Storage::operator=(const Storage &o)
{
  if (&o == this)
  {
    return;
  }
  name = o.name;
  identifier = o.identifier;
  type = o.type;
  filesystem = o.filesystem;
  mount = o.mount;
  total = o.total;
  physical = o.physical;
  uuid = o.uuid;
  label = o.label;
  model = o.model;
  serial = o.serial;
  removable = o.removable;
  protocol = o.protocol;
}

/**
* @brief Sets equal two Storage objects
*
* @param o The Storage object to copy from
*/
void Storage::operator=(Storage *o)
{
  name = o->name;
  identifier = o->identifier;
  type = o->type;
  filesystem = o->filesystem;
  mount = o->mount;
  total = o->total;
  physical = o->physical;
  uuid = o->uuid;
  label = o->label;
  model = o->model;
  serial = o->serial;
  removable = o->removable;
  protocol = o->protocol;
}
#pragma endregion "Operators"
