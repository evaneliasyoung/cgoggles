/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-04-22
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#include "pch.h"
#include "requests.h"
#include "utils.h"
#include "os.h"
#include "processor.h"
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
  std::unique_ptr<std::vector<std::string>> valids = std::make_unique<std::vector<std::string>>();
  valids->push_back("ALL");
  valids->push_back("OS");
  valids->push_back("OS.ALL");
  valids->push_back("SYS");
  valids->push_back("SYS.ALL");
  valids->push_back("CPU");
  valids->push_back("CPU.ALL");
  valids->push_back("GPU");
  valids->push_back("GPU.ALL");
  valids->push_back("STORAGE");
  valids->push_back("STORAGE.ALL");
  valids->push_back("RAM");
  valids->push_back("RAM.ALL");
  valids->push_back("FS");
  valids->push_back("FS.ALL");
  valids->push_back("OS.PLATFORM");
  valids->push_back("OS.CAPTION");
  valids->push_back("OS.SERIAL");
  valids->push_back("OS.BIT");
  valids->push_back("OS.INSTALLTIME");
  valids->push_back("OS.BOOTTIME");
  valids->push_back("OS.CURTIME");
  valids->push_back("OS.KERNEL");
  valids->push_back("OS.VERSION");
  valids->push_back("SYS.MANUFACTURER");
  valids->push_back("SYS.MODEL");
  valids->push_back("SYS.VERSION");
  valids->push_back("SYS.SERIAL");
  valids->push_back("SYS.UUID");
  valids->push_back("CPU.MANUFACTURER");
  valids->push_back("CPU.ARCHITECTURE");
  valids->push_back("CPU.SOCKETTYPE");
  valids->push_back("CPU.BRAND");
  valids->push_back("CPU.FAMILY");
  valids->push_back("CPU.MODEL");
  valids->push_back("CPU.STEPPING");
  valids->push_back("CPU.CORES");
  valids->push_back("CPU.THREADS");
  valids->push_back("CPU.SPEED");
  valids->push_back("CPU.MAXSPEED");
  valids->push_back("GPU.VENDOR");
  valids->push_back("GPU.MODEL");
  valids->push_back("GPU.BUS");
  valids->push_back("GPU.VRAM");
  valids->push_back("GPU.DYNAMIC");
  valids->push_back("RAM.SIZE");
  valids->push_back("RAM.BANK");
  valids->push_back("RAM.TYPE");
  valids->push_back("RAM.SPEED");
  valids->push_back("RAM.FORMFACTOR");
  valids->push_back("RAM.MANUFACTURER");
  valids->push_back("RAM.PART");
  valids->push_back("RAM.SERIAL");
  valids->push_back("RAM.VOLTAGECONFIGURED");
  valids->push_back("RAM.VOLTAGEMIN");
  valids->push_back("RAM.VOLTAGEMAX");
  valids->push_back("STORAGE.NAME");
  valids->push_back("STORAGE.IDENTIFIER");
  valids->push_back("STORAGE.TYPE");
  valids->push_back("STORAGE.FILESYSTEM");
  valids->push_back("STORAGE.MOUNT");
  valids->push_back("STORAGE.TOTAL");
  valids->push_back("STORAGE.PHYSICAL");
  valids->push_back("STORAGE.UUID");
  valids->push_back("STORAGE.LABEL");
  valids->push_back("STORAGE.MODEL");
  valids->push_back("STORAGE.SERIAL");
  valids->push_back("STORAGE.REMOVABLE");
  valids->push_back("STORAGE.PROTOCOL");
  valids->push_back("FS.FS");
  valids->push_back("FS.TYPE");
  valids->push_back("FS.SIZE");
  valids->push_back("FS.USED");
  valids->push_back("FS.MOUNT");

  for (int i = requests.size() - 1; i >= 0; i--)
  {
    if (!contains(valids.get(), requests[i]))
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
  bool gpuAll = contains(&requests, "ALL") || contains(&requests, "GPU.ALL") || contains(&requests, "GPU");
  bool ramAll = contains(&requests, "ALL") || contains(&requests, "RAM.ALL") || contains(&requests, "RAM");
  bool stoAll = contains(&requests, "ALL") || contains(&requests, "STORAGE.ALL") || contains(&requests, "STORAGE");
  bool fsAll = contains(&requests, "ALL") || contains(&requests, "FS.ALL") || contains(&requests, "FS");

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
    vals->push_back(compOS.Platform());
  }
  if (osAll || contains(&requests, "OS.CAPTION"))
  {
    keys->push_back("os.Caption");
    vals->push_back(compOS.Caption());
  }
  if (osAll || contains(&requests, "OS.SERIAL"))
  {
    keys->push_back("os.Serial");
    vals->push_back(compOS.Serial());
  }
  if (osAll || contains(&requests, "OS.BIT"))
  {
    keys->push_back("os.Bit");
    vals->push_back(std::to_string(compOS.Bit()));
  }
  if (osAll || contains(&requests, "OS.INSTALLTIME"))
  {
    keys->push_back("os.InstallTime");
    vals->push_back(compOS.InstallTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "OS.BOOTTIME"))
  {
    keys->push_back("os.BootTime");
    vals->push_back(compOS.BootTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "OS.CURTIME"))
  {
    keys->push_back("os.CurTime");
    vals->push_back(compOS.CurTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "OS.KERNEL"))
  {
    keys->push_back("os.Kernel");
    vals->push_back(compOS.Kernel().Pretty());
  }
  if (osAll || contains(&requests, "OS.VERSION"))
  {
    keys->push_back("os.Version");
    vals->push_back(compOS.Version().Pretty());
  }

  if (sysAll || contains(&requests, "SYS.MANUFACTURER"))
  {
    keys->push_back("sys.Manufacturer");
    vals->push_back(compSys.Manufacturer());
  }
  if (sysAll || contains(&requests, "SYS.MODEL"))
  {
    keys->push_back("sys.Model");
    vals->push_back(compSys.Model());
  }
  if (sysAll || contains(&requests, "SYS.VERSION"))
  {
    keys->push_back("sys.Version");
    vals->push_back(compSys.Version());
  }
  if (sysAll || contains(&requests, "SYS.SERIAL"))
  {
    keys->push_back("sys.Serial");
    vals->push_back(compSys.Serial());
  }
  if (sysAll || contains(&requests, "SYS.UUID"))
  {
    keys->push_back("sys.UUID");
    vals->push_back(compSys.UUID());
  }

  if (cpuAll || contains(&requests, "CPU.MANUFACTURER"))
  {
    keys->push_back("cpu.Manufacturer");
    vals->push_back(compCPU.Manufacturer());
  }
  if (cpuAll || contains(&requests, "CPU.ARCHITECTURE"))
  {
    keys->push_back("cpu.Architecture");
    vals->push_back(compCPU.Architecture());
  }
  if (cpuAll || contains(&requests, "CPU.SOCKETTYPE"))
  {
    keys->push_back("cpu.SocketType");
    vals->push_back(compCPU.SocketType());
  }
  if (cpuAll || contains(&requests, "CPU.BRAND"))
  {
    keys->push_back("cpu.Brand");
    vals->push_back(compCPU.Brand());
  }
  if (cpuAll || contains(&requests, "CPU.FAMILY"))
  {
    keys->push_back("cpu.Family");
    vals->push_back(std::to_string(compCPU.Family()));
  }
  if (cpuAll || contains(&requests, "CPU.MODEL"))
  {
    keys->push_back("cpu.Model");
    vals->push_back(std::to_string(compCPU.Model()));
  }
  if (cpuAll || contains(&requests, "CPU.STEPPING"))
  {
    keys->push_back("cpu.Stepping");
    vals->push_back(std::to_string(compCPU.Stepping()));
  }
  if (cpuAll || contains(&requests, "CPU.CORES"))
  {
    keys->push_back("cpu.Cores");
    vals->push_back(std::to_string(compCPU.Cores()));
  }
  if (cpuAll || contains(&requests, "CPU.THREADS"))
  {
    keys->push_back("cpu.Threads");
    vals->push_back(std::to_string(compCPU.Threads()));
  }
  if (cpuAll || contains(&requests, "CPU.SPEED"))
  {
    keys->push_back("cpu.Speed");
    vals->push_back(pretty
                        ? siUnits(compCPU.Speed(), 2, "Hz")
                        : std::to_string(compCPU.Speed()));
  }
  if (cpuAll || contains(&requests, "CPU.MAXSPEED"))
  {
    keys->push_back("cpu.MaxSpeed");
    vals->push_back(pretty
                        ? siUnits(compCPU.MaxSpeed(), 2, "Hz")
                        : std::to_string(compCPU.MaxSpeed()));
  }

  for (std::size_t i = 0; i < compGPU.Controllers().size(); i++)
  {
    if (gpuAll || contains(&requests, "GPU.VENDOR"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Vendor");
      vals->push_back(compGPU.Controllers()[i].Vendor());
    }
    if (gpuAll || contains(&requests, "GPU.MODEL"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Model");
      vals->push_back(compGPU.Controllers()[i].Model());
    }
    if (gpuAll || contains(&requests, "GPU.BUS"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Bus");
      vals->push_back(compGPU.Controllers()[i].Bus());
    }
    if (gpuAll || contains(&requests, "GPU.VRAM"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].VRAM");
      vals->push_back(pretty ? prettyOutputStorage(compGPU.Controllers()[i].VRAM())
                             : std::to_string(compGPU.Controllers()[i].VRAM()));
    }
    if (gpuAll || contains(&requests, "GPU.DYNAMIC"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Dynamic");
      vals->push_back(compGPU.Controllers()[i].Dynamic() ? "Yes" : "No");
    }
  }

  for (std::size_t i = 0; i < compRAM.Chips().size(); i++)
  {
    if (ramAll || contains(&requests, "RAM.SIZE"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Size");
      vals->push_back(pretty
                          ? prettyOutputStorage(compRAM.Chips()[i].Size(), 0)
                          : std::to_string(compRAM.Chips()[i].Size()));
    }
    if (ramAll || contains(&requests, "RAM.BANK"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Bank");
      vals->push_back(compRAM.Chips()[i].Bank());
    }
    if (ramAll || contains(&requests, "RAM.TYPE"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Type");
      vals->push_back(compRAM.Chips()[i].Type());
    }
    if (ramAll || contains(&requests, "RAM.SPEED"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Speed");
      vals->push_back(pretty
                          ? siUnits(compRAM.Chips()[i].Speed(), 2, "Hz")
                          : std::to_string(compRAM.Chips()[i].Speed()));
    }
    if (ramAll || contains(&requests, "RAM.FORMFACTOR"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].FormFactor");
      vals->push_back(compRAM.Chips()[i].FormFactor());
    }
    if (ramAll || contains(&requests, "RAM.MANUFACTURER"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Manufacturer");
      vals->push_back(compRAM.Chips()[i].Manufacturer());
    }
    if (ramAll || contains(&requests, "RAM.PART"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Part");
      vals->push_back(compRAM.Chips()[i].Part());
    }
    if (ramAll || contains(&requests, "RAM.SERIAL"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Serial");
      vals->push_back(compRAM.Chips()[i].Serial());
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGECONFIGURED"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageConfigured");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageConfigured());
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGEMIN"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMin");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageMin());
    }
    if (ramAll || contains(&requests, "RAM.VOLTAGEMAX"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMax");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageMax());
    }
  }

  for (std::size_t i = 0; i < compStorage.Drives().size(); i++)
  {
    if (stoAll || contains(&requests, "STORAGE.NAME"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Name");
      vals->push_back(compStorage.Drives()[i].Name());
    }
    if (stoAll || contains(&requests, "STORAGE.IDENTIFIER"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Identifier");
      vals->push_back(compStorage.Drives()[i].Identifier());
    }
    if (stoAll || contains(&requests, "STORAGE.TYPE"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Type");
      vals->push_back(compStorage.Drives()[i].Type());
    }
    if (stoAll || contains(&requests, "STORAGE.FILESYSTEM"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].FileSystem");
      vals->push_back(compStorage.Drives()[i].FileSystem());
    }
    if (stoAll || contains(&requests, "STORAGE.MOUNT"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Mount");
      vals->push_back(compStorage.Drives()[i].Mount());
    }
    if (stoAll || contains(&requests, "STORAGE.TOTAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Total");
      vals->push_back(pretty ? prettyOutputStorage(compStorage.Drives()[i].Total())
                             : std::to_string(compStorage.Drives()[i].Total()));
    }
    if (stoAll || contains(&requests, "STORAGE.PHYSICAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Physical");
      vals->push_back(compStorage.Drives()[i].Physical());
    }
    if (stoAll || contains(&requests, "STORAGE.UUID"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].UUID");
      vals->push_back(compStorage.Drives()[i].UUID());
    }
    if (stoAll || contains(&requests, "STORAGE.LABEL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Label");
      vals->push_back(compStorage.Drives()[i].Label());
    }
    if (stoAll || contains(&requests, "STORAGE.MODEL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Model");
      vals->push_back(compStorage.Drives()[i].Model());
    }
    if (stoAll || contains(&requests, "STORAGE.SERIAL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Serial");
      vals->push_back(compStorage.Drives()[i].Serial());
    }
    if (stoAll || contains(&requests, "STORAGE.REMOVABLE"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Removable");
      vals->push_back(compStorage.Drives()[i].Removable() ? "Yes" : "No");
    }
    if (stoAll || contains(&requests, "STORAGE.PROTOCOL"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Protocol");
      vals->push_back(compStorage.Drives()[i].Protocol());
    }
  }

  for (std::size_t i = 0; i < compFS.FileSystems().size(); i++)
  {
    if (fsAll || contains(&requests, "FS.FS"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].FS");
      vals->push_back(compFS.FileSystems()[i].FS());
    }
    if (fsAll || contains(&requests, "FS.TYPE"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Type");
      vals->push_back(compFS.FileSystems()[i].Type());
    }
    if (fsAll || contains(&requests, "FS.SIZE"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Size");
      vals->push_back(pretty ? prettyOutputStorage(compFS.FileSystems()[i].Size())
                             : std::to_string(compFS.FileSystems()[i].Size()));
    }
    if (fsAll || contains(&requests, "FS.USED"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Used");
      vals->push_back(pretty ? prettyOutputStorage(compFS.FileSystems()[i].Used())
                             : std::to_string(compFS.FileSystems()[i].Used()));
    }
    if (fsAll || contains(&requests, "FS.MOUNT"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Mount");
      vals->push_back(compFS.FileSystems()[i].Mount());
    }
  }
}

void outputSimple(std::ostream &stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const char &del)
{
  for (std::size_t i = 0; i < keys->size(); i++)
  {
    stream << (*keys)[i] << del << (*vals)[i] << std::endl;
  }
}

void outputJson(std::ostream &stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const bool &min)
{
  std::string curBeg;
  std::string nl = min ? "" : "\n";
  std::string sp = min ? "" : " ";
  std::string ck;
  std::string cv;

  stream << "{" << nl;
  for (std::size_t i = 0; i < keys->size(); i++)
  {
    ck = (*keys)[i];
    cv = (*vals)[i];

    // New beginning
    if (curBeg != ck.substr(0, ck.find('.')))
    {
      // If not empty, end the last section
      if (curBeg != "")
      {
        stream << sp << sp << "}," << nl;
      }

      // Set up the new beginning
      curBeg = ck.substr(0, ck.find('.'));
      stream << sp << sp << '"' << curBeg << R"(":)" << sp << '{' << nl;
    }

    stream << sp << sp << sp << sp;
    stream << ck.substr(ck.find('.') + 1) << R"(":)" << sp << cv << '"';
    stream << (i < keys->size() - 1 && curBeg == (*keys)[i + 1].substr(0, (*keys)[i + 1].find('.')) ? "," : "") << nl;
  }

  stream << sp << sp << '}' << nl << '}' << nl;
}

/**
* @brief Outputs all of the requests
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
    outputSimple(stream, keys, vals);
    break;
  case OutputStyle::List:
    outputSimple(stream, keys, vals, '=');
    break;
  case OutputStyle::JSON:
    outputJson(stream, keys, vals);
    break;
  case OutputStyle::MinJSON:
    outputJson(stream, keys, vals, true);
    break;
  }
}
