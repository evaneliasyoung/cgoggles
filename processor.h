/**
*  @file      processor.h
*  @brief     The interface for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-16
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef COGGLES_PROCESSOR_H_
#define COGGLES_PROCESSOR_H_

#include "pch.h"
#include "temperature.h"

class Processor
{
private:
  std::unique_ptr<std::string> _manuf;
  std::unique_ptr<std::string> _model;
  std::unique_ptr<Temperature> _temp;

public:
  Processor();
  ~Processor();
  std::string Manufacturer();
};

#endif // COGGLES_PROCESSOR_H_
