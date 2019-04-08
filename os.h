/**
*  @file      os.h
*  @brief     The interface for the operating system handling methods.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-04-08
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_OS_H_ // include guard
#define CGOGGLES_OS_H_

#include "pch.h"
#include "semver.h"

#ifndef OS_DOS
#define OS_DOS 1
#endif // OS_DOS

#ifndef OS_WIN
#define OS_WIN 2
#endif // OS_WIN

#ifndef OS_LUX
#define OS_LUX 3
#endif // OS_LUX

#ifndef OS_MAC
#define OS_MAC 4
#endif // OS_MAC

#ifndef OS_ERR
#define OS_ERR 0
#endif // OS_ERR

#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
#define CGOGGLES_OS OS_DOS
#elif defined(_WIN16) || defined(__TOS_WIN__) || defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN64)
#define CGOGGLES_OS OS_WIN
#elif defined(__linux__)
#define CGOGGLES_OS OS_LUX
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__)
#define CGOGGLES_OS OS_MAC
#else
#define CGOGGLES_OS OS_ERR
#endif

#if CGOGGLES_OS == OS_WIN || CGOGGLES_OS == OS_DOS
#define P_POPEN _popen
#define P_CLOSE _pclose
#else
#define P_POPEN popen
#define P_CLOSE pclose
#endif

/**
* @brief The directory separator for the current OS
*/
const char dirSep = CGOGGLES_OS <= OS_WIN ? '\\' : '/';

/**
* @brief Represents an computer's Operating System
*
*/
class OperatingSystem
{
private:
  /**
  * @brief The platform of the system
  */
  std::unique_ptr<std::string> platform;

  /**
  * @brief The common name of the system
  */
  std::unique_ptr<std::string> caption;

  /**
  * @brief The serial number of the system
  */
  std::unique_ptr<std::string> serial;

  /**
  * @brief The number of bits for the system
  */
  std::unique_ptr<std::uint8_t> bit;

  /**
  * @brief The install time of the system
  */
  std::unique_ptr<std::tm> installTime;

  /**
  * @brief The boot time of the system
  */
  std::unique_ptr<std::tm> bootTime;

  /**
  * @brief The current time of the system
  */
  std::unique_ptr<std::tm> curTime;

  /**
  * @brief The kernel version of the system
  */
  std::unique_ptr<SemVer> kernel;

  /**
  * @brief The OS version of the system
  */
  std::unique_ptr<SemVer> version;

  void GetMac();
  void GetWin();
  void GetLux();

public:
  OperatingSystem();
  OperatingSystem(std::uint8_t plt);
  ~OperatingSystem();
  void operator=(OperatingSystem *o);
  std::string Platform();
  std::string Caption();
  std::string Serial();
  std::uint8_t Bit();
  std::tm InstallTime();
  std::string InstallTime(const std::string &fmt);
  std::tm BootTime();
  std::string BootTime(const std::string &fmt);
  std::tm CurTime();
  std::string CurTime(const std::string &fmt);
  SemVer Kernel();
  SemVer Version();
};

bool fileExists(const std::string &path);
std::string getEnvVar(const std::string &key);
std::string joinPath(std::initializer_list<std::string> paths);
std::string getTempDir();
std::string runCommand(const std::string &cmd);
std::string runWmic(const std::string &query, std::string *path);
std::map<std::string, std::string> runMultiWmic(const std::string &query, std::string *path);
std::vector<std::map<std::string, std::string>> runListMultiWmic(const std::string &query, std::string *path);
std::string getWmicPath();

#endif // CGOGGLES_OS_H_
