/**
*  @file      ram.cpp
*  @brief     The implementation for the RAM class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "ram.h"
#include "os.h"

#pragma region "Constructors"
/**
* @brief Construct a new RAM object
*/
RAM::RAM()
{
  size = 0;
  bank = "";
  type = "";
  speed = 0;
  formFactor = "";
  manufacturer = "";
  part = "";
  serial = "";
  voltageConfigured = 0.0;
  voltageMin = 0.0;
  voltageMax = 0.0;
}

/**
* @brief Construct a new RAM object with values
*
* @param sz     The amount
* @param bk     The bank
* @param tp     The type
* @param spd    The speed
* @param ff     The formfactor
* @param manuf  The manufacture
* @param prt    The part number
* @param srl    The serial number
* @param vlt    The current voltage
* @param vltMin The minimum voltage
* @param vltMax The maximum voltage
*/
RAM::RAM(std::uint64_t sz, std::string bk, std::string tp, std::uint64_t spd, std::string ff, std::string manuf, std::string prt, std::string srl, float vlt, float vltMin, float vltMax)
{
  size = sz;
  bank = bk;
  type = tp;
  speed = spd;
  formFactor = ff;
  manufacturer = manuf;
  part = prt;
  serial = srl;
  voltageConfigured = vlt;
  voltageMin = vltMin;
  voltageMax = vltMax;
}

/**
* @brief Construct a new RAM object with values from another RAM object
*
* @param o The other RAM object to copy from
*/
RAM::RAM(const RAM &o)
{
  size = o.size;
  bank = o.bank;
  type = o.type;
  speed = o.speed;
  formFactor = o.formFactor;
  manufacturer = o.manufacturer;
  part = o.part;
  serial = o.serial;
  voltageConfigured = o.voltageConfigured;
  voltageMin = o.voltageMin;
  voltageMax = o.voltageMax;
}
#pragma endregion "Constructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new RAM object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *RAM::operator new(std::size_t size)
{
  void *o = ::new (RAM);
  return o;
}

/**
* @brief Sets equal two RAM objects
*
* @param o The RAM object to copy from
*/
void RAM::operator=(const RAM &o)
{
  if (&o == this)
  {
    return;
  }
  size = o.size;
  bank = o.bank;
  type = o.type;
  speed = o.speed;
  formFactor = o.formFactor;
  manufacturer = o.manufacturer;
  part = o.part;
  serial = o.serial;
  voltageConfigured = o.voltageConfigured;
  voltageMin = o.voltageMin;
  voltageMax = o.voltageMax;
}

/**
* @brief Sets equal two RAM objects
*
* @param o The RAM object to copy from
*/
void RAM::operator=(RAM *o)
{
  size = o->size;
  bank = o->bank;
  type = o->type;
  speed = o->speed;
  formFactor = o->formFactor;
  manufacturer = o->manufacturer;
  part = o->part;
  serial = o->serial;
  voltageConfigured = o->voltageConfigured;
  voltageMin = o->voltageMin;
  voltageMax = o->voltageMax;
}
#pragma endregion "Operators"
