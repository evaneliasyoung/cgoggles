/**
*  @file      processor.cpp
*  @brief     The implementation for the Processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "processor.h"
#include "temperature.h"
#include "os.h"
#include "utils.h"

#pragma region "Constructors"
/**
* @brief Construct a new Processor object
*/
Processor::Processor()
{
  manufacturer = "";
  architecture = "";
  socketType = "";
  brand = "";
  family = 0;
  model = 0;
  stepping = 0;
  cores = 0;
  threads = 0;
  speed = 0;
  maxSpeed = 0;
}

/**
* @brief Construct a new Processor object with help from the assistants
*
* @param plt The platform of the system
*/
Processor::Processor(std::uint8_t plt)
{
  switch (CGOGGLES_OS)
  {
  case OS_WIN:
    GetWin();
    break;
  case OS_MAC:
    GetMac();
    break;
  case OS_LUX:
    GetLux();
    break;
  }
}

/**
* @brief Construct a new Processor object from another Processor object
*
* @param o The Processor object to copy from
*/
Processor::Processor(const Processor &o)
{
  manufacturer = o.manufacturer;
  architecture = o.architecture;
  socketType = o.socketType;
  brand = o.brand;
  family = o.family;
  model = o.model;
  stepping = o.stepping;
  cores = o.cores;
  threads = o.threads;
  speed = o.speed;
  maxSpeed = o.maxSpeed;
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void Processor::GetMac()
{
  std::string temp;

  manufacturer = runCommand("sysctl -n machdep.cpu.vendor");
  trim(&manufacturer);
  cores = std::stoi(runCommand("sysctl -n hw.physicalcpu"));
  threads = std::stoi(runCommand("sysctl -n hw.logicalcpu"));

  temp = runCommand("uname -m");
  architecture = temp.find("64") == std::string::npos ? temp : "x64";
  socketType = "Soldered";

  brand = runCommand("sysctl -n machdep.cpu.brand_string");
  if (brand.find("@") != std::string::npos)
  {
    brand.erase(brand.find_first_of("@"));
  }
  trim(&brand);

  family = std::stoi(runCommand("sysctl -n machdep.cpu.family"));
  model = std::stoi(runCommand("sysctl -n machdep.cpu.model"));
  stepping = std::stoi(runCommand("sysctl -n machdep.cpu.stepping"));

  maxSpeed = std::round(std::stof(runCommand("sysctl -n hw.cpufrequency_max").substr(0, 4)) / 10) * pow(10, 7);
  speed = std::round(std::stof(runCommand("sysctl -n hw.cpufrequency_max").substr(0, 4)) / 10) * pow(10, 7);
}

/**
* @brief Fills in the processor information for Windows systems
*/
void Processor::GetWin()
{
  std::string wmic = getWmicPath();
  std::map<std::string, std::string> dataMap = runMultiWmic("cpu get Manufacturer,NumberOfCores,NumberOfLogicalProcessors,Architecture,UpgradeMethod,Name,Description,MaxClockSpeed,MaxClockSpeed", &wmic);
  std::string temp;
  std::smatch mt;
  std::string *architectureMap = new std::string[10]{"x86", "MIPS", "Alpha", "PowerPC", "Unknown", "ARM", "ia64", "Unknown", "Unknown", "x64"};
  std::string *socketTypeMap = new std::string[61]{
      "Unknown",
      "Other",
      "Unknown",
      "Daughter Board",
      "ZIF Socket",
      "Replacement/Piggy Back",
      "None",
      "LIF Socket",
      "Slot 1",
      "Slot 2",
      "370 Pin Socket",
      "Slot A",
      "Slot M",
      "423",
      "A (Socket 462)",
      "478",
      "754",
      "940",
      "939",
      "mPGA604",
      "LGA771",
      "LGA775",
      "S1",
      "AM2",
      "F (1207)",
      "LGA1366",
      "G34",
      "AM3",
      "C32",
      "LGA1156",
      "LGA1567",
      "PGA988A",
      "BGA1288",
      "rPGA988B",
      "BGA1023",
      "BGA1224",
      "LGA1155",
      "LGA1356",
      "LGA2011",
      "FS1",
      "FS2",
      "FM1",
      "FM2",
      "LGA2011-3",
      "LGA1356-3",
      "LGA1150",
      "BGA1168",
      "BGA1234",
      "BGA1364",
      "AM4",
      "LGA1151",
      "BGA1356",
      "BGA1440",
      "BGA1515",
      "LGA3647-1",
      "SP3",
      "SP3r2",
      "LGA2066",
      "BGA1392",
      "BGA1510",
      "BGA1528"};

  manufacturer = dataMap["Manufacturer"];
  cores = std::stoi(dataMap["NumberOfCores"]);
  threads = std::stoi(dataMap["NumberOfLogicalProcessors"]);

  architecture = architectureMap[std::stoi(dataMap["Architecture"])];
  socketType = socketTypeMap[std::stoi(dataMap["UpgradeMethod"])];

  brand = dataMap["Name"];
  if (brand.find("@") != std::string::npos)
  {
    brand.erase(brand.find_first_of("@"));
  }
  trim(&brand);

  temp = dataMap["Description"];
  if (std::regex_search(temp, mt, std::regex(R"(.*Family (\d+) Model (\d+) Stepping (\d+))", std::regex_constants::ECMAScript | std::regex_constants::icase)))
  {
    family = std::stoi(mt[1]);
    model = std::stoi(mt[2]);
    stepping = std::stoi(mt[3]);
  }

  maxSpeed = std::round(std::stof(dataMap["MaxClockSpeed"]) / 10) * pow(10, 7);
  speed = std::round(std::stof(dataMap["MaxClockSpeed"]) / 10) * pow(10, 7);

  delete[] architectureMap;
  delete[] socketTypeMap;
}

/**
* @brief Fills in the processor information for Linux systems
*/
void Processor::GetLux()
{
  std::string temp;
  std::vector<std::string> tempLines;
  std::map<std::string, std::string> dataMap;
  std::string key;
  std::string val;
  std::string line;
  std::string mapTry;
  std::string mapTry2;

  temp = runCommand("export LC_ALL=C; lscpu; unset LC_ALL");
  splitStringVector(temp, "\n", &tempLines);
  for (std::size_t i = 0; i < tempLines.size(); ++i)
  {
    line = trim(tempLines[i]);
    splitKeyValuePair(line, &key, &val);
    dataMap[key] = val;
  }

  manufacturer = tryGetValue<std::string, std::string>(dataMap, "Vendor ID", &mapTry) ? mapTry : "";
  cores = tryGetValue<std::string, std::string>(dataMap, "Core(s) per socket", &mapTry) && tryGetValue<std::string, std::string>(dataMap, "Socket(s)", &mapTry2) ? std::stoi(mapTry) * std::stoi(mapTry2) : 0;
  threads = tryGetValue<std::string, std::string>(dataMap, "Thread(s) per core", &mapTry) ? std::stoi(mapTry) * cores : 0;

  architecture = tryGetValue<std::string, std::string>(dataMap, "Architecture", &mapTry) ? mapTry : "";
  architecture = endswith(architecture, "64")
                     ? "x64"
                     : endswith(architecture, "86")
                           ? "x86"
                           : startswith(architecture, "arm")
                                 ? "ARM"
                                 : "Unknown";
  socketType = "Unknown";

  brand = tryGetValue<std::string, std::string>(dataMap, "Model name", &mapTry) ? mapTry : "";
  if (brand.find("@") != std::string::npos)
  {
    brand.erase(brand.find_first_of("@"));
  }
  trim(&brand);

  family = std::stoi(tryGetValue<std::string, std::string>(dataMap, "CPU family", &mapTry) ? mapTry : 0);
  model = std::stoi(tryGetValue<std::string, std::string>(dataMap, "Model", &mapTry) ? mapTry : 0);
  stepping = std::stoi(tryGetValue<std::string, std::string>(dataMap, "Stepping", &mapTry) ? mapTry : 0);

  if (tryGetValue<std::string, std::string>(dataMap, "CPU MHz", &mapTry))
  {
    maxSpeed = std::round(std::stof(mapTry)) * 1000000;
    speed = std::round(std::stof(mapTry)) * 1000000;
  }
  if (tryGetValue<std::string, std::string>(dataMap, "CPU max MHz", &mapTry))
  {
    maxSpeed = std::round(std::stof(mapTry)) * 1000000;
    speed = std::round(std::stof(mapTry)) * 1000000;
  }
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Reserves memory for a new Processor object
*
* @param  size  The amount of memory to allocate
* @return void* A pointer to the allocated memory
*/
void *Processor::operator new(std::size_t size)
{
  void *o = ::new (Processor);
  return o;
}

/**
* @brief Sets equal two Processor objects
*
* @param o The Processor object to copy from
*/
void Processor::operator=(const Processor &o)
{
  if (&o == this)
  {
    return;
  }
  manufacturer = o.manufacturer;
  architecture = o.architecture;
  socketType = o.socketType;
  brand = o.brand;
  family = o.family;
  model = o.model;
  stepping = o.stepping;
  cores = o.cores;
  threads = o.threads;
  speed = o.speed;
  maxSpeed = o.maxSpeed;
}

/**
* @brief Sets one Processor equal to another
*
* @param o The Processor to copy from
*/
void Processor::operator=(Processor *o)
{
  manufacturer = o->manufacturer;
  architecture = o->architecture;
  socketType = o->socketType;
  brand = o->brand;
  family = o->family;
  model = o->model;
  stepping = o->stepping;
  cores = o->cores;
  threads = o->threads;
  speed = o->speed;
  maxSpeed = o->maxSpeed;
}
#pragma endregion "Operators"
