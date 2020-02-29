/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "requests.h"
#include "utils.h"
#include "os.h"
#include "processor.h"
#include "chassis.h"
#include "ram.h"
#include "ramlist.h"
#include "storage.h"
#include "storagelist.h"
#include "fs.h"
#include "fslist.h"
#include "graphics.h"
#include "graphicslist.h"
#include "system.h"

/**
* @brief Filters out any unsupported requests from the queue
*/
void filterRequests()
{
  std::vector<std::string> valids = {
      "ALL", "OS", "OS.ALL", "SYS", "SYS.ALL", "CPU", "CPU.ALL", "GPU", "GPU.ALL", "STORAGE", "STORAGE.ALL", "RAM", "RAM.ALL", "FS", "FS.ALL", "CHASSIS", "CHASSIS.ALL",
      "OS.PLATFORM", "OS.CAPTION", "OS.SERIAL", "OS.BIT", "OS.INSTALLTIME", "OS.BOOTTIME", "OS.CURTIME", "OS.KERNEL", "OS.VERSION",
      "SYS.MANUFACTURER", "SYS.MODEL", "SYS.VERSION", "SYS.SERIAL", "SYS.UUID",
      "CPU.MANUFACTURER", "CPU.ARCHITECTURE", "CPU.SOCKETTYPE", "CPU.BRAND", "CPU.FAMILY", "CPU.MODEL", "CPU.STEPPING", "CPU.CORES", "CPU.THREADS", "CPU.SPEED", "CPU.MAXSPEED",
      "CHASSIS.MANUFACTURER", "CHASSIS.MODEL", "CHASSIS.TYPE", "CHASSIS.VERSION", "CHASSIS.SERIAL", "CHASSIS.ASSETTAG",
      "GPU.VENDOR", "GPU.MODEL", "GPU.BUS", "GPU.VRAM", "GPU.DYNAMIC",
      "RAM.SIZE", "RAM.BANK", "RAM.TYPE", "RAM.SPEED", "RAM.FORMFACTOR", "RAM.MANUFACTURER", "RAM.PART", "RAM.SERIAL", "RAM.VOLTAGECONFIGURED", "RAM.VOLTAGEMIN", "RAM.VOLTAGEMAX",
      "STORAGE.NAME", "STORAGE.IDENTIFIER", "STORAGE.TYPE", "STORAGE.FILESYSTEM", "STORAGE.MOUNT", "STORAGE.TOTAL", "STORAGE.PHYSICAL", "STORAGE.UUID", "STORAGE.LABEL", "STORAGE.MODEL", "STORAGE.SERIAL", "STORAGE.REMOVABLE", "STORAGE.PROTOCOL",
      "FS.FS", "FS.TYPE", "FS.SIZE", "FS.USED", "FS.MOUNT"};

  for (int i = requests.size() - 1; i > 0; --i)
  {
    if (!contains(&valids, requests[i]))
    {
      requests.erase(requests.begin() + i);
    }
  }
  removeDuplicates(&requests);
}

/**
* @brief Turns the raw request string into a collection of requests
*
* @param request A pointer to the raw request
*/
void parseRequests(std::string *request)
{
  splitStringVector((*request), ",", &requests);
  filterRequests();
}

/**
* @brief Turns a list of requests into a list of categories
*/
void gatherCategories(std::vector<std::string> *cats)
{
  std::string cur;
  bool addAll = contains(&requests, "ALL");
  bool addOS = false;
  bool addSYS = false;
  bool addCPU = false;
  bool addCHASSIS = false;
  bool addGPU = false;
  bool addRAM = false;
  bool addSTORAGE = false;
  bool addFS = false;

  for (std::size_t i = 0; i < requests.size(); ++i)
  {
    cur = requests[i];

    if (!addOS && (addAll || startswith(cur, "OS")))
    {
      cats->push_back("OS");
      addOS = true;
    }
    if (!addSYS && (addAll || startswith(cur, "SYS")))
    {
      cats->push_back("SYS");
      addSYS = true;
    }
    if (!addCPU && (addAll || startswith(cur, "CPU")))
    {
      cats->push_back("CPU");
      addCPU = true;
    }
    if (!addCHASSIS && (addAll || startswith(cur, "CHASSIS")))
    {
      cats->push_back("CHASSIS");
      addCHASSIS = true;
    }
    if (!addGPU && (addAll || startswith(cur, "GPU")))
    {
      cats->push_back("GPU");
      addGPU = true;
    }
    if (!addRAM && (addAll || startswith(cur, "RAM")))
    {
      cats->push_back("RAM");
      addRAM = true;
    }
    if (!addSTORAGE && (addAll || startswith(cur, "STORAGE")))
    {
      cats->push_back("STORAGE");
      addSTORAGE = true;
    }
    if (!addFS && (addAll || startswith(cur, "FS")))
    {
      cats->push_back("FS");
      addFS = true;
    }
  }
}

