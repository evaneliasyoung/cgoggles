/**
*  @file      semver.cpp
*  @brief     The implementation for the SemVer class.
*
*  @author    Evan Elias Young
*  @date      2019-03-17
*  @date      2019-03-17
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "semver.h"
#include "utils.h"

#pragma region "Contructors"
SemVer::SemVer()
{
  major = std::make_unique<std::uint32_t>(0);
  minor = std::make_unique<std::uint32_t>(0);
  patch = std::make_unique<std::uint32_t>(0);
  build = std::make_unique<std::uint32_t>(0);
  revision = std::make_unique<std::uint32_t>(0);
}

SemVer::SemVer(const SemVer &v)
{
  major = std::make_unique<std::uint32_t>(0);
  minor = std::make_unique<std::uint32_t>(0);
  patch = std::make_unique<std::uint32_t>(0);
  build = std::make_unique<std::uint32_t>(0);
  revision = std::make_unique<std::uint32_t>(0);

  (*major) = (*v.major);
  (*minor) = (*v.minor);
  (*patch) = (*v.patch);
  (*build) = (*v.build);
  (*revision) = (*v.revision);
}

SemVer::SemVer(const std::string &ver, const std::uint8_t &fmt)
{
  std::unique_ptr<std::vector<std::string>> spl = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::uint8_t> i = std::make_unique<std::uint8_t>(0xFF);
  splitStringVector(ver, ".", spl.get());

  major = std::make_unique<std::uint32_t>(0);
  minor = std::make_unique<std::uint32_t>(0);
  patch = std::make_unique<std::uint32_t>(0);
  build = std::make_unique<std::uint32_t>(0);
  revision = std::make_unique<std::uint32_t>(0);

  if (fmt & 0b10000u)
  {
    (*major) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b01000u)
  {
    (*minor) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00100u)
  {
    (*patch) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00010u)
  {
    (*build) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00001u)
  {
    (*revision) = std::stoi((*spl)[++(*i)]);
  }
}

SemVer::SemVer(const std::string &ver, const std::uint8_t &fmt, const std::string &bld)
{
  std::unique_ptr<std::vector<std::string>> spl = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::uint8_t> i = std::make_unique<std::uint8_t>(0xFF);
  splitStringVector(ver, ".", spl.get());

  major = std::make_unique<std::uint32_t>(0);
  minor = std::make_unique<std::uint32_t>(0);
  patch = std::make_unique<std::uint32_t>(0);
  build = std::make_unique<std::uint32_t>(0);
  revision = std::make_unique<std::uint32_t>(0);

  if (fmt & 0b100u)
  {
    (*major) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b010u)
  {
    (*minor) = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b001u)
  {
    (*patch) = std::stoi((*spl)[++(*i)]);
  }
  (*build) = std::stoi(bld);
}

SemVer::~SemVer()
{
  major.reset();
  minor.reset();
  patch.reset();
  build.reset();
  revision.reset();
}
#pragma endregion "Contructors"

#pragma region "Operators"
void *SemVer::operator new(std::size_t size)
{
  void *o = ::new (SemVer);
  return o;
}

SemVer SemVer::operator=(const SemVer &v)
{
  if (&v == this)
  {
    return *this;
  }
  major = std::make_unique<std::uint32_t>(0);
  minor = std::make_unique<std::uint32_t>(0);
  patch = std::make_unique<std::uint32_t>(0);
  build = std::make_unique<std::uint32_t>(0);
  revision = std::make_unique<std::uint32_t>(0);

  (*v.major) = (*major);
  (*v.minor) = (*minor);
  (*v.patch) = (*patch);
  (*v.build) = (*build);
  (*v.revision) = (*revision);
  return *this;
}
#pragma endregion "Operators"

#pragma region "Methods"
std::string SemVer::Pretty()
{
  return Pretty("$F");
}

std::string SemVer::Pretty(std::string fmt)
{
  fmt = std::regex_replace(fmt, std::regex(R"(\$F)"), "$M.$N.$P");
  fmt = std::regex_replace(fmt, std::regex(R"(\$M)"), std::to_string((*major)));
  fmt = std::regex_replace(fmt, std::regex(R"(\$N)"), std::to_string((*minor)));
  fmt = std::regex_replace(fmt, std::regex(R"(\$P)"), std::to_string((*patch)));
  fmt = std::regex_replace(fmt, std::regex(R"(\$B)"), std::to_string((*build)));
  fmt = std::regex_replace(fmt, std::regex(R"(\$R)"), std::to_string((*revision)));
  return fmt;
}
#pragma endregion "Methods"

#pragma region "Accessors"
std::uint32_t SemVer::Major()
{
  return (*major);
}

std::uint32_t SemVer::Minor()
{
  return (*minor);
}

std::uint32_t SemVer::Patch()
{
  return (*patch);
}

std::uint32_t SemVer::Build()
{
  return (*build);
}

std::uint32_t SemVer::Revision()
{
  return (*revision);
}
#pragma endregion "Accessors"
