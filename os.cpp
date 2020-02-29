/**
*  @file      os.cpp
*  @brief     The implementation for the OperatingSystem Class.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "os.h"
#include "semver.h"
#include "utils.h"

#pragma region "Constructors"
/**
* @brief Construct a new OperatingSystem object
*/
OperatingSystem::OperatingSystem()
{
  platform = "";
  caption = "";
  serial = "";
  bit = 0;
  installTime = std::tm();
  bootTime = std::tm();
  curTime = std::tm();
  kernel = SemVer();
  version = SemVer();
}

/**
* @brief Construct a new OperatingSystem object with help from the assistants
*
* @param plt The platform of the system
*/
OperatingSystem::OperatingSystem(std::uint8_t plt)
{
  platform = "";
  caption = "";
  serial = "";
  bit = 0;
  installTime = std::tm();
  bootTime = std::tm();
  curTime = std::tm();
  kernel = SemVer();
  version = SemVer();

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
* @brief Construct a new OperatingSystem object from another OperatingSystem object
*
* @param o The OperatingSystem object to copy from
*/
OperatingSystem::OperatingSystem(const OperatingSystem &o)
{
  platform = o.platform;
  caption = o.caption;
  serial = o.serial;
  bit = o.bit;
  installTime = o.installTime;
  bootTime = o.bootTime;
  curTime = o.curTime;
  kernel = o.kernel;
  version = o.version;
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the OS information for Darwin systems
*/
void OperatingSystem::GetMac()
{
  std::string versionCapts[14] = {
      "Jaguar",
      "Panther",
      "Tiger",
      "Leopard",
      "Snow Leopard",
      "Lion",
      "Mountain Lion",
      "Mavericks",
      "Yosemite",
      "El Capitan",
      "Sierra",
      "High Sierra",
      "Mojave",
      "Catalina"};
  std::string temp;
  std::time_t tempTime;

  platform = "Darwin";
  serial = runCommand("system_profiler SPHardwareDataType | grep Serial | awk '{ print $4; }'");
  trim(&serial);
  bit = std::stoi(runCommand("getconf LONG_BIT"));
  version = new SemVer(runCommand("sysctl -n kern.osproductversion"), 0b11100u);
  kernel = new SemVer(runCommand("sysctl -n kern.osrelease"), 0b11100u);
  caption = version.Minor() > 11 ? "macOS" : "Mac OS X";
  if (version.Major() == 10 && version.Minor() > 1 && version.Minor() < 15)
  {
    caption += " " + versionCapts[version.Minor() - 2];
  }

  temp = runCommand(R"(system_profiler SPInstallHistoryDataType | grep -A 4 -E '^\s{4}(macOS|OS X)' | tail -n1 | awk '{ print $3 $4; }')");
  installTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  installTime.tm_mon = std::stoi(temp.substr(5, 2)) - 1;
  installTime.tm_mday = std::stoi(temp.substr(8, 2));
  installTime.tm_hour = std::stoi(temp.substr(11, 2));
  installTime.tm_min = std::stoi(temp.substr(14, 2));

  tempTime = (std::time_t)std::stoi(runCommand("sysctl kern.boottime | awk '{ print substr($5, 1, length($5) - 1); }'"));
  bootTime = (*std::localtime(&tempTime));

  temp = runCommand(R"(date +"%Y%m%d%H%M%S")");
  curTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  curTime.tm_mon = std::stoi(temp.substr(4, 2)) - 1;
  curTime.tm_mday = std::stoi(temp.substr(6, 2));
  curTime.tm_hour = std::stoi(temp.substr(8, 2));
  curTime.tm_min = std::stoi(temp.substr(10, 2));
  curTime.tm_sec = std::stoi(temp.substr(12, 2));
}

/**
* @brief Fills in the OS information for Windows systems
*/
void OperatingSystem::GetWin()
{
  std::string wmic = getWmicPath();
  std::map<std::string, std::string> dataMap = runMultiWmic("os get Caption,SerialNumber,OSArchitecture,Version,Version,InstallDate,LastBootUpTime,LocalDateTime", &wmic);
  std::string temp;

  platform = "Windows";
  caption = dataMap["Caption"];
  serial = dataMap["SerialNumber"];
  bit = std::stoi(dataMap["OSArchitecture"].erase(3));
  version = new SemVer(dataMap["Version"], 0b11010u);
  kernel = new SemVer(dataMap["Version"], 0b11010u);

  temp = dataMap["InstallDate"];
  installTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  installTime.tm_mon = std::stoi(temp.substr(4, 2)) - 1;
  installTime.tm_mday = std::stoi(temp.substr(6, 2));
  installTime.tm_hour = std::stoi(temp.substr(8, 2));
  installTime.tm_min = std::stoi(temp.substr(10, 2));
  installTime.tm_sec = std::stoi(temp.substr(12, 2));

  temp = dataMap["LastBootUpTime"];
  bootTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  bootTime.tm_mon = std::stoi(temp.substr(4, 2)) - 1;
  bootTime.tm_mday = std::stoi(temp.substr(6, 2));
  bootTime.tm_hour = std::stoi(temp.substr(8, 2));
  bootTime.tm_min = std::stoi(temp.substr(10, 2));
  bootTime.tm_sec = std::stoi(temp.substr(12, 2));

  temp = dataMap["LocalDateTime"];
  curTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  curTime.tm_mon = std::stoi(temp.substr(4, 2)) - 1;
  curTime.tm_mday = std::stoi(temp.substr(6, 2));
  curTime.tm_hour = std::stoi(temp.substr(8, 2));
  curTime.tm_min = std::stoi(temp.substr(10, 2));
  curTime.tm_sec = std::stoi(temp.substr(12, 2));
}

/**
* @brief Fills in the OS information for Linux systems
*/
void OperatingSystem::GetLux()
{
  std::string temp;
  std::time_t t = std::time(0);

  platform = "Linux";
  temp = runCommand("lsb_release -d");
  caption = trim(temp.substr(temp.find_first_of(":") + 1));
  serial = readFile("/sys/devices/virtual/dmi/id/product_serial", &temp) ? trim(temp) : "";
  temp = trim(runCommand("uname -m"));
  bit = endswith(temp, "64") || temp.find("armv8") != std::string::npos ? 64 : 32;
  temp = runCommand("lsb_release -r");
  version = new SemVer(trim(temp.substr(temp.find_first_of(":") + 1)), std::count(temp.begin(), temp.end(), '.') > 0 ? 0b11000u : 0b1000u);
  temp = runCommand("uname -r");
  kernel = new SemVer(trim(temp.substr(0, temp.find_first_of("-"))), 0b11000u);

  temp = runCommand("stat -c %y /var/cache/apt");
  installTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  installTime.tm_mon = std::stoi(temp.substr(5, 2)) - 1;
  installTime.tm_mday = std::stoi(temp.substr(8, 2));
  installTime.tm_hour = std::stoi(temp.substr(11, 2));
  installTime.tm_min = std::stoi(temp.substr(14, 2));
  installTime.tm_sec = std::stoi(temp.substr(17, 2));

  temp = runCommand("uptime -s");
  bootTime.tm_year = std::stoi(temp.substr(0, 4)) - 1900;
  bootTime.tm_mon = std::stoi(temp.substr(5, 2)) - 1;
  bootTime.tm_mday = std::stoi(temp.substr(8, 2));
  bootTime.tm_hour = std::stoi(temp.substr(11, 2));
  bootTime.tm_min = std::stoi(temp.substr(14, 2));
  bootTime.tm_sec = std::stoi(temp.substr(17, 2));

  curTime = (*std::localtime(&t));
}
#pragma endregion "Constructors' Assistants"

#pragma region "Operators"
/**
* @brief Reserves memory for a new OperatingSystem object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *OperatingSystem::operator new(std::size_t size)
{
  void *o = ::new (OperatingSystem);
  return o;
}

/**
* @brief Sets equal two OperatingSystem objects
*
* @param o The OperatingSystem object to copy from
*/
void OperatingSystem::operator=(const OperatingSystem &o)
{
  if (&o == this)
  {
    return;
  }
  platform = o.platform;
  caption = o.caption;
  serial = o.serial;
  bit = o.bit;
  installTime = o.installTime;
  bootTime = o.bootTime;
  curTime = o.curTime;
  kernel = o.kernel;
  version = o.version;
}

/**
* @brief Sets one OperatingSystem equal to another
*
* @param o The OperatingSystem to copy from
*/
void OperatingSystem::operator=(OperatingSystem *o)
{
  platform = o->platform;
  caption = o->caption;
  serial = o->serial;
  bit = o->bit;
  installTime = o->installTime;
  bootTime = o->bootTime;
  curTime = o->curTime;
  kernel = o->kernel;
  version = o->version;
}
#pragma endregion "Operators"

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
  std::stringstream buffer;
  for (std::string s : paths)
  {
    buffer << s;
    if (s != (*(paths.end() - 1)))
    {
      buffer << dirSep;
    }
  }
  return buffer.str();
}

/**
* @brief Gets the temporary directory for the system
*
* @return std::string The temporary directory
*/
std::string getTempDir()
{
  std::string tempDir;

  if (CGOGGLES_OS != OS_ERR)
  {
    if (tempDir.empty())
    {
      tempDir = getEnvVar("TMP");
    }
    if (tempDir.empty())
    {
      tempDir = getEnvVar("TEMP");
    }
    if (tempDir.empty())
    {
      tempDir = getEnvVar("TMPDIR");
    }
    if (tempDir.empty())
    {
      tempDir = getEnvVar("TEMPDIR");
    }
    if (tempDir.empty())
    {
      if (CGOGGLES_OS != OS_WIN)
      {
        tempDir = "/tmp";
      }
    }
  }

  return tempDir;
}

/**
* @brief Runs a command and retrieves output from stdout
*
* @param  cmd         The command to run
* @return std::string The command's output
*/
std::string runCommand(const std::string &cmd)
{
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&P_PCLOSE)> pipe(P_POPEN(cmd.c_str(), "r"), P_PCLOSE);
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
  {
    result += buffer.data();
  }

  return result;
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
  std::string temp = runCommand((*path) + " " + query + " /format:list");
  std::stringstream buffer;

  for (size_t i = 0; i < temp.length(); ++i)
  {
    if (int(temp[i]) < 1 || int(temp[i]) > 0xFF)
    {
      continue;
    }
    buffer << temp[i];
  }
  temp = buffer.str();

  temp.erase(0, temp.find_first_of('=') + 1);
  temp.erase(temp.find_last_of('\r'));

  return temp;
}

