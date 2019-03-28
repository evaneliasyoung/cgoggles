/**
*  @file      processor.cpp
*  @brief     The implementation for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-25
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
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
  manufacturer = std::make_unique<std::string>();
  architecture = std::make_unique<std::string>();
  socketType = std::make_unique<std::string>();
  brand = std::make_unique<std::string>();
  family = std::make_unique<std::uint8_t>();
  model = std::make_unique<std::uint8_t>();
  stepping = std::make_unique<std::uint8_t>();
  cores = std::make_unique<std::uint8_t>();
  threads = std::make_unique<std::uint8_t>();
  speed = std::make_unique<float>();
  maxSpeed = std::make_unique<float>();
}

/**
* @brief Construct a new Processor object with help from the assistants
*
* @param plt The platform of the system
*/
Processor::Processor(std::uint8_t plt)
{
  manufacturer = std::make_unique<std::string>();
  architecture = std::make_unique<std::string>();
  socketType = std::make_unique<std::string>();
  brand = std::make_unique<std::string>();
  family = std::make_unique<std::uint8_t>();
  model = std::make_unique<std::uint8_t>();
  stepping = std::make_unique<std::uint8_t>();
  cores = std::make_unique<std::uint8_t>();
  threads = std::make_unique<std::uint8_t>();
  speed = std::make_unique<float>();
  maxSpeed = std::make_unique<float>();

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
* @brief Destroy the Processor object
*/
Processor::~Processor()
{
  manufacturer.reset();
  architecture.reset();
  socketType.reset();
  brand.reset();
  family.reset();
  model.reset();
  stepping.reset();
  cores.reset();
  threads.reset();
  speed.reset();
  maxSpeed.reset();
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void Processor::GetMac()
{
  std::string temp;

  (*manufacturer) = runCommand("sysctl -n machdep.cpu.vendor");
  trim(manufacturer.get());
  (*cores) = std::stoi(runCommand("sysctl -n hw.physicalcpu"));
  (*threads) = std::stoi(runCommand("sysctl -n hw.logicalcpu"));

  temp = runCommand("uname -m");
  (*architecture) = temp.find("64") == std::string::npos ? temp : "x64";
  (*socketType) = "Soldered";

  (*brand) = runCommand("sysctl -n machdep.cpu.brand_string");
  if (brand->find("@") != std::string::npos)
  {
    brand->erase(brand->find_first_of("@"));
  }
  trim(brand.get());

  (*family) = std::stoi(runCommand("sysctl -n machdep.cpu.family"));
  (*model) = std::stoi(runCommand("sysctl -n machdep.cpu.model"));
  (*stepping) = std::stoi(runCommand("sysctl -n machdep.cpu.stepping"));

  (*maxSpeed) = std::round(std::stof(runCommand("sysctl -n hw.cpufrequency_max").substr(0, 4)) / 10) / 100;
  (*speed) = std::round(std::stof(runCommand("sysctl -n hw.cpufrequency_max").substr(0, 4)) / 10) / 100;
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

  (*manufacturer) = dataMap["Manufacturer"];
  (*cores) = std::stoi(dataMap["NumberOfCores"]);
  (*threads) = std::stoi(dataMap["NumberOfLogicalProcessors"]);

  (*architecture) = architectureMap[std::stoi(dataMap["Architecture"])];
  (*socketType) = socketTypeMap[std::stoi(dataMap["UpgradeMethod"])];

  (*brand) = dataMap["Name"];
  if (brand->find("@") != std::string::npos)
  {
    brand->erase(brand->find_first_of("@"));
  }
  trim(brand.get());

  temp = dataMap["Description"];
  if (std::regex_search(temp, mt, std::regex(R"(.*Family (\d+) Model (\d+) Stepping (\d+))", std::regex_constants::ECMAScript | std::regex_constants::icase)))
  {
    (*family) = std::stoi(mt[1]);
    (*model) = std::stoi(mt[2]);
    (*stepping) = std::stoi(mt[3]);
  }

  (*maxSpeed) = std::round(std::stof(dataMap["MaxClockSpeed"]) / 10) / 100;
  (*speed) = std::round(std::stof(dataMap["MaxClockSpeed"]) / 10) / 100;

  delete architectureMap;
  delete socketTypeMap;
}

/**
* @brief Fills in the processor information for Linux systems
*/
void Processor::GetLux()
{
}
#pragma endregion

#pragma region "Operators"
/**
* @brief Sets one Processor equal to another
*
* @param o The Processor to copy from
*/
void Processor::operator=(Processor *p)
{
  (*manufacturer) = (*p->manufacturer);
  (*architecture) = (*p->architecture);
  (*socketType) = (*p->socketType);
  (*brand) = (*p->brand);
  (*family) = (*p->family);
  (*model) = (*p->model);
  (*stepping) = (*p->stepping);
  (*cores) = (*p->cores);
  (*threads) = (*p->threads);
  (*speed) = (*p->speed);
  (*maxSpeed) = (*p->maxSpeed);
}
#pragma endregion "Operators"

#pragma region "Accessors"
/**
* @brief Returns a copy of the manufacturer
*
* @return std::string The manufacturer
*/
std::string Processor::Manufacturer()
{
  return (*manufacturer);
}

/**
* @brief Returns a copy of the architecture
*
* @return std::string The architecture
*/
std::string Processor::Architecture()
{
  return (*architecture);
}

/**
* @brief Returns a copy of the internal socket type
*
* @return std::string The internal socket type
*/
std::string Processor::SocketType()
{
  return (*socketType);
}

/**
* @brief Returns the a copy of the make/model
*
* @return std::string The make/model
*/
std::string Processor::Brand()
{
  return (*brand);
}

/**
* @brief Returns a copy of the family
*
* @return std::uint8_t The family number
*/
std::uint8_t Processor::Family()
{
  return (*family);
}

/**
* @brief Returns a copy of the model
*
* @return std::uint8_t The model number
*/
std::uint8_t Processor::Model()
{
  return (*model);
}

/**
* @brief Returns a copy of the step
*
* @return std::uint8_t The stepping number
*/
std::uint8_t Processor::Stepping()
{
  return (*stepping);
}

/**
* @brief Returns a copy of the physical core count
*
* @return std::uint8_t The number of physical cores
*/
std::uint8_t Processor::Cores()
{
  return (*cores);
}

/**
* @brief Returns a copy of the logical core count
*
* @return std::uint8_t The number of logical cores
*/
std::uint8_t Processor::Threads()
{
  return (*threads);
}

/**
* @brief Returns a copy of the current clock speed
*
* @return float The current clock speed
*/
float Processor::Speed()
{
  return (*speed);
}

/**
* @brief Returns a human-readable copy of the current clock speed
*
* @return std::string The human-readable current clock speed
*/
std::string Processor::PrettySpeed()
{
  std::stringstream buffer;
  buffer << std::fixed << std::setprecision(2) << (*speed) << " GHz";
  return buffer.str();
}

/**
* @brief Returns a copy of the maximum clock speed
*
* @return float The maximum clock speed
*/
float Processor::MaxSpeed()
{
  return (*maxSpeed);
}

/**
* @brief Returns a human-readable copy of the maximum clock speed
*
* @return std::string The human-readable maximum clock speed
*/
std::string Processor::PrettyMaxSpeed()
{
  std::stringstream buffer;
  buffer << std::fixed << std::setprecision(2) << (*maxSpeed) << " GHz";
  return buffer.str();
}
#pragma endregion "Accessors"
