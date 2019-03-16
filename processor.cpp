/**
*  @file      processor.cpp
*  @brief     The implementation for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-16
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "processor.h"
#include "temperature.h"

#pragma region "Constructors"
Processor::Processor()
{
  _manuf = std::make_unique<std::string>();
  _model = std::make_unique<std::string>();
  _temp = std::make_unique<Temperature>();
}

Processor::~Processor()
{
  _manuf.reset();
  _model.reset();
  _temp.reset();
}
#pragma endregion "Constructors"

#pragma region "Accessors"
std::string Processor::Manufacturer()
{
  return (*_manuf);
}
#pragma endregion "Accessors"
