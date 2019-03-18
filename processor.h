/**
*  @file      processor.h
*  @brief     The interface for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-18
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  /**
  * @brief The manufacturer
  */
  std::unique_ptr<std::string> manufacturer;

  /**
  * @brief The make/model
  */
  std::unique_ptr<std::string> model;

  /**
  * @brief The number of physical cores
  */
  std::unique_ptr<std::uint8_t> cores;

  /**
  * @brief The number of logical cores (threads)
  */
  std::unique_ptr<std::uint8_t> threads;

  /**
  * @brief The current temperature as a Temperature object
  */
  std::unique_ptr<Temperature> temperature;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  Processor();
  ~Processor();
  std::string Manufacturer();
  std::string Model();
  std::uint8_t Cores();
  std::uint8_t Threads();
};

#endif // COGGLES_PROCESSOR_H_
