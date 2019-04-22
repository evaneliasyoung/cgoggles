/**
*  @file      ram.cpp
*  @brief     The implementation for the ram class.
*
*  @author    Evan Elias Young
*  @date      2019-04-04
*  @date      2019-04-22
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "ram.h"
#include "os.h"

#pragma region "Constructors"
/**
* @brief Construct a new RAM object
*/
RAM::RAM()
{
  size = std::make_unique<std::uint64_t>();
  bank = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  speed = std::make_unique<std::uint64_t>();
  formFactor = std::make_unique<std::string>();
  manufacturer = std::make_unique<std::string>();
  part = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  voltageConfigured = std::make_unique<float>();
  voltageMin = std::make_unique<float>();
  voltageMax = std::make_unique<float>();
}

/**
* @brief Construct a new RAM object with values
*/
RAM::RAM(std::uint64_t sz, std::string bk, std::string tp, std::uint64_t spd, std::string ff, std::string manuf, std::string prt, std::string srl, float vlt, float vltMin, float vltMax)
{
  size = std::make_unique<std::uint64_t>(sz);
  bank = std::make_unique<std::string>(bk);
  type = std::make_unique<std::string>(tp);
  speed = std::make_unique<std::uint64_t>(spd);
  formFactor = std::make_unique<std::string>(ff);
  manufacturer = std::make_unique<std::string>(manuf);
  part = std::make_unique<std::string>(prt);
  serial = std::make_unique<std::string>(srl);
  voltageConfigured = std::make_unique<float>(vlt);
  voltageMin = std::make_unique<float>(vltMin);
  voltageMax = std::make_unique<float>(vltMax);
}

/**
* @brief Construct a new RAM object with values from another RAM object
*
* @param s The other RAM object to copy from
*/
RAM::RAM(const RAM &s)
{
  size = std::make_unique<std::uint64_t>();
  bank = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  speed = std::make_unique<std::uint64_t>();
  formFactor = std::make_unique<std::string>();
  manufacturer = std::make_unique<std::string>();
  part = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  voltageConfigured = std::make_unique<float>();
  voltageMin = std::make_unique<float>();
  voltageMax = std::make_unique<float>();

  (*size) = (*s.size);
  (*bank) = (*s.bank);
  (*type) = (*s.type);
  (*speed) = (*s.speed);
  (*formFactor) = (*s.formFactor);
  (*manufacturer) = (*s.manufacturer);
  (*part) = (*s.part);
  (*serial) = (*s.serial);
  (*voltageConfigured) = (*s.voltageConfigured);
  (*voltageMin) = (*s.voltageMin);
  (*voltageMax) = (*s.voltageMax);
}

/**
* @brief Destroy the RAM object
*/
RAM::~RAM()
{
  size.reset();
  bank.reset();
  type.reset();
  speed.reset();
  formFactor.reset();
  manufacturer.reset();
  part.reset();
  serial.reset();
  voltageConfigured.reset();
  voltageMin.reset();
  voltageMax.reset();
}
#pragma endregion "Constructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new RAM object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *RAM::operator new(std::size_t size)
{
  void *o = ::new (RAM);
  return o;
}

/**
* @brief Sets equal two RAM objects
*
* @param v The RAM object to copy from
*/
void RAM::operator=(const RAM &s)
{
  if (&s == this)
  {
    return;
  }
  size = std::make_unique<std::uint64_t>();
  bank = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  speed = std::make_unique<std::uint64_t>();
  formFactor = std::make_unique<std::string>();
  manufacturer = std::make_unique<std::string>();
  part = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  voltageConfigured = std::make_unique<float>();
  voltageMin = std::make_unique<float>();
  voltageMax = std::make_unique<float>();

  (*size) = (*s.size);
  (*bank) = (*s.bank);
  (*type) = (*s.type);
  (*speed) = (*s.speed);
  (*formFactor) = (*s.formFactor);
  (*manufacturer) = (*s.manufacturer);
  (*part) = (*s.part);
  (*serial) = (*s.serial);
  (*voltageConfigured) = (*s.voltageConfigured);
  (*voltageMin) = (*s.voltageMin);
  (*voltageMax) = (*s.voltageMax);
}

