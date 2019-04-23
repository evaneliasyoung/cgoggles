/**
*  @file      utils.h
*  @brief     The interface for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-04-23
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_UTILS_H_
#define CGOGGLES_UTILS_H_

#include "pch.h"

#define CGOGGLES_VERSION_ 0x000302
#if _WIN32 || _WIN64
#if _WIN64
#define CGOGGLES_ENVIRONMENT_ 64
#else
#define CGOGGLES_ENVIRONMENT_ 32
#endif
#elif __GNUC__
#if __x86_64__ || __ppc64__
#define CGOGGLES_ENVIRONMENT_ 64
#else
#define CGOGGLES_ENVIRONMENT_ 32
#endif
#endif

#if CGOGGLES_ENVIRONMENT_ == 64
static_assert(sizeof(void *) == 8, "Void pointer should be 8 bytes long.");
#elif CGOGGLES_ENVIRONMENT_ == 32
static_assert(sizeof(void *) == 4, "Void pointer should be 4 bytes long.");
#else
#error "Must define CGOGGLES_ENVIRONMENT_"
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
extern bool pretty;

void splitStringVector(const std::string &s, const std::string &d, std::vector<std::string> *v);
void removeDuplicates(std::vector<std::string> *v);
bool contains(std::vector<std::string> *v, const std::string &s);
void rtrim(std::string *s, const char *t = " \t\n\r\f\v");
void ltrim(std::string *s, const char *t = " \t\n\r\f\v");
void trim(std::string *s, const char *t = " \t\n\r\f\v");
std::string rtrim(std::string s, const char *t = " \t\n\r\f\v");
std::string ltrim(std::string s, const char *t = " \t\n\r\f\v");
std::string trim(std::string s, const char *t = " \t\n\r\f\v");
bool startswith(const std::string &s, const std::string &r);
bool endswith(const std::string &s, const std::string &r);
bool splitKeyValuePair(const std::string &base, std::string *k, std::string *v, const bool &doTrim = true, const char &spl = ':');
template <class T, class R>
bool tryGetValue(const std::map<T, R> &m, const T &k, R *v)
{
  auto mapFind = m.find(k);
  if (mapFind != m.end())
  {
    (*v) = mapFind->second;
    return true;
  }
  return false;
}
bool readFile(const std::string &p, std::string *o);
std::string siUnits(const std::uint64_t &num, const std::string &suff = "", const std::uint8_t &plc = 2);
std::string siUnits(const std::uint32_t &num, const std::string &suff = "", const std::uint8_t &plc = 2);
std::string siUnits(const float &num, const std::string &suff = "", const std::uint8_t &plc = 2);
void outputVersion();
void outputList(const std::string &cat = "");
void outputHelp();
int handleArgs(int argc, const char *argv[], std::string *request);

#endif // CGOGGLES_UTILS_H_
