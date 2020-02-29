/**
*  @file      processor.h
*  @brief     The interface for the Processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef COGGLES_PROCESSOR_H_
#define COGGLES_PROCESSOR_H_

#include "pch.h"
#include "temperature.h"

/**
* @brief Represents a computer's central processing unit
*/
class Processor
{
private:
  void GetMac();
  void GetWin();
  void GetLux();

public:
  Processor();
  Processor(std::uint8_t plt);
  Processor(const Processor &o);
  void *operator new(std::size_t size);
  void operator=(const Processor &o);
  void operator=(Processor *o);
  std::string manufacturer;
  std::string architecture;
  std::string socketType;
  std::string brand;
  std::uint8_t family;
  std::uint8_t model;
  std::uint8_t stepping;
  std::uint8_t cores;
  std::uint8_t threads;
  std::uint64_t speed;
  std::uint64_t maxSpeed;
};

#endif // COGGLES_PROCESSOR_H_
