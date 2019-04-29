/**
*  @file      graphicslist.h
*  @brief     The interface for the GraphicsList class.
*
*  @author    Evan Elias Young
*  @date      2019-03-30
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_GRAPHICSLIST_H_
#define CGOGGLES_GRAPHICSLIST_H_

#include "pch.h"
#include "graphics.h"

/**
* @brief Represents a computer's collection of Graphics objects
*/
class GraphicsList
{
private:
  std::unique_ptr<std::vector<Graphics>> controllers;
  void GetMac();
  void GetWin();
  void GetLux();

public:
  GraphicsList();
  GraphicsList(std::uint8_t plt);
  GraphicsList(const GraphicsList &o);
  ~GraphicsList();
  void *operator new(std::size_t size);
  void operator=(const GraphicsList &o);
  void operator=(GraphicsList *o);
  std::vector<Graphics> Controllers();
};

#endif // CGOGGLES_GRAPHICSLIST_H_
