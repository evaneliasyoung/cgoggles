/**
*  @file      temperature.h
*  @brief     The interface for the Temperature class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_TEMPERATURE_H_
#define CGOGGLES_TEMPERATURE_H_

#include "pch.h"

/**
 * @brief Represents a Temperature with a value of degrees in kelvin
 */
class Temperature
{
public:
  Temperature();
  Temperature(const float &c);
  Temperature(const Temperature &o);
  void *operator new(std::size_t size);
  void operator=(const Temperature &o);
  void operator=(Temperature *o);
  bool operator==(Temperature &t);
  bool operator!=(Temperature &t);
  bool operator<(Temperature &t);
  bool operator>(Temperature &t);
  bool operator<=(Temperature &t);
  bool operator>=(Temperature &t);
  float kelvin;
  int compare(Temperature &t);
};

float ktoc(const float &t);
float ktof(const float &t);
float ctok(const float &t);
float ctof(const float &t);
float ftok(const float &t);
float ftoc(const float &t);
int compare(Temperature &t, Temperature &c);

#endif // CGOGGLES_TEMPERATURE_H_
