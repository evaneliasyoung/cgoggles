/**
*  @file      utils.cpp
*  @brief     The implementation for the utilities.
*
*  @author    Evan Elias Young
*  @date      2019-03-12
*  @date      2019-04-22
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

/**
* @brief Determines whether or not a string s starts with string r
*
* @param s      The string to analyze
* @param r      The string to search for
* @return true  The string starts with the other string
* @return false The string does NOT start with the other string
*/
bool startswith(const std::string &s, const std::string &r)
{
  if (r.size() > s.size())
  {
    return false;
  }

  if (s.substr(0, r.size()) == r)
  {
    return true;
  }

  return false;
}

/**
* @brief Determines whether or not a string s ends with string r
*
* @param s      The string to analyze
* @param r      The string to search for
* @return true  The string ends with the other string
* @return false The string does NOT end with the other string
*/
bool endswith(const std::string &s, const std::string &r)
{
  if (r.size() > s.size())
  {
    return false;
  }

  if (s.substr(s.size() - r.size()) == r)
  {
    return true;
  }

  return false;
}

/**
* @brief Splits a key/value pair base on a delimiter
*
* @param base   The base string to derive the key and value from
* @param k      The key
* @param v      The value
* @param doTrim Whether or not to trim the output
* @param spl    The character to split upon
* @return true  The split was successful
* @return false The split was NOT successful
*/
bool splitKeyValuePair(const std::string &base, std::string *k, std::string *v, const bool &doTrim, const char &spl)
{
  if (base.find_first_of(spl) == std::string::npos)
  {
    return false;
  }

  (*k) = base.substr(0, base.find_first_of(spl));
  (*v) = base.substr(base.find_first_of(spl) + 1);

  if (doTrim)
  {
    trim(k);
    trim(v);
  }

  return true;
}

/**
* @brief Attempts to read a file and get its contents
*
* @param p      The path to the file to read
* @param o      The output of the file, if read
* @return true  The file was read successfully
* @return false The file was NOT read successfully
*/
bool readFile(const std::string &p, std::string *o)
{
  std::ifstream t(p);
  std::stringstream buffer;

  if (!t.good())
  {
    return false;
  }

  try
  {
    buffer << t.rdbuf();
    (*o) = buffer.str();
  }
  catch (...)
  {
    return false;
  }

  return true;
}

std::string siUnits(const std::uint64_t &num, const std::uint8_t &plc, const std::string &suff)
{
  std::stringstream ss;
  char suf[9] = {'\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};

  for (std::size_t i = 5; i > 0; --i)
  {
    if (num >= pow(1024, i))
    {
      ss << std::fixed << std::setprecision(plc) << num / pow(1024, i) << ' ' << suf[i] << suff;
      return ss.str();
    }
  }
}

std::string siUnits(const std::uint32_t &num, const std::uint8_t &plc, const std::string &suff)
{
  std::stringstream ss;
  char suf[9] = {'\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};

  for (std::size_t i = 5; i > 0; --i)
  {
    if (num >= pow(1024, i))
    {
      ss << std::fixed << std::setprecision(plc) << num / pow(1024, i) << ' ' << suf[i] << suff;
      return ss.str();
    }
  }
}

std::string siUnits(const float &num, const std::uint8_t &plc, const std::string &suff)
{
  std::stringstream ss;
  char suf[9] = {'\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y'};

  for (std::size_t i = 5; i > 0; --i)
  {
    if (num >= pow(1024, i))
    {
      ss << std::fixed << std::setprecision(plc) << num / pow(1024, i) << ' ' << suf[i] << suff;
      return ss.str();
    }
  }
}

std::string prettyOutputStorage(const std::uint64_t &num, const std::uint8_t &plc)
{
  return siUnits(num, plc, "B");
}

std::string prettyOutputStorage(const std::uint32_t &num, const std::uint8_t &plc)
{
  return siUnits(num, plc, "B");
}

std::string prettyOutputStorage(const float &num, const std::uint8_t &plc)
{
  return siUnits(num, plc, "B");
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
  std::cout << "usage: cgoggles [-v|--ver|--version] [-h|--help] [-l|--list] [-r|--raw] <command> [<args>]" << std::endl
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
  std::vector<std::string> sysList = {
      "sys",
      "sys.All"
      "sys.Manufacturer",
      "sys.Model",
      "sys.Version",
      "sys.Serial",
      "sys.UUID"};
  std::vector<std::string>
      cpuList = {"cpu", "cpu.All", "cpu.Manufacturer", "cpu.Architecture", "cpu.SocketType", "cpu.Brand", "cpu.Family", "cpu.Model", "cpu.Stepping", "cpu.Cores", "cpu.Threads", "cpu.Speed", "cpu.MaxSpeed"};
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
      osList, sysList, cpuList, gpuList,
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

  if (cmdl[{"r", "raw"}])
  {
    pretty = false;
  }

  for (int i = 0; i < argc; ++i)
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

  for (int i = 0; i < argc; ++i)
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
  std::transform(request->begin(), request->end(), request->begin(), ::toupper);

  return EXIT_SUCCESS;
}
