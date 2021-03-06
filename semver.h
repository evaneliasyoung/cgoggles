/**
*  @file      semver.h
*  @brief     The interface for the SemVer class.
*
*  @author    Evan Elias Young
*  @date      2019-03-17
*  @date      2019-04-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_SEMVER_H_
#define CGOGGLES_SEMVER_H_

#include "pch.h"

/**
* @brief Represents a Semantic Version, according to standard 2.0.0
*/
class SemVer
{
private:
  /**
  * @brief The underlying value of the SemVer class
  */
  std::uint32_t *ver;

public:
  SemVer();
  SemVer(const SemVer &o);
  SemVer(const std::string &ver, const std::uint8_t &fmt);
  SemVer(const std::string &ver, const std::uint8_t &fmt, const std::string &bld);
  ~SemVer();
  void *operator new(std::size_t size);
  void operator=(const SemVer &o);
  void operator=(SemVer *o);
  bool operator==(SemVer &o);
  bool operator!=(SemVer &o);
  bool operator<(SemVer &o);
  bool operator>(SemVer &o);
  bool operator<=(SemVer &o);
  bool operator>=(SemVer &o);
  int compare(SemVer &o);
  std::string Pretty();
  std::string Pretty(std::string fmt);
  std::uint32_t Major();
  std::uint32_t Minor();
  std::uint32_t Patch();
  std::uint32_t Build();
  std::uint32_t Revision();
};

int compare(SemVer &o, SemVer &c);

#endif // CGOGGLES_SEMVER_H_