/**
* @brief Turns the list of requests into a list of data
*/
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals, std::vector<std::string> *cats)
{
  bool osAll = contains(&requests, "ALL") || contains(&requests, "OS.ALL") || contains(&requests, "OS");
  bool sysAll = contains(&requests, "ALL") || contains(&requests, "SYS.ALL") || contains(&requests, "SYS");
  bool cpuAll = contains(&requests, "ALL") || contains(&requests, "CPU.ALL") || contains(&requests, "CPU");
  bool chassisAll = contains(&requests, "ALL") || contains(&requests, "CHASSIS.ALL") || contains(&requests, "CHASSIS");
  bool gpuAll = contains(&requests, "ALL") || contains(&requests, "GPU.ALL") || contains(&requests, "GPU");
  bool ramAll = contains(&requests, "ALL") || contains(&requests, "RAM.ALL") || contains(&requests, "RAM");
  bool stoAll = contains(&requests, "ALL") || contains(&requests, "STORAGE.ALL") || contains(&requests, "STORAGE");
  bool fsAll = contains(&requests, "ALL") || contains(&requests, "FS.ALL") || contains(&requests, "FS");
  std::stringstream buffer;

  if (contains(cats, "OS"))
  {
    compOS = new OperatingSystem(CGOGGLES_OS);
  }
  if (contains(cats, "SYS"))
  {
    compSys = new System(CGOGGLES_OS);
  }
  if (contains(cats, "CPU"))
  {
    compCPU = new Processor(CGOGGLES_OS);
  }
  if (contains(cats, "CHASSIS"))
  {
    compChassis = new Chassis(CGOGGLES_OS);
  }
  if (contains(cats, "GPU"))
  {
    compGPU = new GraphicsList(CGOGGLES_OS);
  }
  if (contains(cats, "RAM"))
  {
    compRAM = new RAMList(CGOGGLES_OS);
  }
  if (contains(cats, "STORAGE"))
  {
    compStorage = new StorageList(CGOGGLES_OS);
  }
  if (contains(cats, "FS"))
  {
    compFS = new FileSystemList(CGOGGLES_OS);
  }

  if (osAll || contains(&requests, "OS.PLATFORM"))
  {
    keys->push_back("os.Platform");
    vals->push_back(compOS.platform);
  }
  if (osAll || contains(&requests, "OS.CAPTION"))
  {
    keys->push_back("os.Caption");
    vals->push_back(compOS.caption);
  }
  if (osAll || contains(&requests, "OS.SERIAL"))
  {
    keys->push_back("os.Serial");
    vals->push_back(compOS.serial);
  }
  if (osAll || contains(&requests, "OS.BIT"))
  {
    keys->push_back("os.Bit");
    vals->push_back(std::to_string(compOS.bit));
  }
  if (osAll || contains(&requests, "OS.INSTALLTIME"))
  {
    buffer << std::put_time(&compOS.installTime, "%Y-%m-%dT%H:%M:%S");
    keys->push_back("os.InstallTime");
    vals->push_back(buffer.str());
    buffer.str("");
  }
  if (osAll || contains(&requests, "OS.BOOTTIME"))
  {
    buffer << std::put_time(&compOS.bootTime, "%Y-%m-%dT%H:%M:%S");
    keys->push_back("os.BootTime");
    vals->push_back(buffer.str());
    buffer.str("");
  }
  if (osAll || contains(&requests, "OS.CURTIME"))
  {
    buffer << std::put_time(&compOS.curTime, "%Y-%m-%dT%H:%M:%S");
    keys->push_back("os.CurTime");
    vals->push_back(buffer.str());
    buffer.str("");
  }
  if (osAll || contains(&requests, "OS.KERNEL"))
  {
    keys->push_back("os.Kernel");
    vals->push_back(compOS.kernel.Pretty());
  }
  if (osAll || contains(&requests, "OS.VERSION"))
  {
    keys->push_back("os.Version");
    vals->push_back(compOS.version.Pretty());
  }

  if (sysAll || contains(&requests, "SYS.MANUFACTURER"))
  {
    keys->push_back("sys.Manufacturer");
    vals->push_back(compSys.manufacturer);
  }
  if (sysAll || contains(&requests, "SYS.MODEL"))
  {
    keys->push_back("sys.Model");
    vals->push_back(compSys.model);
  }
  if (sysAll || contains(&requests, "SYS.VERSION"))
  {
    keys->push_back("sys.Version");
    vals->push_back(compSys.version);
  }
  if (sysAll || contains(&requests, "SYS.SERIAL"))
  {
    keys->push_back("sys.Serial");
    vals->push_back(compSys.serial);
  }
  if (sysAll || contains(&requests, "SYS.UUID"))
  {
    keys->push_back("sys.UUID");
    vals->push_back(compSys.uuid);
  }

  if (cpuAll || contains(&requests, "CPU.MANUFACTURER"))
  {
    keys->push_back("cpu.Manufacturer");
    vals->push_back(compCPU.manufacturer);
  }
  if (cpuAll || contains(&requests, "CPU.ARCHITECTURE"))
  {
    keys->push_back("cpu.Architecture");
    vals->push_back(compCPU.architecture);
  }
  if (cpuAll || contains(&requests, "CPU.SOCKETTYPE"))
  {
    keys->push_back("cpu.SocketType");
    vals->push_back(compCPU.socketType);
  }
  if (cpuAll || contains(&requests, "CPU.BRAND"))
  {
    keys->push_back("cpu.Brand");
    vals->push_back(compCPU.brand);
  }
  if (cpuAll || contains(&requests, "CPU.FAMILY"))
  {
    keys->push_back("cpu.Family");
    vals->push_back(std::to_string(compCPU.family));
  }
  if (cpuAll || contains(&requests, "CPU.MODEL"))
  {
    keys->push_back("cpu.Model");
    vals->push_back(std::to_string(compCPU.model));
  }
  if (cpuAll || contains(&requests, "CPU.STEPPING"))
  {
    keys->push_back("cpu.Stepping");
    vals->push_back(std::to_string(compCPU.stepping));
  }
  if (cpuAll || contains(&requests, "CPU.CORES"))
  {
    keys->push_back("cpu.Cores");
    vals->push_back(std::to_string(compCPU.cores));
  }
  if (cpuAll || contains(&requests, "CPU.THREADS"))
  {
    keys->push_back("cpu.Threads");
    vals->push_back(std::to_string(compCPU.threads));
  }
  if (cpuAll || contains(&requests, "CPU.SPEED"))
  {
    keys->push_back("cpu.Speed");
    vals->push_back(pretty
                        ? siUnits(compCPU.speed, "Hz")
                        : std::to_string(compCPU.speed));
  }
  if (cpuAll || contains(&requests, "CPU.MAXSPEED"))
  {
    keys->push_back("cpu.MaxSpeed");
    vals->push_back(pretty
                        ? siUnits(compCPU.maxSpeed, "Hz")
                        : std::to_string(compCPU.maxSpeed));
  }

  if (chassisAll || contains(&requests, "CHASSIS.MANUFACTURER"))
  {
    keys->push_back("chassis.Manufacturer");
    vals->push_back(compChassis.manufacturer);
  }
  if (chassisAll || contains(&requests, "CHASSIS.MODEL"))
  {
    keys->push_back("chassis.Model");
    vals->push_back(compChassis.model);
  }
  if (chassisAll || contains(&requests, "CHASSIS.TYPE"))
  {
    keys->push_back("chassis.Type");
    vals->push_back(compChassis.type);
  }
  if (chassisAll || contains(&requests, "CHASSIS.VERSION"))
  {
    keys->push_back("chassis.Version");
    vals->push_back(compChassis.version);
  }
  if (chassisAll || contains(&requests, "CHASSIS.SERIAL"))
  {
    keys->push_back("chassis.Serial");
    vals->push_back(compChassis.serial);
  }
  if (chassisAll || contains(&requests, "CHASSIS.ASSETTAG"))
  {
    keys->push_back("chassis.AssetTag");
    vals->push_back(compChassis.assetTag);
  }

  for (std::size_t i = 0; i < compGPU.controllers.size(); ++i)
  {
    if (gpuAll || contains(&requests, "GPU.VENDOR"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Vendor");
      vals->push_back(compGPU.controllers[i].vendor);
    }
    if (gpuAll || contains(&requests, "GPU.MODEL"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Model");
      vals->push_back(compGPU.controllers[i].model);
    }
    if (gpuAll || contains(&requests, "GPU.BUS"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Bus");
      vals->push_back(compGPU.controllers[i].bus);
    }
    if (gpuAll || contains(&requests, "GPU.VRAM"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].VRAM");
      vals->push_back(pretty ? siUnits(compGPU.controllers[i].vram, "B")
                             : std::to_string(compGPU.controllers[i].vram));
    }
    if (gpuAll || contains(&requests, "GPU.DYNAMIC"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Dynamic");
      vals->push_back(compGPU.controllers[i].dynamic ? "Yes" : "No");
    }
  }

  for (std::size_t i = 0; i < compRAM.chips.size(); ++i)
  {
    if (ramAll || contains(&requests, "RAM.SIZE"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Size");
      vals->push_back(pretty
                          ? siUnits(compRAM.chips[i].size, "B", 0)
                          : std::to_string(compRAM.chips[i].size));
    }
    if (ramAll || contains(&requests, "RAM.BANK"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Bank");
      vals->push_back(compRAM.chips[i].bank);
    }
    if (ramAll || contains(&requests, "RAM.TYPE"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Type");
      vals->push_back(compRAM.chips[i].type);
    }
    if (ramAll || contains(&requests, "RAM.SPEED"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Speed");
      vals->push_back(pretty
                          ? siUnits(compRAM.chips[i].speed, "Hz")
                          : std::to_string(compRAM.chips[i].speed));
    }
    if (ramAll || contains(&requests, "RAM.FORMFACTOR"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].FormFactor");
      vals->push_back(compRAM.chips[i].formFactor);
    }
    if (ramAll || contains(&requests, "RAM.MANUFACTURER"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Manufacturer");
      vals->push_back(compRAM.chips[i].manufacturer);
    }
    if (ramAll || contains(&requests, "RAM.PART"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Part");
      vals->push_back(compRAM.chips[i].part);
    }
    if (ramAll || contains(&requests, "RAM.SERIAL"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Serial");
      vals->push_back(compRAM.chips[i].serial);
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGECONFIGURED"))
    {
      buffer << std::fixed << std::setprecision(1) << compRAM.chips[i].voltageConfigured << " V";
      keys->push_back("ram[" + std::to_string(i) + "].VoltageConfigured");
      vals->push_back(buffer.str());
      buffer.str("");
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGEMIN"))
    {
      buffer << std::fixed << std::setprecision(1) << compRAM.chips[i].voltageMin << " V";
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMin");
      vals->push_back(buffer.str());
      buffer.str("");
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGEMAX"))
    {
      buffer << std::fixed << std::setprecision(1) << compRAM.chips[i].voltageMax << " V";
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMax");
      vals->push_back(buffer.str());
      buffer.str("");
    }
  }

  for (std::size_t i = 0; i < compStorage.drives.size(); ++i)
  {
    if (stoAll || contains(&requests, "STORAGE.NAME"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Name");
      vals->push_back(compStorage.drives[i].name);
    }
    if (stoAll || contains(&requests, "STORAGE.IDENTIFIER"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Identifier");
      vals->push_back(compStorage.drives[i].identifier);
    }
    if (stoAll || contains(&requests, "STORAGE.TYPE"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Type");
      vals->push_back(compStorage.drives[i].type);
    }
    if (stoAll || contains(&requests, "STORAGE.FILESYSTEM"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].FileSystem");
      vals->push_back(compStorage.drives[i].filesystem);
    }
    if (stoAll || contains(&requests, "STORAGE.MOUNT"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Mount");
      vals->push_back(compStorage.drives[i].mount);
    }
    if (stoAll || contains(&requests, "STORAGE.TOTAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Total");
      vals->push_back(pretty ? siUnits(compStorage.drives[i].total, "B")
                             : std::to_string(compStorage.drives[i].total));
    }
    if (stoAll || contains(&requests, "STORAGE.PHYSICAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Physical");
      vals->push_back(compStorage.drives[i].physical);
    }
    if (stoAll || contains(&requests, "STORAGE.UUID"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].UUID");
      vals->push_back(compStorage.drives[i].uuid);
    }
    if (stoAll || contains(&requests, "STORAGE.LABEL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Label");
      vals->push_back(compStorage.drives[i].label);
    }
    if (stoAll || contains(&requests, "STORAGE.MODEL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Model");
      vals->push_back(compStorage.drives[i].model);
    }
    if (stoAll || contains(&requests, "STORAGE.SERIAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Serial");
      vals->push_back(compStorage.drives[i].serial);
    }
    if (stoAll || contains(&requests, "STORAGE.REMOVABLE"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Removable");
      vals->push_back(compStorage.drives[i].removable ? "Yes" : "No");
    }
    if (stoAll || contains(&requests, "STORAGE.PROTOCOL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Protocol");
      vals->push_back(compStorage.drives[i].protocol);
    }
  }

  for (std::size_t i = 0; i < compFS.fsList.size(); ++i)
  {
    if (fsAll || contains(&requests, "FS.FS"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].FS");
      vals->push_back(compFS.fsList[i].fs);
    }
    if (fsAll || contains(&requests, "FS.TYPE"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Type");
      vals->push_back(compFS.fsList[i].type);
    }
    if (fsAll || contains(&requests, "FS.SIZE"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Size");
      vals->push_back(pretty ? siUnits(compFS.fsList[i].size, "B")
                             : std::to_string(compFS.fsList[i].size));
    }
    if (fsAll || contains(&requests, "FS.USED"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Used");
      vals->push_back(pretty ? siUnits(compFS.fsList[i].used, "B")
                             : std::to_string(compFS.fsList[i].used));
    }
    if (fsAll || contains(&requests, "FS.MOUNT"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Mount");
      vals->push_back(compFS.fsList[i].mount);
    }
  }
}

/**
* @brief Processes simple output, like a list or default view
*
* @param stream The output stream
* @param keys   The keys to output
* @param vals   The values to output
* @param del    The delimiter character
*/
void outputSimple(std::ostream &stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const char &del)
{
  for (std::size_t i = 0; i < keys->size(); ++i)
  {
    stream << (*keys)[i] << del << (*vals)[i] << '\n';
  }
}

/**
* @brief Processes value output, just the values for the key(s)
*
* @param stream The output stream
* @param vals   The values to output
*/
void outputValue(std::ostream &stream, std::vector<std::string> *vals)
{
  for (std::size_t i = 0; i < vals->size(); ++i)
  {
    stream << (*vals)[i] << '\n';
  }
}

/**
* @brief Outputs all of the requests
*
* @param stream The output stream
*/
void outputRequests(std::ostream &stream)
{
  std::vector<std::string> *keys = new std::vector<std::string>;
  std::vector<std::string> *vals = new std::vector<std::string>;
  std::vector<std::string> *cats = new std::vector<std::string>;
  gatherCategories(cats);
  gatherRequests(keys, vals, cats);

  switch (style)
  {
  case OutputStyle::Default:
    return outputSimple(stream, keys, vals);
  case OutputStyle::List:
    return outputSimple(stream, keys, vals, '=');
  case OutputStyle::Value:
    return outputValue(stream, vals);
  }
}
