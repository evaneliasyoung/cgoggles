/**
*  @file      graphics.h
*  @brief     The interface for the Graphics class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2020-02-28
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_GRAPHICS_H_
#define CGOGGLES_GRAPHICS_H_

#include "pch.h"

/**
* @brief Represents a computer's graphics processing unit
*/
class Graphics
{
public:
  Graphics();
  Graphics(std::string vnd, std::string mdl, std::string b, std::uint64_t ram, bool dyn);
  Graphics(const Graphics &o);
  void *operator new(std::size_t size);
  void operator=(const Graphics &o);
  void operator=(Graphics *o);
  std::string vendor;
  std::string model;
  std::string bus;
  std::uint64_t vram;
  bool dynamic;
};

#endif // CGOGGLES_GRAPHICS_H_
