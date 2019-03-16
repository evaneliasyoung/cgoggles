/**
*  @file      temperature.cpp
*  @brief     The implementation for the temperature class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-16
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_TEMPERATURE_H_
#define CGOGGLES_TEMPERATURE_H_

#include "pch.h"

class Temperature
{
private:
  std::unique_ptr<float> kelvin;

public:
  Temperature();
  Temperature(const float &c);
  ~Temperature();
  void *operator new(std::size_t size);
  float K();
  float C();
  float F();
  bool operator==(Temperature t);
  bool operator!=(Temperature t);
  bool operator<(Temperature t);
  bool operator>(Temperature t);
  bool operator<=(Temperature t);
  bool operator>=(Temperature t);
};

float ktoc(const float &t);
float ktof(const float &t);
float ctok(const float &t);
float ctof(const float &t);
float ftok(const float &t);
float ftoc(const float &t);

#endif // CGOGGLES_TEMPERATURE_H_
