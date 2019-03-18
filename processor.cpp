/**
*  @file      processor.cpp
*  @brief     The implementation for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-18
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "processor.h"
#include "temperature.h"
#include "os.h"
#include "utils.h"

#pragma region "Constructors"
/**
* @brief Construct a new Processor::Processor object
*/
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

/**
* @brief Destroy the Processor::Processor object
*/
Processor::~Processor()
{
  manufacturer.reset();
  model.reset();
  cores.reset();
  threads.reset();
  temperature.reset();
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void Processor::GetMac()
{
}

/**
* @brief Fills in the processor information for Windows systems
*/
void Processor::GetWin()
{
  std::unique_ptr<std::string> wmicPath = std::make_unique<std::string>(getWmicPath());
}

/**
* @brief Fills in the processor information for Linux systems
*/
void Processor::GetLux()
{
}
#pragma endregion

#pragma region "Accessors"
/**
* @brief Returns a copy of the manufacturer
*
* @return std::string The manufacturer
*/
std::string Processor::Manufacturer()
{
  return (*manufacturer);
}

/**
* @brief Returns the a copy of the model
*
* @return std::string The model
*/
std::string Processor::Model()
{
  return (*model);
}

/**
* @brief Returns a copy of the physical core count
*
* @return std::uint8_t The number of physical cores
*/
std::uint8_t Processor::Cores()
{
  return (*cores);
}

/**
* @brief Returns a copy of the logical core count
*
* @return std::uint8_t The number of logical cores
*/
std::uint8_t Processor::Threads()
{
  return (*threads);
}
#pragma endregion "Accessors"
