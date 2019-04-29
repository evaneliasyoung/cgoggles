/**
*  @file      system.h
*  @brief     The interface for the System class.
*
*  @author    Evan Elias Young
*  @date      2019-04-03
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  std::unique_ptr<std::string> manufacturer;
  std::unique_ptr<std::string> model;
  std::unique_ptr<std::string> version;
  std::unique_ptr<std::string> serial;
  std::unique_ptr<std::string> uuid;

  void GetMac();
  void GetWin();
  void GetLux();

public:
  System();
  System(std::uint8_t plt);
  ~System();
  void operator=(System *o);
  std::string Manufacturer();
  std::string Model();
  std::string Version();
  std::string Serial();
  std::string UUID();
};

#endif // COGGLES_SYSTEM_H_
