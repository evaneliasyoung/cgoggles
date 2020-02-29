/**
*  @file      chassis.h
*  @brief     The interface for the Chassis class.
*
*  @author    Evan Elias Young
*  @date      2019-09-11
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_CHASSIS_H_
#define CGOGGLES_CHASSIS_H_

#include "pch.h"

class Chassis
{
private:
  void GetMac();
  void GetWin();
  void GetLux();

public:
  Chassis();
  Chassis(std::uint8_t plt);
  Chassis(const Chassis &o);
  void *operator new(std::size_t size);
  void operator=(const Chassis &o);
  void operator=(Chassis *o);
  std::string manufacturer;
  std::string model;
  std::string type;
  std::string version;
  std::string serial;
  std::string assetTag;
};

#endif // CGOGGLES_CHASSIS_H_
