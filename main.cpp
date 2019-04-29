/**
*  @file      main.cpp
*  @brief     The main entry point for cgoggles
*
*  @author    Evan Elias Young
*  @date      2019-03-11
*  @date      2019-04-29
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

/**
* @brief The list of requests to retrieve
*/
std::vector<std::string> requests;

/**
* @brief The OutputStyle to use when presenting the data
*/
OutputStyle style = OutputStyle::Default;

/**
* @brief Whether or not to pretty-print the data
*
*/
bool pretty = true;

/**
* @brief The computer's operating system
*/
OperatingSystem compOS;

/**
* @brief The computer's system info
*/
System compSys;
/**
* @brief The computer's processor
*/
Processor compCPU;
/**
* @brief The computer's memory chip(s)
*/
RAMList compRAM;
/**
* @brief The computer's graphics processor(s)
*/
GraphicsList compGPU;
/**
* @brief The computer's storage drive(s)
*/
StorageList compStorage;
/**
* @brief The computer's file system(s)
*/
FileSystemList compFS;

/**
* @brief The main point of entry for cgoggles
*
* @param argc The count of arguments
* @param argv The value of arguments
* @return int The exit code
*/
int main(int argc, const char *argv[])
{
  std::string *request = new std::string();
  runCommand("echo");

  handleArgs(argc, argv, request);
  parseRequests(request);

  outputRequests();

  return EXIT_SUCCESS;
}
