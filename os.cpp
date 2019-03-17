/**
*  @file      os.cpp
*  @brief     The implementation for the operating system handling methods.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-17
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "os.h"
#include "semver.h"

OperatingSystem::OperatingSystem()
{
  platform = std::make_unique<std::string>();
  kernel = std::make_unique<SemVer>();
  version = std::make_unique<SemVer>();

  switch (CGOGGLES_OS)
  {
  case OS_WIN:
    GetWin();
    break;
  case OS_MAC:
    GetMac();
    break;
  case OS_LUX:
    GetLux();
  default:
    break;
  }
}

OperatingSystem::~OperatingSystem()
{
  platform.reset();
  kernel.reset();
  version.reset();
}

void OperatingSystem::GetMac()
{
  platform = std::make_unique<std::string>("Darwin");
}
void OperatingSystem::GetWin()
{
  std::unique_ptr<std::string> temp = std::make_unique<std::string>(runCommand("ver"));
  std::unique_ptr<std::smatch> mt = std::make_unique<std::smatch>();

  platform = std::make_unique<std::string>("Windows");

  if (std::regex_search((*temp), (*mt), std::regex(R"((\d+\.?)+)", std::regex::ECMAScript)))
  {
    version = std::unique_ptr<SemVer>(new SemVer((*mt).str(), 0b11011u));
    kernel = std::unique_ptr<SemVer>(new SemVer((*mt).str(), 0b11011u));
  }
}
void OperatingSystem::GetLux()
{
  platform = std::make_unique<std::string>("Linux");
}

std::string OperatingSystem::Platform()
{
  return (*platform);
}
SemVer OperatingSystem::Kernel()
{
  return (*kernel);
}
SemVer OperatingSystem::Version()
{
  return (*version);
}

bool fileExists(const std::string &path)
{
  if (std::FILE *file = std::fopen(path.c_str(), "r"))
  {
    std::fclose(file);
    return true;
  }
  else
  {
    return false;
  }
}

std::string getEnvVar(const std::string &key)
{
  char const *val = std::getenv(key.c_str());
  return val == NULL ? std::string() : std::string(val);
}

std::string joinPath(std::initializer_list<std::string> paths)
{
  std::unique_ptr<std::stringstream> ss = std::make_unique<std::stringstream>();
  for (std::string s : paths)
  {
    (*ss) << s;
    if (s != (*(paths.end() - 1)))
    {
      (*ss) << dirSep;
    }
  }
  return ss->str();
}

std::string getTempDir()
{
  std::unique_ptr<std::string> tempDir = std::make_unique<std::string>();

  if (CGOGGLES_OS != OS_ERR)
  {
    if ((*tempDir).empty())
    {
      (*tempDir) = getEnvVar("TMP");
    }
    if ((*tempDir).empty())
    {
      (*tempDir) = getEnvVar("TEMP");
    }
    if ((*tempDir).empty())
    {
      (*tempDir) = getEnvVar("TMPDIR");
    }
    if ((*tempDir).empty())
    {
      (*tempDir) = getEnvVar("TEMPDIR");
    }
    if ((*tempDir).empty())
    {
      if (CGOGGLES_OS != OS_WIN)
      {
        (*tempDir) = "/tmp";
      }
    }
  }

  return (*tempDir);
}

std::string runCommand(const std::string &cmd)
{
  std::unique_ptr<std::string> path = std::make_unique<std::string>(joinPath({getTempDir(), "cgoggles.txt"}));
  std::unique_ptr<std::ifstream> file = std::make_unique<std::ifstream>((*path));
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();

  std::system((cmd + " > " + (*path)).c_str());
  (*buffer) << file->rdbuf();

  return buffer->str();
}