/**
* @brief Sets equal two RAM objects
*
* @param v The RAM object to copy from
*/
void RAM::operator=(RAM *s)
{
  size = std::make_unique<std::uint64_t>();
  bank = std::make_unique<std::string>();
  type = std::make_unique<std::string>();
  speed = std::make_unique<std::uint64_t>();
  formFactor = std::make_unique<std::string>();
  manufacturer = std::make_unique<std::string>();
  part = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  voltageConfigured = std::make_unique<float>();
  voltageMin = std::make_unique<float>();
  voltageMax = std::make_unique<float>();

  (*size) = (*s->size);
  (*bank) = (*s->bank);
  (*type) = (*s->type);
  (*speed) = (*s->speed);
  (*formFactor) = (*s->formFactor);
  (*manufacturer) = (*s->manufacturer);
  (*part) = (*s->part);
  (*serial) = (*s->serial);
  (*voltageConfigured) = (*s->voltageConfigured);
  (*voltageMin) = (*s->voltageMin);
  (*voltageMax) = (*s->voltageMax);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the size
*
* @return std::string The size
*/
std::uint64_t RAM::Size()
{
  return (*size);
}

/**
* @brief Returns a copy of the installed slot
*
* @return std::string The installed slot
*/
std::string RAM::Bank()
{
  return (*bank);
}

/**
* @brief Returns a copy of the type of ram
*
* @return std::string The type of ram
*/
std::string RAM::Type()
{
  return (*type);
}

/**
* @brief Returns a copy of the speed
*
* @return std::uint64_t The speed
*/
std::uint64_t RAM::Speed()
{
  return (*speed);
}

/**
* @brief Returns a copy of the form-factor
*
* @return std::string The form-factor
*/
std::string RAM::FormFactor()
{
  return (*formFactor);
}

/**
* @brief Returns a copy of the manufacturer
*
* @return std::string The manufacturer
*/
std::string RAM::Manufacturer()
{
  return (*manufacturer);
}

/**
* @brief Returns a copy of the part number
*
* @return std::string The part number
*/
std::string RAM::Part()
{
  return (*part);
}

/**
* @brief Returns a copy of the serial number
*
* @return std::string The serial number
*/
std::string RAM::Serial()
{
  return (*serial);
}

/**
* @brief Returns a copy of the voltage
*
* @return float The voltage
*/
float RAM::VoltageConfigured()
{
  return (*voltageConfigured);
}

/**
* @brief Returns human-readable a copy of the voltage
*
* @return std::string The human-readble voltage
*/
std::string RAM::PrettyVoltageConfigured()
{
  std::stringstream buffer;
  buffer << std::fixed << std::setprecision(1) << (*voltageConfigured) << " V";
  return buffer.str();
}

/**
* @brief Returns a copy of the minimum voltage
*
* @return float The minimum voltage
*/
float RAM::VoltageMin()
{
  return (*voltageMin);
}

/**
* @brief Returns a human-readable copy of the minimum voltage
*
* @return std::string The human-readble minimum voltage
*/
std::string RAM::PrettyVoltageMin()
{
  std::stringstream buffer;
  buffer << std::fixed << std::setprecision(1) << (*voltageMin) << " V";
  return buffer.str();
}

/**
* @brief Returns a copy of the maximum voltage
*
* @return float The maximum voltage
*/
float RAM::VoltageMax()
{
  return (*voltageMax);
}

/**
* @brief Returns a human-readable copy of the maximum voltage
*
* @return std::string The human-readble maximum voltage
*/
std::string RAM::PrettyVoltageMax()
{
  std::stringstream buffer;
  buffer << std::fixed << std::setprecision(1) << (*voltageMax) << " V";
  return buffer.str();
}
#pragma endregion "Accessors"
