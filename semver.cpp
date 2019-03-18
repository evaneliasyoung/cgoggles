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
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
}

SemVer::SemVer(const SemVer &v)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  for (std::size_t i = 0; i < 5; ++i)
  {
    ver[i] = v.ver[i];
  }
}

SemVer::SemVer(const std::string &rawVer, const std::uint8_t &fmt)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  std::unique_ptr<std::vector<std::string>> spl = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::uint8_t> i = std::make_unique<std::uint8_t>(0xFF);
  splitStringVector(rawVer, ".", spl.get());

  if (fmt & 0b10000u)
  {
    ver[0] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b01000u)
  {
    ver[1] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00100u)
  {
    ver[2] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00010u)
  {
    ver[3] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b00001u)
  {
    ver[4] = std::stoi((*spl)[++(*i)]);
  }
}

SemVer::SemVer(const std::string &rawVer, const std::uint8_t &fmt, const std::string &bld)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  std::unique_ptr<std::vector<std::string>> spl = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::uint8_t> i = std::make_unique<std::uint8_t>(0xFF);
  splitStringVector(rawVer, ".", spl.get());

  if (fmt & 0b100u)
  {
    ver[0] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b010u)
  {
    ver[1] = std::stoi((*spl)[++(*i)]);
  }
  if (fmt & 0b001u)
  {
    ver[2] = std::stoi((*spl)[++(*i)]);
  }
  ver[3] = std::stoi(bld);
}

SemVer::~SemVer()
{
  delete ver;
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
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};

  v.ver[0] = ver[0];
  v.ver[1] = ver[1];
  v.ver[2] = ver[2];
  v.ver[3] = ver[3];
  v.ver[4] = ver[4];
  return *this;
}

bool SemVer::operator==(SemVer &v)
{
  return this->compare(v) == 0;
}

bool SemVer::operator!=(SemVer &v)
{
  return this->compare(v) != 0;
}

bool SemVer::operator<(SemVer &v)
{
  return this->compare(v) < 0;
}

bool SemVer::operator>(SemVer &v)
{
  return this->compare(v) > 0;
}

bool SemVer::operator<=(SemVer &v)
{
  return this->compare(v) <= 0;
}

bool SemVer::operator>=(SemVer &v)
{
  return this->compare(v) >= 0;
}
#pragma endregion "Operators"

#pragma region "Accessors"
std::uint32_t SemVer::Major()
{
  return ver[0];
}

std::uint32_t SemVer::Minor()
{
  return ver[1];
}

std::uint32_t SemVer::Patch()
{
  return ver[2];
}

std::uint32_t SemVer::Build()
{
  return ver[3];
}

std::uint32_t SemVer::Revision()
{
  return ver[4];
}
#pragma endregion "Accessors"

#pragma region "Methods"
int SemVer::compare(SemVer &v)
{
  for (std::size_t i = 0; i < 5; i++)
  {
    if (ver[i] == v.ver[i])
    {
      continue;
    }
    if (ver[i] > v.ver[i])
    {
      return 1;
    }
    if (ver[i] < v.ver[i])
    {
      return -1;
    }
  }

  return 0;
}

std::string SemVer::Pretty()
{
  return Pretty("$F");
}

std::string SemVer::Pretty(std::string fmt)
{
  fmt = std::regex_replace(fmt, std::regex(R"(\$F)"), "$M.$N.$P");
  fmt = std::regex_replace(fmt, std::regex(R"(\$M)"), std::to_string(ver[0]));
  fmt = std::regex_replace(fmt, std::regex(R"(\$N)"), std::to_string(ver[1]));
  fmt = std::regex_replace(fmt, std::regex(R"(\$P)"), std::to_string(ver[2]));
  fmt = std::regex_replace(fmt, std::regex(R"(\$B)"), std::to_string(ver[3]));
  fmt = std::regex_replace(fmt, std::regex(R"(\$R)"), std::to_string(ver[4]));
  return fmt;
}
#pragma endregion "Methods"

#pragma region "Static Methods"
int compare(SemVer &v, SemVer &c)
{
  return v.compare(c);
}
#pragma endregion "Static Methods"
