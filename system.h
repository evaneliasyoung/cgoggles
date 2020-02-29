/**
*  @file      system.h
*  @brief     The interface for the System class.
*
*  @author    Evan Elias Young
*  @date      2019-04-03
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef COGGLES_SYSTEM_H_
#define COGGLES_SYSTEM_H_

#include "pch.h"

/**
* @brief Represents a computer's branding-information (make, model, etc.)
*/
class System
{
private:
  void GetMac();
  void GetWin();
  void GetLux();

public:
  System();
  System(std::uint8_t plt);
  System(const System &o);
  void *operator new(std::size_t size);
  void operator=(const System &o);
  void operator=(System *o);
  std::string manufacturer;
  std::string model;
  std::string version;
  std::string serial;
  std::string uuid;
};

#endif // COGGLES_SYSTEM_H_
