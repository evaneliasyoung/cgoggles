/**
*  @file      graphics.cpp
*  @brief     The implementation for the Graphics class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "graphics.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new Graphics object
*/
Graphics::Graphics()
{
  vendor = "";
  model = "";
  bus = "";
  vram = 0;
  dynamic = false;
}

/**
* @brief Construct a new Graphics object from the data
*
* @param vnd The vendor
* @param mdl The model number
* @param b   The bus space
* @param ram The amount of VRAM
* @param dyn Whether or not the RAM is dynamic
*/
Graphics::Graphics(std::string vnd, std::string mdl, std::string b, std::uint64_t ram, bool dyn)
{
  vendor = vnd;
  model = mdl;
  bus = b;
  vram = ram;
  dynamic = dyn;
}

/**
* @brief Construct a new Graphics object from another Graphics object
*
* @param o The Graphics object to copy from
*/
Graphics::Graphics(const Graphics &o)
{
  vendor = o.vendor;
  model = o.model;
  bus = o.bus;
  vram = o.vram;
  dynamic = o.dynamic;
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new Graphics object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Graphics::operator new(std::size_t size)
{
  void *o = ::new (Graphics);
  return o;
}

/**
* @brief Sets equal two Graphics objects
*
* @param o The Graphics object to copy from
*/
void Graphics::operator=(const Graphics &o)
{
  if (&o == this)
  {
    return;
  }

  vendor = o.vendor;
  model = o.model;
  bus = o.bus;
  vram = o.vram;
  dynamic = o.dynamic;
}

/**
* @brief Sets equal two Graphics objects
*
* @param o The Graphics object to copy from
*/
void Graphics::operator=(Graphics *o)
{
  vendor = o->vendor;
  model = o->model;
  bus = o->bus;
  vram = o->vram;
  dynamic = o->dynamic;
}
#pragma endregion "Operators"
