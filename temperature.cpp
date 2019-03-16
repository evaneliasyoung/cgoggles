/**
*  @file      temperature.cpp
*  @brief     The implementation for the temperature class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-16
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "temperature.h"

#pragma region "Constructors"
Temperature::Temperature()
{
  _kelvin = std::make_unique<float>(-1);
}

Temperature::Temperature(const float &c)
{
  _kelvin = std::make_unique<float>(c + 273.15);
}

Temperature::~Temperature()
{
  _kelvin.reset();
}
#pragma endregion

#pragma region "Accessors"
float Temperature::K()
{
  return (*_kelvin);
}
float Temperature::C()
{
  return ktoc((*_kelvin));
}
float Temperature::F()
{
  return ktof((*_kelvin));
}
#pragma endregion "Accessors"

#pragma region "Operators"
void *Temperature::operator new(std::size_t size)
{
  void *o = ::new (Temperature);
  return o;
}

bool Temperature::operator==(Temperature t)
{
  return this->K() == t.K();
}

bool Temperature::operator!=(Temperature t)
{
  return this->K() != t.K();
}

bool Temperature::operator<(Temperature t)
{
  return this->K() < t.K();
}

bool Temperature::operator>(Temperature t)
{
  return this->K() > t.K();
}

bool Temperature::operator<=(Temperature t)
{
  return this->K() <= t.K();
}

bool Temperature::operator>=(Temperature t)
{
  return this->K() >= t.K();
}
#pragma endregion "Operators"

#pragma region "Static Methods"
float ktoc(const float &t)
{
  return t - 273.15;
}

float ktof(const float &t)
{
  return ctof(ktoc(t));
}

float ctok(const float &t)
{
  return t + 273.15;
}

float ctof(const float &t)
{
  return (9.0 / 5 * t) + 32;
}

float ftok(const float &t)
{
  return ctok(ftoc(t));
}

float ftoc(const float &t)
{
  return (5.0 / 9) * (t - 32);
}
#pragma endregion "Static Methods"
