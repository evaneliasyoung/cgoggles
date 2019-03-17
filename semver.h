/**
*  @file      semver.h
*  @brief     The interface for the SemVer class.
*
*  @author    Evan Elias Young
*  @date      2019-03-17
*  @date      2019-03-17
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_SEMVER_H_
#define CGOGGLES_SEMVER_H_

#include "pch.h"

class SemVer
{
private:
  std::unique_ptr<std::uint32_t> major;
  std::unique_ptr<std::uint32_t> minor;
  std::unique_ptr<std::uint32_t> patch;
  std::unique_ptr<std::uint32_t> build;
  std::unique_ptr<std::uint32_t> revision;

public:
  SemVer();
  SemVer(const SemVer &v);
  SemVer(const std::string &ver, const std::uint8_t &fmt);
  SemVer(const std::string &ver, const std::uint8_t &fmt, const std::string &bld);
  ~SemVer();
  void *operator new(std::size_t size);
  SemVer operator=(const SemVer &v);
  std::string Pretty();
  std::string Pretty(std::string fmt);
  std::uint32_t Major();
  std::uint32_t Minor();
  std::uint32_t Patch();
  std::uint32_t Build();
  std::uint32_t Revision();
};

#endif // CGOGGLES_SEMVER_H_
