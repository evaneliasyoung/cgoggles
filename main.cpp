/**
*  @file      main.cpp
*  @brief     The main entry point for cgoggles.
*
*  @author    Evan Elias Young
*  @date      2019-03-11
*  @date      2019-04-01
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "argh.h"
#include "utils.h"
#include "temperature.h"
#include "os.h"
#include "processor.h"
#include "requests.h"
#include "storage.h"
#include "storagelist.h"
#include "fs.h"
#include "fslist.h"
#include "graphics.h"
#include "graphicslist.h"

#define CGOGGLES_VERSION_ 0x000200

std::vector<std::string> requests;
OutputStyle style = OutputStyle::Default;

OperatingSystem compOS;
Processor compCPU;
GraphicsList compGPU;
StorageList compStorage;
FileSystemList compFS;

void outputVersion()
{
  std::cout << ((CGOGGLES_VERSION_ & 0xFF0000) >> (4 * 4)) << '.';
  std::cout << ((CGOGGLES_VERSION_ & 0x00FF00) >> (2 * 4)) << '.';
  std::cout << ((CGOGGLES_VERSION_ & 0x0000FF) >> (0 * 4)) << std::endl;
}

void outputHelp()
{
  // NOTE: JSON output disabled until further notice
  // std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [-l|--list|-j|--json|-m|--minjson] -get=[<args>]" << std::endl;
  std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [-l|--list] -get=[<args>]" << std::endl;
  std::cout << "example: cgoggles -get=cpu.Brand,cpu.Cores,cpu.Speed" << std::endl;
}

int handleArgs(const char *argv[], std::string *request)
{
  argh::parser cmdl(argv);

  if (cmdl[{"v", "ver", "version"}])
  {
    outputVersion();
    std::exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
  }

  if (cmdl[{"h", "help"}])
  {
    outputHelp();
    std::exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
  }

  // NOTE: JSON output disabled until further notice
  //       It's really quite a mess without a JSON library
  // if (cmdl[{"m", "minjson"}])
  // {
  //   if (cmdl[{"j", "json", "l", "list"}]) {
  //     outputHelp();
  //     return EXIT_FAILURE;
  //   }

  //   style = OutputStyle::MinJSON;
  // }

  // if (cmdl[{"j", "json"}])
  // {
  //   if (cmdl[{"m", "minjson", "l", "list"}]) {
  //     outputHelp();
  //     return EXIT_FAILURE;
  //   }

  //   style = OutputStyle::JSON;
  // }

  if (cmdl[{"l", "list"}])
  {
    style = OutputStyle::List;
  }

  if (!(cmdl({"g", "get"}) >> (*request)))
  {
    outputHelp();
    std::exit(EXIT_FAILURE);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
  std::unique_ptr<std::string> request = std::make_unique<std::string>();

  if (handleArgs(argv, request.get()) != EXIT_SUCCESS)
  {
    return EXIT_FAILURE;
  }

  parseRequests(request.get());
  request.reset();

  compOS = new OperatingSystem(CGOGGLES_OS);
  compCPU = new Processor(CGOGGLES_OS);
  compGPU = new GraphicsList(CGOGGLES_OS);
  compStorage = new StorageList(CGOGGLES_OS);
  compFS = new FileSystemList(CGOGGLES_OS);

  runCommand("echo");

  outputRequests();

  return EXIT_SUCCESS;
}
