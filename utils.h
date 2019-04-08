/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-04-08
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_UTILS_H_
#define CGOGGLES_UTILS_H_

#include "pch.h"

#define CGOGGLES_VERSION_ 0x000200
#if _WIN32 || _WIN64
#if _WIN64
#define CGOGGLES_ENVIRONMENT_ 0x40u
#else
#define CGOGGLES_ENVIRONMENT_ 0x20u
#endif
#elif __GNUC__
#if __x86_64__ || __ppc64__
#define CGOGGLES_ENVIRONMENT_ 0x40u
#else
#define CGOGGLES_ENVIRONMENT_ 0x20u
#endif
#else
#define CGOGGLES_ENVIRONMENT_ 0x20u
#endif

enum class OutputStyle : std::uint8_t
{
  Default,
  List,
  JSON,
  MinJSON
};

extern std::vector<std::string> requests;
extern OutputStyle style;

void splitStringVector(const std::string &s, const std::string &d, std::vector<std::string> *v);
void removeDuplicates(std::vector<std::string> *v);
bool contains(std::vector<std::string> *v, const std::string &s);
void rtrim(std::string *s, const char *t = " \t\n\r\f\v");
void ltrim(std::string *s, const char *t = " \t\n\r\f\v");
void trim(std::string *s, const char *t = " \t\n\r\f\v");
std::string rtrim(std::string s, const char *t = " \t\n\r\f\v");
std::string ltrim(std::string s, const char *t = " \t\n\r\f\v");
std::string trim(std::string s, const char *t = " \t\n\r\f\v");
void outputVersion();
void outputList(const std::string &cat = "");
void outputHelp();
int handleArgs(int argc, const char *argv[], std::string *request);

#endif // CGOGGLES_UTILS_H_
