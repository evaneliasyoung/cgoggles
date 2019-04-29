/**
*  @file      graphics.cpp
*  @brief     The implementation for the graphics class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  vendor = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  bus = std::make_unique<std::string>();
  vram = std::make_unique<std::uint64_t>();
  dynamic = std::make_unique<bool>();
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
  vendor = std::make_unique<std::string>(vnd);
  model = std::make_unique<std::string>(mdl);
  bus = std::make_unique<std::string>(b);
  vram = std::make_unique<std::uint64_t>(ram);
  dynamic = std::make_unique<bool>(dyn);
}

/**
* @brief Construct a new Graphics object from another Graphics object
*
* @param s The Graphics object to copy from
*/
Graphics::Graphics(const Graphics &s)
{
  vendor = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  bus = std::make_unique<std::string>();
  vram = std::make_unique<std::uint64_t>();
  dynamic = std::make_unique<bool>();

  (*vendor) = (*s.vendor);
  (*model) = (*s.model);
  (*bus) = (*s.bus);
  (*vram) = (*s.vram);
  (*dynamic) = (*s.dynamic);
}

/**
* @brief Destroy the Processor object
*/
Graphics::~Graphics()
{
  vendor.reset();
  model.reset();
  bus.reset();
  vram.reset();
  dynamic.reset();
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new fs object
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
* @brief Sets equal two fs objects
*
* @param v The fs object to copy from
*/
void Graphics::operator=(const Graphics &s)
{
  if (&s == this)
  {
    return;
  }
  vendor = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  bus = std::make_unique<std::string>();
  vram = std::make_unique<std::uint64_t>();
  dynamic = std::make_unique<bool>();

  (*vendor) = (*s.vendor);
  (*model) = (*s.model);
  (*bus) = (*s.bus);
  (*vram) = (*s.vram);
  (*dynamic) = (*s.dynamic);
}

/**
* @brief Sets equal two fs objects
*
* @param v The fs object to copy from
*/
void Graphics::operator=(Graphics *s)
{
  vendor = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  bus = std::make_unique<std::string>();
  vram = std::make_unique<std::uint64_t>();
  dynamic = std::make_unique<bool>();

  (*vendor) = (*s->vendor);
  (*model) = (*s->model);
  (*bus) = (*s->bus);
  (*vram) = (*s->vram);
  (*dynamic) = (*s->dynamic);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the vendor
*
* @return std::string A copy of the vendor
*/
std::string Graphics::Vendor()
{
  return (*vendor);
}

/**
* @brief Returns a copy of the model
*
* @return std::string A copy of the model
*/
std::string Graphics::Model()
{
  return (*model);
}

/**
* @brief Returns a copy of the bus location
*
* @return std::string A copy of the bus location
*/
std::string Graphics::Bus()
{
  return (*bus);
}

/**
* @brief Returns a copy of the amount ofVRAM
*
* @return std::uint64_t A copy of the amount ofVRAM
*/
std::uint64_t Graphics::VRAM()
{
  return (*vram);
}

/**
* @brief Returns a copy of whether or not the VRAM is dynamic
*
* @return bool A copy of whether or not the VRAM is dynamic
*/
bool Graphics::Dynamic()
{
  return (*dynamic);
}
#pragma endregion "Accessors"
