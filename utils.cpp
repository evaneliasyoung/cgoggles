/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-03-15
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "utils.h"

void splitStringVector(const std::string &s, const std::string &d, std::vector<std::string> *v)
{
  std::unique_ptr<std::string::size_type> beg(new std::string::size_type(0));
  std::unique_ptr<std::string::size_type> end(new std::string::size_type(s.find(d, (*beg) + 1)));

  if (s.find_last_of(d) != std::string::npos)
  {
    while ((*beg) < s.size() && (*end) <= s.size())
    {
      (*v).push_back(s.substr((*beg), (*end) - (*beg)));
      (*beg) = s.find(d, (*end)) + d.length();
      (*end) = s.find(d, (*beg));
    }
  }
  (*v).push_back(s.substr((*beg), s.length() - (*beg)));
}

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