/**
* @brief Runs a WMIC multi-key-query and retrieves the result
*
* @param  query                              The query to run
* @param  path                               The WMIC execution path
* @return std::map<std::string, std::string> The query's result
*/
std::map<std::string, std::string> runMultiWmic(const std::string &query, std::string *path)
{
  std::map<std::string, std::string> ret;
  std::string temp = runCommand((*path) + " " + query + " /format:list");
  std::stringstream buffer;
  std::vector<std::string> lines;

  for (size_t i = 0; i < temp.length(); ++i)
  {
    if (int(temp[i]) < 1 || int(temp[i]) > 0xFF)
    {
      continue;
    }
    buffer << temp[i];
  }
  temp = buffer.str();

  temp.erase(0, 4);
  temp.erase(temp.length() - 5);
  splitStringVector(temp, "\r\n", &lines);

  for (size_t i = 0; i < lines.size(); ++i)
  {
    ret[lines[i].substr(0, lines[i].find_first_of('='))] = lines[i].substr(lines[i].find_first_of('=') + 1);
  }

  return ret;
}

/**
* @brief Runs a WMIC multi-key-multi-object-query and retrieves the result
*
* @param query                                            The query to run
* @param path                                             The WMIC execution path
* @return std::vector<std::map<std::string, std::string>> The query's result
*/
std::vector<std::map<std::string, std::string>> runListMultiWmic(const std::string &query, std::string *path)
{
  std::vector<std::map<std::string, std::string>> ret;
  std::map<std::string, std::string> acc;
  std::string temp = runCommand((*path) + " " + query + " /format:list");
  std::stringstream buffer;
  std::vector<std::string> lines;

  for (size_t i = 0; i < temp.length(); ++i)
  {
    if (int(temp[i]) < 1 || int(temp[i]) > 0xFF)
    {
      continue;
    }
    buffer << temp[i];
  }
  temp = buffer.str();

  temp.erase(0, 4);
  temp.erase(temp.length() - 4);
  splitStringVector(temp, "\r\n", &lines);

  for (size_t i = 0; i < lines.size(); ++i)
  {
    if (i < lines.size() && lines[i] == "")
    {
      ret.push_back(acc);
      acc.clear();
      ++i;
      continue;
    }
    acc[lines[i].substr(0, lines[i].find_first_of('='))] = lines[i].substr(lines[i].find_first_of('=') + 1);
  }

  return ret;
}

/**
* @brief Get the WMIC path for Windows
*
* @return std::string The WMIC path
*/
std::string getWmicPath()
{
  std::string wmicPath = joinPath({getEnvVar("WINDIR"), "system32", "wbem", "wmic.exe"});

  return fileExists(wmicPath) ? wmicPath : "wmic.exe";
}
#pragma endregion "Static Methods"
