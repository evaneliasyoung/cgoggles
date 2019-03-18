/**
*  @file      semver.h
*  @brief     The interface for the SemVer class.
*
*  @author    Evan Elias Young
*  @date      2019-03-17
*  @date      2019-03-18
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  SemVer(const SemVer &v);
  SemVer(const std::string &ver, const std::uint8_t &fmt);
  SemVer(const std::string &ver, const std::uint8_t &fmt, const std::string &bld);
  ~SemVer();
  void *operator new(std::size_t size);
  SemVer operator=(const SemVer &v);
  bool operator==(SemVer &v);
  bool operator!=(SemVer &v);
  bool operator<(SemVer &v);
  bool operator>(SemVer &v);
  bool operator<=(SemVer &v);
  bool operator>=(SemVer &v);
  int compare(SemVer &v);
  std::string Pretty();
  std::string Pretty(std::string fmt);
  std::uint32_t Major();
  std::uint32_t Minor();
  std::uint32_t Patch();
  std::uint32_t Build();
  std::uint32_t Revision();
};

int compare(SemVer &v, SemVer &c);

#endif // CGOGGLES_SEMVER_H_
