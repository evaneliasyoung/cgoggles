/**
*  @file      processor.cpp
*  @brief     The implementation for the processor class.
*
*  @author    Evan Elias Young
*  @date      2019-03-16
*  @date      2019-03-22
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
  default:
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
}
#pragma endregion "Constructors"

#pragma region "Constructors' Assistants"
/**
* @brief Fills in the processor information for Darwin systems
*/
void Processor::GetMac()
{
}

/**
* @brief Fills in the processor information for Windows systems
*/
void Processor::GetWin()
{
  std::unique_ptr<std::string> wmicPath = std::make_unique<std::string>(getWmicPath());
  std::unique_ptr<std::string> temp = std::make_unique<std::string>();
  std::unique_ptr<int> tempInt = std::make_unique<int>();
  std::unique_ptr<std::smatch> mt = std::make_unique<std::smatch>();
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

  manufacturer = std::make_unique<std::string>(runWmic("cpu get Manufacturer", wmicPath.get()));
  cores = std::make_unique<std::uint8_t>(std::stoi(runWmic("cpu get NumberOfCores", wmicPath.get())));
  threads = std::make_unique<std::uint8_t>(std::stoi(runWmic("cpu get NumberOfLogicalProcessors", wmicPath.get())));

  architecture = std::make_unique<std::string>(architectureMap[std::stoi(runWmic("cpu get Architecture", wmicPath.get()))]);
  socketType = std::make_unique<std::string>(socketTypeMap[std::stoi(runWmic("cpu get UpgradeMethod", wmicPath.get()))]);

  brand = std::make_unique<std::string>(runWmic("cpu get Name", wmicPath.get()));
  brand->erase(brand->find_first_of("@"));
  trim(brand.get());

  temp = std::make_unique<std::string>(runWmic("cpu get Description", wmicPath.get()));
  if (std::regex_search((*temp), (*mt), std::regex(R"(.*Family (\d+) Model (\d+) Stepping (\d+))", std::regex_constants::ECMAScript|std::regex_constants::icase)))
  {
    family = std::make_unique<std::uint8_t>(std::stoi((*mt)[1]));
    model = std::make_unique<std::uint8_t>(std::stoi((*mt)[2]));
    stepping = std::make_unique<std::uint8_t>(std::stoi((*mt)[3]));
  }

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
#pragma endregion "Accessors"
