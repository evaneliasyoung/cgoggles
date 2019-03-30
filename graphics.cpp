/**
*  @file      graphics.cpp
*  @brief     The implementation for the graphics class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-03-30
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "graphics.h"
#include "utils.h"

#pragma region "Contructors"
Graphics::Graphics()
{
  vendor = std::make_unique<std::string>();
  model = std::make_unique<std::string>();
  bus = std::make_unique<std::string>();
  vram = std::make_unique<std::uint64_t>();
  dynamic = std::make_unique<bool>();
}

Graphics::Graphics(std::string vnd, std::string mdl, std::string b, std::uint64_t ram, bool dyn)
{
  vendor = std::make_unique<std::string>(vnd);
  model = std::make_unique<std::string>(mdl);
  bus = std::make_unique<std::string>(b);
  vram = std::make_unique<std::uint64_t>(ram);
  dynamic = std::make_unique<bool>(dyn);
}

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
std::string Graphics::Vendor()
{
  return (*vendor);
}

std::string Graphics::Model()
{
  return (*model);
}

std::string Graphics::Bus()
{
  return (*bus);
}

std::uint64_t Graphics::VRAM()
{
  return (*vram);
}

bool Graphics::Dynamic()
{
  return (*dynamic);
}
#pragma endregion "Accessors"
