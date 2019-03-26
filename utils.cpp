/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "utils.h"

/**
* @brief Splits a string into a vector of its parts
*
* @param s The string to slit
* @param d The delimiter to split upon
* @param v The vector to add to
*/
void splitStringVector(const std::string &s, const std::string &d, std::vector<std::string> *v)
{
  std::string::size_type beg = std::string::size_type(0);
  std::string::size_type end = std::string::size_type(s.find(d, 1));

  if (s.find_last_of(d) != std::string::npos)
  {
    while (beg < s.size() && end <= s.size())
    {
      (*v).push_back(s.substr(beg, end - beg));
      beg = s.find(d, end) + d.length();
      end = s.find(d, beg);
    }
  }
  (*v).push_back(s.substr(beg, s.length() - beg));
}

/**
* @brief Removes any duplicates from the specified vector
*
* @param v The vector to make unique
*/
void removeDuplicates(std::vector<std::string> *v)
{
  if ((*v).size() <= 1)
  {
    return;
  }

  for (int i = (*v).size() - 1; i >= 0; i--)
  {
    if (i != std::distance((*v).begin(), std::find((*v).begin(), (*v).end(), (*v)[i])))
    {
      (*v).erase((*v).begin() + i);
    }
  }
}

/**
* @brief Determines whether or not a vector contains the specified element
*
* @param  v The vector to search
* @param  s The string to stearch for
* @return   true  The vector contains the string
* @return   false The vector does NOT contain the string
*/
bool contains(std::vector<std::string> *v, const std::string &s)
{
  return std::find(v->begin(), v->end(), s) != v->end();
}

/**
* @brief Trims away the specified characters from the end of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
void rtrim(std::string *s, const char *t)
{
  s->erase(s->find_last_not_of(t) + 1);
}

/**
* @brief Trims away the specified characters from the beginning of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
void ltrim(std::string *s, const char *t)
{
  s->erase(0, s->find_first_not_of(t));
}

/**
* @brief Trims away the specified characters from both ends of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
void trim(std::string *s, const char *t)
{
  rtrim(s, t);
  ltrim(s, t);
}
