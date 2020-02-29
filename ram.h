/**
*  @file      ram.h
*  @brief     The interface for the RAM class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef COGGLES_RAM_H_
#define COGGLES_RAM_H_

#include "pch.h"

/**
* @brief Represents a computer's central processing unit
*/
class RAM
{
public:
  RAM();
  RAM(std::uint64_t sz, std::string bk, std::string tp, std::uint64_t spd, std::string ff, std::string manuf, std::string prt, std::string srl, float vlt, float vltMin, float vltMax);
  RAM(const RAM &o);
  void *operator new(std::size_t size);
  void operator=(const RAM &o);
  void operator=(RAM *o);
  std::uint64_t size;
  std::string bank;
  std::string type;
  std::uint64_t speed;
  std::string formFactor;
  std::string manufacturer;
  std::string part;
  std::string serial;
  float voltageConfigured;
  float voltageMin;
  float voltageMax;
};

#endif // COGGLES_RAM_H_
