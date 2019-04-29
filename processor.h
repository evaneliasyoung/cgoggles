/**
*  @file      processor.h
*  @brief     The interface for the Processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-04-29
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
  * @brief The architecture
  */
  std::unique_ptr<std::string> architecture;

  /**
  * @brief The internal socket type
  */
  std::unique_ptr<std::string> socketType;

  /**
  * @brief The make/model
  */
  std::unique_ptr<std::string> brand;

  /**
  * @brief The number of physical family
  */
  std::unique_ptr<std::uint8_t> family;

  /**
  * @brief The number of physical model
  */
  std::unique_ptr<std::uint8_t> model;

  /**
  * @brief The number of physical stepping
  */
  std::unique_ptr<std::uint8_t> stepping;

  /**
  * @brief The number of physical cores
  */
  std::unique_ptr<std::uint8_t> cores;

  /**
  * @brief The number of logical cores (threads)
  */
  std::unique_ptr<std::uint8_t> threads;

  /**
  * @brief The current clock speed (in GHz)
  */
  std::unique_ptr<std::uint64_t> speed;

  /**
  * @brief The maximum clock speed (in GHz)
  */
  std::unique_ptr<std::uint64_t> maxSpeed;

  void GetMac();
  void GetWin();
  void GetLux();

public:
  Processor();
  Processor(std::uint8_t plt);
  ~Processor();
  void operator=(Processor *o);
  std::string Manufacturer();
  std::string Architecture();
  std::string SocketType();
  std::string Brand();
  std::uint8_t Family();
  std::uint8_t Model();
  std::uint8_t Stepping();
  std::uint8_t Cores();
  std::uint8_t Threads();
  std::uint64_t Speed();
  std::uint64_t MaxSpeed();
};

#endif // COGGLES_PROCESSOR_H_
