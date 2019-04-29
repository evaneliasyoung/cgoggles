/**
*  @file      graphics.h
*  @brief     The interface for the Graphics class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_GRAPHICS_H_
#define CGOGGLES_GRAPHICS_H_

#include "pch.h"

/**
* @brief Represents a computer's graphics processing unit
*/
class Graphics
{
private:
  std::unique_ptr<std::string> vendor;
  std::unique_ptr<std::string> model;
  std::unique_ptr<std::string> bus;
  std::unique_ptr<std::uint64_t> vram;
  std::unique_ptr<bool> dynamic;

public:
  Graphics();
  Graphics(std::string vnd, std::string mdl, std::string b, std::uint64_t ram, bool dyn);
  Graphics(const Graphics &o);
  ~Graphics();
  void *operator new(std::size_t size);
  void operator=(const Graphics &o);
  void operator=(Graphics *o);
  std::string Vendor();
  std::string Model();
  std::string Bus();
  std::uint64_t VRAM();
  bool Dynamic();
};

#endif // CGOGGLES_GRAPHICS_H_
