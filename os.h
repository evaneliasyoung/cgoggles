/**
*  @file      os.h
*  @brief     The interface for the operating system handling methods.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-03-15=6
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_OS_H_ // include guard
#define CGOGGLES_OS_H_

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

const char dirSep = CGOGGLES_OS <= OS_WIN ? '\\' : '/';

bool fileExists(const std::string &path);
std::string getEnvVar(const std::string &key);
std::string joinPath(std::initializer_list<std::string> paths);
std::string getTempDir();
std::string runCommand(const std::string &cmd);

#endif // CGOGGLES_OS_H_
