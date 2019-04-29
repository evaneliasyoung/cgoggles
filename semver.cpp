/**
*  @file      semver.cpp
*  @brief     The implementation for the SemVer class.
*
*  @author    Evan Elias Young
*  @date      2019-03-17
*  @date      2019-04-29
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "semver.h"
#include "utils.h"

#pragma region "Contructors"
/**
* @brief Construct a new SemVer object as release 0.0.0 build 0 revision 0
*/
SemVer::SemVer()
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
}

/**
* @brief Construct a new SemVer object from another SemVer object
*
* @param o The SemVer object to copy
*/
SemVer::SemVer(const SemVer &o)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  for (std::size_t i = 0; i < 5; ++i)
  {
    ver[i] = o.ver[i];
  }
}

/**
* @brief Construct a new SemVer object from the raw string and it's format code
*
* @param rawVer The raw string to interpolate
* @param fmt    The number included in the rawVer string
*/
SemVer::SemVer(const std::string &rawVer, const std::uint8_t &fmt)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  std::vector<std::string> spl;
  std::uint8_t i = 0xFF;
  splitStringVector(rawVer, ".", &spl);

  if (fmt & 0b10000u)
  {
    ver[0] = std::stoi(spl[++i]);
  }
  if (fmt & 0b01000u)
  {
    ver[1] = std::stoi(spl[++i]);
  }
  if (fmt & 0b00100u)
  {
    ver[2] = std::stoi(spl[++i]);
  }
  if (fmt & 0b00010u)
  {
    ver[3] = std::stoi(spl[++i]);
  }
  if (fmt & 0b00001u)
  {
    ver[4] = std::stoi(spl[++i]);
  }
}

/**
* @brief Construct a new SemVer object from the raw string and it's format code and the build number
*
* @param rawVer The raw string to interpolate
* @param fmt    The number included in the rawVer string
* @param bld    The build number
*/
SemVer::SemVer(const std::string &rawVer, const std::uint8_t &fmt, const std::string &bld)
{
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};
  std::vector<std::string> spl;
  std::uint8_t i = 0xFF;
  splitStringVector(rawVer, ".", &spl);

  if (fmt & 0b100u)
  {
    ver[0] = std::stoi(spl[++i]);
  }
  if (fmt & 0b010u)
  {
    ver[1] = std::stoi(spl[++i]);
  }
  if (fmt & 0b001u)
  {
    ver[2] = std::stoi(spl[++i]);
  }
  ver[3] = std::stoi(bld);
}

/**
* @brief Destroy the SemVer object
*
*/
SemVer::~SemVer()
{
  delete ver;
}
#pragma endregion "Contructors"

#pragma region "Operators"
/**
* @brief Reserves memory for a new SemVer object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *SemVer::operator new(std::size_t size)
{
  void *o = ::new (SemVer);
  return o;
}

/**
* @brief Sets equal two SemVer objects
*
* @param o The SemVer object to copy from
*/
void SemVer::operator=(const SemVer &o)
{
  if (&o == this)
  {
    return;
  }
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};

  ver[0] = o.ver[0];
  ver[1] = o.ver[1];
  ver[2] = o.ver[2];
  ver[3] = o.ver[3];
  ver[4] = o.ver[4];
}

/**
* @brief Sets equal two SemVer objects
*
* @param o The SemVer object to copy from
*/
void SemVer::operator=(SemVer *o)
{
  if ((*o) == (*this))
  {
    return;
  }
  ver = new std::uint32_t[5]{0, 0, 0, 0, 0};

  ver[0] = o->ver[0];
  ver[1] = o->ver[1];
  ver[2] = o->ver[2];
  ver[3] = o->ver[3];
  ver[4] = o->ver[4];
}

/**
* @brief Compares the equality two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The two SemVer objects are equal
* @return false The two SemVer objects are NOT equal
*/
bool SemVer::operator==(SemVer &o)
{
  return this->compare(o) == 0;
}

/**
* @brief Compares the inequality two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The two SemVer objects are NOT equal
* @return false The two SemVer objects are equal
*/
bool SemVer::operator!=(SemVer &o)
{
  return this->compare(o) != 0;
}

/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The primary SemVer object is less than t
* @return false The primary SemVer object is NOT less than t
*/
bool SemVer::operator<(SemVer &o)
{
  return this->compare(o) < 0;
}

/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The primary SemVer object is greater than t
* @return false The primary SemVer object is NOT greater than t
*/
bool SemVer::operator>(SemVer &o)
{
  return this->compare(o) > 0;
}

/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The primary SemVer object is less than or equal to t
* @return false The primary SemVer object is NOT less than or equal to t
*/
bool SemVer::operator<=(SemVer &o)
{
  return this->compare(o) <= 0;
}

/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return true  The primary SemVer object is greater than or equal to t
* @return false The primary SemVer object is NOT greater than or equal to t
*/
bool SemVer::operator>=(SemVer &o)
{
  return this->compare(o) >= 0;
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns the a copy of the major version number
*
* @return std::uint32_t The major version number
*/
std::uint32_t SemVer::Major()
{
  return ver[0];
}

/**
* @brief Returns the a copy of the minor version number
*
* @return std::uint32_t The minor version number
*/
std::uint32_t SemVer::Minor()
{
  return ver[1];
}

/**
* @brief Returns the a copy of the patch number
*
* @return std::uint32_t The patch number
*/
std::uint32_t SemVer::Patch()
{
  return ver[2];
}

/**
* @brief Returns the a copy of the build number
*
* @return std::uint32_t The build number
*/
std::uint32_t SemVer::Build()
{
  return ver[3];
}

/**
* @brief Returns the a copy of the revision number
*
* @return std::uint32_t The revision number
*/
std::uint32_t SemVer::Revision()
{
  return ver[4];
}
#pragma endregion "Accessors"

#pragma region "Methods"
/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The SemVer object to compare against
* @return -1    The primary SemVer object is less than v
* @return 0     The primary SemVer object is equal to v
* @return 1     The primary SemVer object is greater than v
*/
int SemVer::compare(SemVer &o)
{
  for (std::size_t i = 0; i < 5; i++)
  {
    if (ver[i] == o.ver[i])
    {
      continue;
    }
    return ver[i] > o.ver[i] ? 1 : -1;
  }

  return 0;
}

/**
* @brief Pretty prints the full version number Major.Minor.Patch
*
* @return std::string The version number 1.2.3
*/
std::string SemVer::Pretty()
{
  return Pretty("$F");
}

/**
* @brief Pretty prints the version based on the specified format
*
* @param fmt The format to conform to $M.$N.$P-$B.$R = 10.14.2-12387.367
* @return std::string the version number in the specified format
*/
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
/**
* @brief Compares the value of two SemVer objects
*
* @param  o     The primary SemVer object to compare against
* @param  c     The SemVer object to compare against
* @return -1    The SemVer object v is less than c
* @return 0     The SemVer object v is equal to c
* @return 1     The SemVer object v is greater than c
*/
int compare(SemVer &o, SemVer &c)
{
  return o.compare(c);
}
#pragma endregion "Static Methods"
