/**
*  @file      os.h
*  @brief     The interface for the OperatingSystem class.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_OS_H_ // include guard
#define CGOGGLES_OS_H_

#include "pch.h"
#include "semver.h"

#ifndef OS_DOS
/**
* @brief The internal number for the DOS operating system
*/
#define OS_DOS 1
#endif // OS_DOS

#ifndef OS_WIN
/**
* @brief The internal number for the Windows operating system
*/
#define OS_WIN 2
#endif // OS_WIN

#ifndef OS_LUX
/**
* @brief The internal number for the Linux operating system
*/
#define OS_LUX 3
#endif // OS_LUX

#ifndef OS_MAC
/**
* @brief The internal number for the Mac operating system
*/
#define OS_MAC 4
#endif // OS_MAC

#ifndef OS_ERR
/**
* @brief The internal number for the unknown operating system
*/
#define OS_ERR 0
#endif // OS_ERR

#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
/**
* @brief The operating system on the current system
*/
#define CGOGGLES_OS OS_DOS
#elif defined(_WIN16) || defined(__TOS_WIN__) || defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__) || defined(_WIN64)
/**
* @brief The operating system on the current system
*/
#define CGOGGLES_OS OS_WIN
#elif defined(__linux__)
/**
* @brief The operating system on the current system
*/
#define CGOGGLES_OS OS_LUX
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__)
/**
* @brief The operating system on the current system
*/
#define CGOGGLES_OS OS_MAC
#else
/**
* @brief The operating system on the current system
*/
#define CGOGGLES_OS OS_ERR
#endif

#if CGOGGLES_OS == OS_WIN || CGOGGLES_OS == OS_DOS
/**
* @brief The portable popen
*/
#define P_POPEN _popen
/**
* @brief The portable pclose
*/
#define P_PCLOSE _pclose
#else
/**
* @brief The portable popen
*/
#define P_POPEN popen
/**
* @brief The portable pclose
*/
#define P_PCLOSE pclose
#endif

/**
* @brief The directory separator for the current OS
*/
const char dirSep = CGOGGLES_OS <= OS_WIN ? '\\' : '/';

/**
* @brief Represents a computer's Operating System
*/
class OperatingSystem
{
private:
  void GetMac();
  void GetWin();
  void GetLux();

public:
  OperatingSystem();
  OperatingSystem(std::uint8_t plt);
  OperatingSystem(const OperatingSystem &o);
  void *operator new(std::size_t size);
  void operator=(const OperatingSystem &o);
  void operator=(OperatingSystem *o);
  std::string platform;
  std::string caption;
  std::string serial;
  std::uint8_t bit;
  std::tm installTime;
  std::tm bootTime;
  std::tm curTime;
  SemVer kernel;
  SemVer version;
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
