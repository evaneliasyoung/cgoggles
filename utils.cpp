/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-04-08
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "argh.h"
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

/**
* @brief Trims away the specified characters from the end of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
std::string rtrim(std::string s, const char *t)
{
  return s.erase(s.find_last_not_of(t) + 1);
}

/**
* @brief Trims away the specified characters from the beginning of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
std::string ltrim(std::string s, const char *t)
{
  return s.erase(0, s.find_first_not_of(t));
}

/**
* @brief Trims away the specified characters from both ends of a string
*
* @param s A pointer to the string to trim
* @param t A collection of chars to remove
*/
std::string trim(std::string s, const char *t)
{
  return ltrim(rtrim(s, t), t);
}

void outputVersion()
{
  std::cout << ((CGOGGLES_VERSION_ & 0xFF0000) >> (4 * 4)) << '.'
            << ((CGOGGLES_VERSION_ & 0x00FF00) >> (2 * 4)) << '.'
            << ((CGOGGLES_VERSION_ & 0x0000FF) >> (0 * 4)) << ' '
            << 'x' << CGOGGLES_ENVIRONMENT_ << std::endl;
}

void outputHelp()
{
  // NOTE: JSON output disabled until further notice
  // std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [-l|--list|-j|--json|-m|--minjson] -get=[<args>]" << std::endl;
  std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [-l|--list] <command> [<args>]" << std::endl
            << "  get   Makes a query to the computer's internals" << std::endl
            << "  list  List the values that you can query to CGoggles" << std::endl
            << std::endl
            << "example: cgoggles get cpu.Brand, cpu.Cores, os.Version" << std::endl;
}

void outputList(const std::string &cat)
{
  std::vector<std::string> osList = {
      "os", "os.All", "os.Platform",
      "os.Caption", "os.Serial", "os.Bit",
      "os.InstallTime", "os.BootTime", "os.CurTime",
      "os.Kernel", "os.Version"};
  std::vector<std::string> cpuList = {
      "cpu", "cpu.All", "cpu.Manufacturer",
      "cpu.Architecture", "cpu.SocketType", "cpu.Brand",
      "cpu.Family", "cpu.Model", "cpu.Stepping",
      "cpu.Cores", "cpu.Threads", "cpu.Speed",
      "cpu.MaxSpeed"};
  std::vector<std::string> gpuList = {
      "gpu", "gpu.All", "gpu.Vendor",
      "gpu.Model", "gpu.Bus", "gpu.VRAM",
      "gpu.Dynamic"};
  std::vector<std::string> ramList = {
      "ram", "ram.All", "ram.Size",
      "ram.Bank", "ram.Type", "ram.Speed",
      "ram.FormFactor", "ram.Manufacturer", "ram.Part",
      "ram.Serial", "ram.VoltageConfigured", "ram.VoltageMin",
      "ram.VoltageMax"};
  std::vector<std::string> storageList = {
      "storage", "storage.All", "storage.Name",
      "storage.Identifier", "storage.Type", "storage.FileSystem",
      "storage.Mount", "storage.Total", "storage.Physical",
      "storage.UUID", "storage.Label", "storage.Model",
      "storage.Serial", "storage.Removable", "storage.Protocol"};
  std::vector<std::string> fsList = {
      "fs", "fs.All", "fs.FS",
      "fs.Type", "fs.Size", "fs.Used",
      "fs.Mount"};
  std::vector<std::vector<std::string>> liList = {
      osList, cpuList, gpuList,
      ramList, storageList, fsList};

  if (cat == "" || cat == "all" || cat == "All")
  {
    std::cout << "All available queries for CGoggles." << '\n';
    for (std::size_t i = 0; i < liList.size(); ++i)
    {
      std::cout << liList[i][0] << std::endl;
      for (std::size_t j = 0; j < liList[i].size(); ++j)
      {
        std::cout << liList[i][j] << std::endl;
      }
    }
    return;
  }

  std::cout << "Available queries for the specified category." << '\n';
  if (cat == "os")
  {
    for (std::size_t i = 0; i < osList.size(); ++i)
    {
      std::cout << osList[i] << std::endl;
    }
  }
  if (cat == "cpu")
  {
    for (std::size_t i = 0; i < cpuList.size(); ++i)
    {
      std::cout << cpuList[i] << std::endl;
    }
  }
  if (cat == "gpu")
  {
    for (std::size_t i = 0; i < gpuList.size(); ++i)
    {
      std::cout << gpuList[i] << std::endl;
    }
  }
  if (cat == "ram")
  {
    for (std::size_t i = 0; i < ramList.size(); ++i)
    {
      std::cout << ramList[i] << std::endl;
    }
  }
  if (cat == "storage")
  {
    for (std::size_t i = 0; i < storageList.size(); ++i)
    {
      std::cout << storageList[i] << std::endl;
    }
  }
  if (cat == "fs")
  {
    for (std::size_t i = 0; i < fsList.size(); ++i)
    {
      std::cout << fsList[i] << std::endl;
    }
  }
}

int handleArgs(int argc, const char *argv[], std::string *request)
{
  argh::parser cmdl(argv);
  bool getArgs = false;

  if (cmdl[{"v", "ver", "version"}])
  {
    outputVersion();
    std::exit(EXIT_SUCCESS);
  }

  if (cmdl[{"h", "help"}])
  {
    outputHelp();
    std::exit(EXIT_SUCCESS);
  }

  // NOTE: JSON output disabled until further notice
  //       It's really quite a mess without a JSON library
  // if (cmdl[{"m", "minjson"}])
  // {
  //   if (cmdl[{"j", "json", "l", "list"}]) {
  //     outputHelp();
  //     return EXIT_FAILURE;
  //   }

  //   style = OutputStyle::MinJSON;
  // }

  // if (cmdl[{"j", "json"}])
  // {
  //   if (cmdl[{"m", "minjson", "l", "list"}]) {
  //     outputHelp();
  //     return EXIT_FAILURE;
  //   }

  //   style = OutputStyle::JSON;
  // }

  if (cmdl[{"l", "list"}])
  {
    style = OutputStyle::List;
  }

  for (std::size_t i = 0; i < argc; ++i)
  {
    if (!std::strcmp(argv[i], "list"))
    {
      outputList(i + 1 < argc ? argv[++i] : "");
      return EXIT_SUCCESS;
    }
    if (!getArgs || i == 0 || argv[i][0] == '-')
    {
      continue;
    }
  }

  for (std::size_t i = 0; i < argc; ++i)
  {
    if (!std::strcmp(argv[i], "get"))
    {
      getArgs = true;
      continue;
    }
    if (!getArgs || i == 0 || argv[i][0] == '-')
    {
      continue;
    }
    (*request) += argv[i];
  }

  return EXIT_SUCCESS;
}
