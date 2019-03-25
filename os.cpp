/**
*  @file      os.cpp
*  @brief     The implementation for the operating system handling methods.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "os.h"
#include "semver.h"
#include "utils.h"

#pragma region "Constructors"
/**
* @brief Construct a new Operating System object
*/
OperatingSystem::OperatingSystem()
{
  platform = std::make_unique<std::string>();
  caption = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  bit = std::make_unique<std::uint8_t>();
  installTime = std::make_unique<std::tm>();
  bootTime = std::make_unique<std::tm>();
  curTime = std::make_unique<std::tm>();
  kernel = std::make_unique<SemVer>();
  version = std::make_unique<SemVer>();
}

/**
* @brief Construct a new Operating System object with help from the assistants
*
* @param plt The platform of the system
*/
OperatingSystem::OperatingSystem(std::uint8_t plt)
{
  platform = std::make_unique<std::string>();
  caption = std::make_unique<std::string>();
  serial = std::make_unique<std::string>();
  bit = std::make_unique<std::uint8_t>();
  installTime = std::make_unique<std::tm>();
  bootTime = std::make_unique<std::tm>();
  curTime = std::make_unique<std::tm>();
  kernel = std::make_unique<SemVer>();
  version = std::make_unique<SemVer>();

  switch (plt)
  {
  case OS_WIN:
    GetWin();
    break;
  case OS_MAC:
    GetMac();
    break;
  case OS_LUX:
    GetLux();
    break;
  }
}

