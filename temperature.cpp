/**
*  @file      temperature.cpp
*  @brief     The implementation for the temperature class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-18
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "temperature.h"

#pragma region "Constructors"
/**
* @brief Construct a new Temperature object with a degree of -1 Kelvin
*/
Temperature::Temperature()
{
  kelvin = std::make_unique<float>(-1);
}

/**
* @brief Construct a new Temperature object with a degree of c Celsius
*
* @param c The degrees in celsius
*/
Temperature::Temperature(const float &c)
{
  kelvin = std::make_unique<float>(c + 273.15);
}

/**
* @brief Destroy the Temperature object
*/
Temperature::~Temperature()
{
  kelvin.reset();
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new Temperature object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Temperature::operator new(std::size_t size)
{
  void *o = ::new (Temperature);
  return o;
}

/**
* @brief Compares the equality two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The two Temperature objects are equal
* @return false The two Temperature objects are NOT equal
*/
bool Temperature::operator==(Temperature &t)
{
  return this->compare(t) == 0;
}

/**
* @brief Compares the inequality two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The two Temperature objects are NOT equal
* @return false The two Temperature objects are equal
*/
bool Temperature::operator!=(Temperature &t)
{
  return this->compare(t) != 0;
}

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The primary Temperature object is less than t
* @return false The primary Temperature object is NOT less than t
*/
bool Temperature::operator<(Temperature &t)
{
  return this->compare(t) < 0;
}

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The primary Temperature object is greater than t
* @return false The primary Temperature object is NOT greater than t
*/
bool Temperature::operator>(Temperature &t)
{
  return this->compare(t) > 0;
}

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The primary Temperature object is less than or equal to t
* @return false The primary Temperature object is NOT less than or equal to t
*/
bool Temperature::operator<=(Temperature &t)
{
  return this->compare(t) <= 0;
}

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return true  The primary Temperature object is greater than or equal to t
* @return false The primary Temperature object is NOT greater than or equal to t
*/
bool Temperature::operator>=(Temperature &t)
{
  return this->compare(t) >= 0;
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns the value of the Temperature object in kelvin
*
* @return float The temperature in kelvin
*/
float Temperature::K()
{
  return (*kelvin);
}

/**
* @brief Returns the value of the Temperature object in celsius
*
* @return float The temperature in celsius
*/
float Temperature::C()
{
  return ktoc((*kelvin));
}

/**
* @brief Returns the value of the Temperature object in fahrenheit
*
* @return float The temperature in fahrenheit
*/
float Temperature::F()
{
  return ktof((*kelvin));
}
#pragma endregion "Accessors"

#pragma region "Methods"

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The Temperature object to compare against
* @return -1    The primary Temperature object is less than t
* @return 0     The primary Temperature object is equal to t
* @return 1     The primary Temperature object is greater than t
*/
int Temperature::compare(Temperature &t)
{
  return this->K() == t.K() ? 0 : this->K() < t.K() ? -1 : 1;
}
#pragma endregion "Methods"

#pragma region "Static Methods"
/**
* @brief Converts kelvin to celsius
*
* @param  t The temperature in kelvin
* @return float The temperature in celsius
*/
float ktoc(const float &t)
{
  return t - 273.15;
}

/**
* @brief Converts kelvin to fahrenheit
*
* @param  t The temperature in kelvin
* @return float The temperature in fahrenheit
*/
float ktof(const float &t)
{
  return ctof(ktoc(t));
}

/**
* @brief Converts celsius to kelvin
*
* @param  t The temperature in celsius
* @return float The temperature in kelvin
*/
float ctok(const float &t)
{
  return t + 273.15;
}

/**
* @brief Converts celsius to fahrenheit
*
* @param  t The temperature in celsius
* @return float The temperature in fahrenheit
*/
float ctof(const float &t)
{
  return (9.0 / 5 * t) + 32;
}

/**
* @brief Converts fahrenheit to kelvin
*
* @param  t The temperature in fahrenheit
* @return float The temperature in kelvin
*/
float ftok(const float &t)
{
  return ctok(ftoc(t));
}

/**
* @brief Converts fahrenheit to celsius
*
* @param  t The temperature in fahrenheit
* @return float The temperature in celsius
*/
float ftoc(const float &t)
{
  return (5.0 / 9) * (t - 32);
}

/**
* @brief Compares the value of two Temperature objects
*
* @param  t     The primary Temperature object to compare against
* @param  c     The Temperature object to compare against
* @return -1    The Temperature object t is less than c
* @return 0     The Temperature object t is equal to c
* @return 1     The Temperature object t is greater than c
*/
int compare(Temperature &t, Temperature &c)
{
  return t.compare(c);
}
#pragma endregion "Static Methods"
