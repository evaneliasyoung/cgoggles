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
#include "os.h"
#include "utils.h"

#pragma region "Constructors"
Processor::Processor()
{
  manufacturer = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  cores = std::make_unique<std::uint8_t>();
  threads = std::make_unique<std::uint8_t>();
  temperature = std::make_unique<Temperature>();

  switch (CGOGGLES_OS)
  {
  case OS_WIN:
    GetWin();
    break;
  case OS_MAC:
    GetMac();
    break;
  case OS_LUX:
    GetLux();
  default:
    break;
  }
}

Processor::~Processor()
{
  manufacturer.reset();
  model.reset();
  temperature.reset();
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
void Processor::GetMac()
{
}
void Processor::GetWin()
{
  std::unique_ptr<std::string> wmicPath = std::make_unique<std::string>(getWmicPath());
}
void Processor::GetLux()
{
}
#pragma endregion

#pragma region "Accessors"
std::string Processor::Manufacturer()
{
  return (*manufacturer);
}

std::string Processor::Model()
{
  return (*model);
}

std::uint8_t Processor::Cores()
{
  return (*cores);
}

std::uint8_t Processor::Threads()
{
  return (*threads);
}
#pragma endregion "Accessors"