/**
* @brief Destroy the Operating System object
*/
OperatingSystem::~OperatingSystem()
{
  platform.reset();
  caption.reset();
  serial.reset();
  bit.reset();
  installTime.reset();
  bootTime.reset();
  curTime.reset();
  kernel.reset();
  version.reset();
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the OS information for Darwin systems
*/
void OperatingSystem::GetMac()
{
  platform = std::make_unique<std::string>("Darwin");
}

/**
* @brief Fills in the OS information for Windows systems
*/
void OperatingSystem::GetWin()
{
  std::unique_ptr<std::string> wmic = std::make_unique<std::string>(getWmicPath());
  std::unique_ptr<std::map<std::string, std::string>> dataMap = std::make_unique<std::map<std::string, std::string>>(runMultiWmic("os get Caption,SerialNumber,OSArchitecture,Version,Version,InstallDate,LastBootUpTime,LocalDateTime", wmic.get()));
  std::unique_ptr<std::string> temp = std::make_unique<std::string>();

  (*platform) = "Windows";
  (*caption) = (*dataMap)["Caption"];
  (*serial) = (*dataMap)["SerialNumber"];
  (*bit) = std::stoi((*dataMap)["OSArchitecture"].erase(3));
  (*version) = new SemVer((*dataMap)["Version"], 0b11010u);
  (*kernel) = new SemVer((*dataMap)["Version"], 0b11010u);

  (*temp) = (*dataMap)["InstallDate"];
  installTime->tm_year = std::stoi(temp->substr(0, 4)) - 1900;
  installTime->tm_mon = std::stoi(temp->substr(4, 2)) - 1;
  installTime->tm_mday = std::stoi(temp->substr(6, 2));
  installTime->tm_hour = std::stoi(temp->substr(8, 2));
  installTime->tm_min = std::stoi(temp->substr(10, 2));
  installTime->tm_sec = std::stoi(temp->substr(12, 2));

  (*temp) = (*dataMap)["LastBootUpTime"];
  bootTime->tm_year = std::stoi(temp->substr(0, 4)) - 1900;
  bootTime->tm_mon = std::stoi(temp->substr(4, 2)) - 1;
  bootTime->tm_mday = std::stoi(temp->substr(6, 2));
  bootTime->tm_hour = std::stoi(temp->substr(8, 2));
  bootTime->tm_min = std::stoi(temp->substr(10, 2));
  bootTime->tm_sec = std::stoi(temp->substr(12, 2));

  (*temp) = (*dataMap)["LocalDateTime"];
  curTime->tm_year = std::stoi(temp->substr(0, 4)) - 1900;
  curTime->tm_mon = std::stoi(temp->substr(4, 2)) - 1;
  curTime->tm_mday = std::stoi(temp->substr(6, 2));
  curTime->tm_hour = std::stoi(temp->substr(8, 2));
  curTime->tm_min = std::stoi(temp->substr(10, 2));
  curTime->tm_sec = std::stoi(temp->substr(12, 2));
}

/**
* @brief Fills in the OS information for Linux systems
*/
void OperatingSystem::GetLux()
{
  platform = std::make_unique<std::string>("Linux");
}
#pragma endregion "Constructors' Assistants"

#pragma region "Operators"
/**
* @brief Sets one Operating System equal to another
*
* @param o The Operating System to copy from
*/
void OperatingSystem::operator=(OperatingSystem *o)
{
  (*platform) = (*o->platform);
  (*caption) = (*o->caption);
  (*serial) = (*o->serial);
  (*bit) = (*o->bit);
  (*installTime) = (*o->installTime);
  (*bootTime) = (*o->bootTime);
  (*curTime) = (*o->curTime);
  (*kernel) = (*o->kernel);
  (*version) = (*o->version);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the platform
*
* @return std::string The platform
*/
std::string OperatingSystem::Platform()
{
  return (*platform);
}

/**
* @brief Returns a copy of the caption
*
* @return std::string The caption
*/
std::string OperatingSystem::Caption()
{
  return (*caption);
}

/**
* @brief Returns a copy of the serial number
*
* @return std::string The serial number
*/
std::string OperatingSystem::Serial()
{
  return (*serial);
}

/**
* @brief Returns a copy of the bit
*
* @return std::string The bit
*/
std::uint8_t OperatingSystem::Bit()
{
  return (*bit);
}

/**
* @brief Returns a copy of the install time
*
* @return std::string The install time
*/
std::tm OperatingSystem::InstallTime()
{
  return (*installTime);
}

/**
* @brief Returns a copy of the boot time with a specific format
*
* @param  fmt     How to format the time
* @return std::tm The formatted time string
*/
std::string OperatingSystem::InstallTime(const std::string &fmt)
{
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();
  (*buffer) << std::put_time(installTime.get(), fmt.c_str());
  return buffer->str();
}

/**
* @brief Returns a copy of the boot time
*
* @return std::string The boot time
*/
std::tm OperatingSystem::BootTime()
{
  return (*bootTime);
}

/**
* @brief Returns a copy of the install time with a specific format
*
* @param  fmt     How to format the time
* @return std::tm The formatted time string
*/
std::string OperatingSystem::BootTime(const std::string &fmt)
{
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();
  (*buffer) << std::put_time(bootTime.get(), fmt.c_str());
  return buffer->str();
}

/**
* @brief Returns a copy of the current time
*
* @return std::string The current time
*/
std::tm OperatingSystem::CurTime()
{
  return (*curTime);
}

/**
* @brief Returns a copy of the current time with a specific format
*
* @param  fmt     How to format the time
* @return std::tm The formatted time string
*/
std::string OperatingSystem::CurTime(const std::string &fmt)
{
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();
  (*buffer) << std::put_time(curTime.get(), fmt.c_str());
  return buffer->str();
}

/**
* @brief Returns a copy of the kernel version
*
* @return std::string The kernel version
*/
SemVer OperatingSystem::Kernel()
{
  return (*kernel);
}

/**
* @brief Returns a copy of the version
*
* @return std::string The version
*/
SemVer OperatingSystem::Version()
{
  return (*version);
}
#pragma endregion "Accessors"

#pragma region "Static Methods"
/**
* @brief Checks if the given path is a file
*
* @param  path  The path to check
* @return true  The file at the path does exist
* @return false The file at the path does NOT exist
*/
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

/**
* @brief Retrieves a given environment variable
*
* @param  key         The environment variable
* @return std::string The value of the given environment variable
*/
std::string getEnvVar(const std::string &key)
{
  char const *val = std::getenv(key.c_str());
  return val == NULL ? std::string() : std::string(val);
}

/**
* @brief Joins a list of paths with the system's path separator
*
* @param  paths       The list of paths to join
* @return std::string The joint path
*/
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

/**
* @brief Gets the temporary directory for the system
*
* @return std::string The temporary directory
*/
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

/**
* @brief Runs a command and retrieves output from stdout
*
* @param  cmd         The command to run
* @return std::string The command's output
*/
std::string runCommand(const std::string &cmd)
{
  std::unique_ptr<std::string> path = std::make_unique<std::string>(joinPath({getTempDir(), "cgoggles.txt"}));
  std::unique_ptr<std::ifstream> file = std::make_unique<std::ifstream>((*path));
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();

  std::system((cmd + " > " + (*path)).c_str());
  (*buffer) << file->rdbuf();

  return buffer->str();
}

/**
* @brief Runs a WMIC query and retrieves the result
*
* @param  query       The query to run
* @param  path        The WMIC execution path
* @return std::string The query's result
*/
std::string runWmic(const std::string &query, std::string *path)
{
  std::unique_ptr<std::string> temp = std::make_unique<std::string>(runCommand((*path) + " " + query + " /format:list"));
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();

  for (size_t i = 0; i < temp->length(); i++)
  {
    if (int((*temp)[i]) < 1 || int((*temp)[i]) > 0xFF)
    {
      continue;
    }
    (*buffer) << (*temp)[i];
  }
  (*temp) = buffer->str();
  buffer.reset();

  temp->erase(0, temp->find_first_of('=') + 1);
  temp->erase(temp->find_last_of('\r'));

  return (*temp);
}

std::map<std::string, std::string> runMultiWmic(const std::string &query, std::string *path)
{
  std::unique_ptr<std::map<std::string, std::string>> ret = std::make_unique<std::map<std::string, std::string>>();
  std::unique_ptr<std::string> temp = std::make_unique<std::string>(runCommand((*path) + " " + query + " /format:list"));
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();
  std::unique_ptr<std::vector<std::string>> lines = std::make_unique<std::vector<std::string>>();

  for (size_t i = 0; i < temp->length(); i++)
  {
    if (int((*temp)[i]) < 1 || int((*temp)[i]) > 0xFF)
    {
      continue;
    }
    (*buffer) << (*temp)[i];
  }
  (*temp) = buffer->str();
  buffer.reset();

  temp->erase(0, 4);
  temp->erase(temp->length() - 5);
  splitStringVector((*temp), "\r\n", lines.get());
  temp.reset();

  for (size_t i = 0; i < lines->size(); i++)
  {
    (*ret)[(*lines)[i].substr(0, (*lines)[i].find_first_of('='))] = (*lines)[i].substr((*lines)[i].find_first_of('=') + 1);
  }
  lines.reset();

  return (*ret);
}

std::vector<std::map<std::string, std::string>> runListMultiWmic(const std::string &query, std::string *path)
{
  std::unique_ptr<std::vector<std::map<std::string, std::string>>> ret = std::make_unique<std::vector<std::map<std::string, std::string>>>();
  std::unique_ptr<std::map<std::string, std::string>> acc = std::make_unique<std::map<std::string, std::string>>();
  std::unique_ptr<std::string> temp = std::make_unique<std::string>(runCommand((*path) + " " + query + " /format:list"));
  std::unique_ptr<std::stringstream> buffer = std::make_unique<std::stringstream>();
  std::unique_ptr<std::vector<std::string>> lines = std::make_unique<std::vector<std::string>>();

  for (size_t i = 0; i < temp->length(); i++)
  {
    if (int((*temp)[i]) < 1 || int((*temp)[i]) > 0xFF)
    {
      continue;
    }
    (*buffer) << (*temp)[i];
  }
  (*temp) = buffer->str();
  buffer.reset();

  temp->erase(0, 4);
  temp->erase(temp->length() - 5);
  splitStringVector((*temp), "\r\n", lines.get());
  temp.reset();

  for (size_t i = 0; i < lines->size(); i++)
  {
    if (i < lines->size() && (*lines)[i] == "" && (*lines)[i + 1] == "")
    {
      ret->push_back((*acc));
      acc->clear();
      i += 2;
    }
    (*acc)[(*lines)[i].substr(0, (*lines)[i].find_first_of('='))] = (*lines)[i].substr((*lines)[i].find_first_of('=') + 1);
  }
  lines.reset();
  acc.reset();

  return (*ret);
}
#pragma endregion "Static Methods"
