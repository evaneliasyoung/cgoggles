/**
*  @file      main.cpp
*  @brief     The main entry point for cgoggles.
*
*  @author    Evan Elias Young
*  @date      2019-03-11
*  @date      2019-04-12
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "utils.h"
#include "temperature.h"
#include "os.h"
#include "processor.h"
#include "requests.h"
#include "ram.h"
#include "ramlist.h"
#include "storage.h"
#include "storagelist.h"
#include "fs.h"
#include "fslist.h"
#include "graphics.h"
#include "graphicslist.h"
#include "system.h"

std::vector<std::string> requests;
OutputStyle style = OutputStyle::Default;

OperatingSystem compOS;
System compSys;
Processor compCPU;
RAMList compRAM;
GraphicsList compGPU;
StorageList compStorage;
FileSystemList compFS;

int main(int argc, const char *argv[])
{
  std::string *request = new std::string();
  runCommand("echo");

  handleArgs(argc, argv, request);
  parseRequests(request);

  compOS = new OperatingSystem(CGOGGLES_OS);
  compSys = new System(CGOGGLES_OS);
  compCPU = new Processor(CGOGGLES_OS);
  compRAM = new RAMList(CGOGGLES_OS);
  compGPU = new GraphicsList(CGOGGLES_OS);
  compStorage = new StorageList(CGOGGLES_OS);
  compFS = new FileSystemList(CGOGGLES_OS);

  outputRequests();

  return EXIT_SUCCESS;
}
