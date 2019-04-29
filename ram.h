/**
*  @file      ram.h
*  @brief     The interface for the RAM class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef COGGLES_RAM_H_
#define COGGLES_RAM_H_

#include "pch.h"

/**
* @brief Represents a computer's central processing unit
*/
class RAM
{
private:
  std::unique_ptr<std::uint64_t> size;
  std::unique_ptr<std::string> bank;
  std::unique_ptr<std::string> type;
  std::unique_ptr<std::uint64_t> speed;
  std::unique_ptr<std::string> formFactor;
  std::unique_ptr<std::string> manufacturer;
  std::unique_ptr<std::string> part;
  std::unique_ptr<std::string> serial;
  std::unique_ptr<float> voltageConfigured;
  std::unique_ptr<float> voltageMin;
  std::unique_ptr<float> voltageMax;

public:
  RAM();
  RAM(std::uint64_t sz, std::string bk, std::string tp, std::uint64_t spd, std::string ff, std::string manuf, std::string prt, std::string srl, float vlt, float vltMin, float vltMax);
  ~RAM();
  RAM(const RAM &o);
  void *operator new(std::size_t size);
  void operator=(const RAM &o);
  void operator=(RAM *o);
  std::uint64_t Size();
  std::string Bank();
  std::string Type();
  std::uint64_t Speed();
  std::string FormFactor();
  std::string Manufacturer();
  std::string Part();
  std::string Serial();
  float VoltageConfigured();
  std::string PrettyVoltageConfigured();
  float VoltageMin();
  std::string PrettyVoltageMin();
  float VoltageMax();
  std::string PrettyVoltageMax();
};

#endif // COGGLES_RAM_H_
