/**
*  @file      main.cpp
*  @brief     The main entry point for cgoggles.
*
*  @author    Evan Elias Young
*  @date      2019-03-11
*  @date      2019-03-22
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

#define CGOGGLES_VERSION_ 0x000100

std::vector<std::string> requests;
OutputStyle style = OutputStyle::Default;

OperatingSystem compOS;
Processor compCPU;
std::vector<Storage> compStorage;

void outputVersion()
{
  std::cout << ((CGOGGLES_VERSION_ & 0xFF0000) >> (4 * 4)) << '.';
  std::cout << ((CGOGGLES_VERSION_ & 0x00FF00) >> (2 * 4)) << '.';
  std::cout << ((CGOGGLES_VERSION_ & 0x0000FF) >> (0 * 4)) << std::endl;
}

void outputHelp()
{
  std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [--list] <command> [<args>]" << std::endl;
  std::cout << "example: cgoggles -get=cpu" << std::endl;
}

int handleArgs(const char *argv[], std::string *request)
{
  argh::parser cmdl(argv);

  if (cmdl[{"v", "ver", "version"}])
  {
    outputVersion();
    return EXIT_SUCCESS;
  }

  if (cmdl[{"h", "help"}])
  {
    outputHelp();
    return EXIT_SUCCESS;
  }

  if (cmdl[{"list"}])
  {
    style = OutputStyle::List;
  }

  if (!(cmdl({"g", "get"}) >> (*request)))
  {
    outputHelp();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
  // std::unique_ptr<std::string> request = std::make_unique<std::string>();

  // if (handleArgs(argv, request.get()) != EXIT_SUCCESS)
  // {
  //   return EXIT_FAILURE;
  // }

  // parseRequests(request.get());
  // request.reset();
  runCommand("echo");

  // outputRequests();

  return EXIT_SUCCESS;
}
