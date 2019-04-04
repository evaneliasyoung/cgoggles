/**
*  @file      requests.cpp
*  @brief     The implementation for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-04-04
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
  valids->push_back("All");
  valids->push_back("os");
  valids->push_back("os.All");
  valids->push_back("sys");
  valids->push_back("sys.All");
  valids->push_back("cpu");
  valids->push_back("cpu.All");
  valids->push_back("gpu");
  valids->push_back("gpu.All");
  valids->push_back("storage");
  valids->push_back("storage.All");
  valids->push_back("ram");
  valids->push_back("ram.All");
  valids->push_back("fs");
  valids->push_back("fs.All");
  valids->push_back("os.Platform");
  valids->push_back("os.Caption");
  valids->push_back("os.Serial");
  valids->push_back("os.Bit");
  valids->push_back("os.InstallTime");
  valids->push_back("os.BootTime");
  valids->push_back("os.CurTime");
  valids->push_back("os.Kernel");
  valids->push_back("os.Version");
  valids->push_back("sys.Manufacturer");
  valids->push_back("sys.Model");
  valids->push_back("sys.Version");
  valids->push_back("sys.Serial");
  valids->push_back("sys.UUID");
  valids->push_back("cpu.Manufacturer");
  valids->push_back("cpu.Architecture");
  valids->push_back("cpu.SocketType");
  valids->push_back("cpu.Brand");
  valids->push_back("cpu.Family");
  valids->push_back("cpu.Model");
  valids->push_back("cpu.Stepping");
  valids->push_back("cpu.Cores");
  valids->push_back("cpu.Threads");
  valids->push_back("cpu.Speed");
  valids->push_back("cpu.MaxSpeed");
  valids->push_back("gpu.Vendor");
  valids->push_back("gpu.Model");
  valids->push_back("gpu.Bus");
  valids->push_back("gpu.VRAM");
  valids->push_back("gpu.Dynamic");
  valids->push_back("ram.Size");
  valids->push_back("ram.Bank");
  valids->push_back("ram.Type");
  valids->push_back("ram.Speed");
  valids->push_back("ram.FormFactor");
  valids->push_back("ram.Manufacturer");
  valids->push_back("ram.Part");
  valids->push_back("ram.Serial");
  valids->push_back("ram.VoltageConfigured");
  valids->push_back("ram.VoltageMin");
  valids->push_back("ram.VoltageMax");
  valids->push_back("storage.Name");
  valids->push_back("storage.Identifier");
  valids->push_back("storage.Type");
  valids->push_back("storage.FileSystem");
  valids->push_back("storage.Mount");
  valids->push_back("storage.Total");
  valids->push_back("storage.Physical");
  valids->push_back("storage.UUID");
  valids->push_back("storage.Label");
  valids->push_back("storage.Model");
  valids->push_back("storage.Serial");
  valids->push_back("storage.Removable");
  valids->push_back("storage.Protocol");
  valids->push_back("fs.FS");
  valids->push_back("fs.Type");
  valids->push_back("fs.Size");
  valids->push_back("fs.Used");
  valids->push_back("fs.Mount");

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
* @brief Turns the list of requests into a list of data
*/
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals)
{
  bool osAll = contains(&requests, "All") || contains(&requests, "os.All") || contains(&requests, "os");
  bool sysAll = contains(&requests, "All") || contains(&requests, "sys.All") || contains(&requests, "sys");
  bool cpuAll = contains(&requests, "All") || contains(&requests, "cpu.All") || contains(&requests, "cpu");
  bool ramAll = contains(&requests, "All") || contains(&requests, "ram.All") || contains(&requests, "ram");
  bool stoAll = contains(&requests, "All") || contains(&requests, "storage.All") || contains(&requests, "storage");
  bool fsAll = contains(&requests, "All") || contains(&requests, "fs.All") || contains(&requests, "fs");
  bool gpuAll = contains(&requests, "All") || contains(&requests, "gpu.All") || contains(&requests, "gpu");

  if (osAll || contains(&requests, "os.Platform"))
  {
    keys->push_back("os.Platform");
    vals->push_back(compOS.Platform());
  }
  if (osAll || contains(&requests, "os.Caption"))
  {
    keys->push_back("os.Caption");
    vals->push_back(compOS.Caption());
  }
  if (osAll || contains(&requests, "os.Serial"))
  {
    keys->push_back("os.Serial");
    vals->push_back(compOS.Serial());
  }
  if (osAll || contains(&requests, "os.Bit"))
  {
    keys->push_back("os.Bit");
    vals->push_back(std::to_string(compOS.Bit()));
  }
  if (osAll || contains(&requests, "os.InstallTime"))
  {
    keys->push_back("os.InstallTime");
    vals->push_back(compOS.InstallTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "os.BootTime"))
  {
    keys->push_back("os.BootTime");
    vals->push_back(compOS.BootTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "os.CurTime"))
  {
    keys->push_back("os.CurTime");
    vals->push_back(compOS.CurTime("%Y-%m-%dT%H:%M:%S"));
  }
  if (osAll || contains(&requests, "os.Kernel"))
  {
    keys->push_back("os.Kernel");
    vals->push_back(compOS.Kernel().Pretty());
  }
  if (osAll || contains(&requests, "os.Version"))
  {
    keys->push_back("os.Version");
    vals->push_back(compOS.Version().Pretty());
  }

  if (sysAll || contains(&requests, "sys.Manufacturer"))
  {
    keys->push_back("sys.Manufacturer");
    vals->push_back(compSys.Manufacturer());
  }
  if (sysAll || contains(&requests, "sys.Model"))
  {
    keys->push_back("sys.Model");
    vals->push_back(compSys.Model());
  }
  if (sysAll || contains(&requests, "sys.Version"))
  {
    keys->push_back("sys.Version");
    vals->push_back(compSys.Version());
  }
  if (sysAll || contains(&requests, "sys.Serial"))
  {
    keys->push_back("sys.Serial");
    vals->push_back(compSys.Serial());
  }
  if (sysAll || contains(&requests, "sys.UUID"))
  {
    keys->push_back("sys.UUID");
    vals->push_back(compSys.UUID());
  }

  if (cpuAll || contains(&requests, "cpu.Manufacturer"))
  {
    keys->push_back("cpu.Manufacturer");
    vals->push_back(compCPU.Manufacturer());
  }
  if (cpuAll || contains(&requests, "cpu.Architecture"))
  {
    keys->push_back("cpu.Architecture");
    vals->push_back(compCPU.Architecture());
  }
  if (cpuAll || contains(&requests, "cpu.SocketType"))
  {
    keys->push_back("cpu.SocketType");
    vals->push_back(compCPU.SocketType());
  }
  if (cpuAll || contains(&requests, "cpu.Brand"))
  {
    keys->push_back("cpu.Brand");
    vals->push_back(compCPU.Brand());
  }
  if (cpuAll || contains(&requests, "cpu.Family"))
  {
    keys->push_back("cpu.Family");
    vals->push_back(std::to_string(compCPU.Family()));
  }
  if (cpuAll || contains(&requests, "cpu.Model"))
  {
    keys->push_back("cpu.Model");
    vals->push_back(std::to_string(compCPU.Model()));
  }
  if (cpuAll || contains(&requests, "cpu.Stepping"))
  {
    keys->push_back("cpu.Stepping");
    vals->push_back(std::to_string(compCPU.Stepping()));
  }
  if (cpuAll || contains(&requests, "cpu.Cores"))
  {
    keys->push_back("cpu.Cores");
    vals->push_back(std::to_string(compCPU.Cores()));
  }
  if (cpuAll || contains(&requests, "cpu.Threads"))
  {
    keys->push_back("cpu.Threads");
    vals->push_back(std::to_string(compCPU.Threads()));
  }
  if (cpuAll || contains(&requests, "cpu.Speed"))
  {
    keys->push_back("cpu.Speed");
    vals->push_back(compCPU.PrettySpeed());
  }
  if (cpuAll || contains(&requests, "cpu.MaxSpeed"))
  {
    keys->push_back("cpu.MaxSpeed");
    vals->push_back(compCPU.PrettyMaxSpeed());
  }

  for (std::size_t i = 0; i < compGPU.Controllers().size(); i++)
  {
    if (gpuAll || contains(&requests, "Vendor"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Vendor");
      vals->push_back(compGPU.Controllers()[i].Vendor());
    }
    if (gpuAll || contains(&requests, "Model"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Model");
      vals->push_back(compGPU.Controllers()[i].Model());
    }
    if (gpuAll || contains(&requests, "Bus"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Bus");
      vals->push_back(compGPU.Controllers()[i].Bus());
    }
    if (gpuAll || contains(&requests, "VRAM"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].VRAM");
      vals->push_back(std::to_string(compGPU.Controllers()[i].VRAM()));
    }
    if (gpuAll || contains(&requests, "Dynamic"))
    {
      keys->push_back("gpu[" + std::to_string(i) + "].Dynamic");
      vals->push_back(compGPU.Controllers()[i].Dynamic() ? "Yes" : "No");
    }
  }

  for (std::size_t i = 0; i < compRAM.Chips().size(); i++)
  {
    if (ramAll || contains(&requests, "Size"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Size");
      vals->push_back(std::to_string(compRAM.Chips()[i].Size()));
    }
    if (ramAll || contains(&requests, "Bank"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Bank");
      vals->push_back(compRAM.Chips()[i].Bank());
    }
    if (ramAll || contains(&requests, "Type"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Type");
      vals->push_back(compRAM.Chips()[i].Type());
    }
    if (ramAll || contains(&requests, "Speed"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Speed");
      vals->push_back(compRAM.Chips()[i].PrettySpeed());
    }
    if (ramAll || contains(&requests, "FormFactor"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].FormFactor");
      vals->push_back(compRAM.Chips()[i].FormFactor());
    }
    if (ramAll || contains(&requests, "Manufacturer"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Manufacturer");
      vals->push_back(compRAM.Chips()[i].Manufacturer());
    }
    if (ramAll || contains(&requests, "Part"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Part");
      vals->push_back(compRAM.Chips()[i].Part());
    }
    if (ramAll || contains(&requests, "Serial"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].Serial");
      vals->push_back(compRAM.Chips()[i].Serial());
    }
    if (ramAll || contains(&requests, "VoltageConfigured"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageConfigured");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageConfigured());
    }
    if (ramAll || contains(&requests, "VoltageMin"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMin");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageMin());
    }
    if (ramAll || contains(&requests, "VoltageMax"))
    {
      keys->push_back("ram[" + std::to_string(i) + "].VoltageMax");
      vals->push_back(compRAM.Chips()[i].PrettyVoltageMax());
    }
  }

  for (std::size_t i = 0; i < compStorage.Drives().size(); i++)
  {
    if (stoAll || contains(&requests, "storage.Name"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Name");
      vals->push_back(compStorage.Drives()[i].Name());
    }
    if (stoAll || contains(&requests, "storage.Identifier"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Identifier");
      vals->push_back(compStorage.Drives()[i].Identifier());
    }
    if (stoAll || contains(&requests, "storage.Type"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Type");
      vals->push_back(compStorage.Drives()[i].Type());
    }
    if (stoAll || contains(&requests, "storage.FileSystem"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].FileSystem");
      vals->push_back(compStorage.Drives()[i].FileSystem());
    }
    if (stoAll || contains(&requests, "storage.Mount"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Mount");
      vals->push_back(compStorage.Drives()[i].Mount());
    }
    if (stoAll || contains(&requests, "storage.Total"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Total");
      vals->push_back(std::to_string(compStorage.Drives()[i].Total()));
    }
    if (stoAll || contains(&requests, "storage.Physical"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Physical");
      vals->push_back(compStorage.Drives()[i].Physical());
    }
    if (stoAll || contains(&requests, "storage.UUID"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].UUID");
      vals->push_back(compStorage.Drives()[i].UUID());
    }
    if (stoAll || contains(&requests, "storage.Label"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Label");
      vals->push_back(compStorage.Drives()[i].Label());
    }
    if (stoAll || contains(&requests, "storage.Model"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Model");
      vals->push_back(compStorage.Drives()[i].Model());
    }
    if (stoAll || contains(&requests, "storage.Serial"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Serial");
      vals->push_back(compStorage.Drives()[i].Serial());
    }
    if (stoAll || contains(&requests, "storage.Removable"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Removable");
      vals->push_back(compStorage.Drives()[i].Removable() ? "Yes" : "No");
    }
    if (stoAll || contains(&requests, "storage.Protocol"))
    {
      keys->push_back("storage[" + std::to_string(i) + "].Protocol");
      vals->push_back(compStorage.Drives()[i].Protocol());
    }
  }

  for (std::size_t i = 0; i < compFS.FileSystems().size(); i++)
  {
    if (fsAll || contains(&requests, "fs.FS"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].FS");
      vals->push_back(compFS.FileSystems()[i].FS());
    }
    if (fsAll || contains(&requests, "fs.Type"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Type");
      vals->push_back(compFS.FileSystems()[i].Type());
    }
    if (fsAll || contains(&requests, "fs.Size"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Size");
      vals->push_back(std::to_string(compFS.FileSystems()[i].Size()));
    }
    if (fsAll || contains(&requests, "fs.Used"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Used");
      vals->push_back(std::to_string(compFS.FileSystems()[i].Used()));
    }
    if (fsAll || contains(&requests, "fs.Mount"))
    {
      keys->push_back("fs[" + std::to_string(i) + "].Mount");
      vals->push_back(compFS.FileSystems()[i].Mount());
    }
  }
}

void outputSimple(std::vector<std::string> *keys, std::vector<std::string> *vals, const char &del)
{
  for (std::size_t i = 0; i < keys->size(); i++)
  {
    std::cout << (*keys)[i] << del << (*vals)[i] << std::endl;
  }
}

void outputJson(std::vector<std::string> *keys, std::vector<std::string> *vals, const bool &min)
{
  std::string curBeg;
  std::string nl = min ? "" : "\n";
  std::string sp = min ? "" : " ";
  std::string ck;
  std::string cv;

  std::cout << "{" << nl;
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
        std::cout << sp << sp << "}," << nl;
      }

      // Set up the new beginning
      curBeg = ck.substr(0, ck.find('.'));
      std::cout << sp << sp << '"' << curBeg << R"(":)" << sp << '{' << nl;
    }

    std::cout << sp << sp << sp << sp;
    std::cout << ck.substr(ck.find('.') + 1) << R"(":)" << sp << cv << '"';
    std::cout << (i < keys->size() - 1 && curBeg == (*keys)[i + 1].substr(0, (*keys)[i + 1].find('.')) ? "," : "") << nl;
  }

  std::cout << sp << sp << '}' << nl << '}' << nl;
}

/**
* @brief Outputs all of the requests
*/
void outputRequests()
{
  std::unique_ptr<std::vector<std::string>> keys = std::make_unique<std::vector<std::string>>();
  std::unique_ptr<std::vector<std::string>> vals = std::make_unique<std::vector<std::string>>();
  gatherRequests(keys.get(), vals.get());

  switch (style)
  {
  case OutputStyle::Default:
    outputSimple(keys.get(), vals.get());
    break;
  case OutputStyle::List:
    outputSimple(keys.get(), vals.get(), '=');
    break;
  case OutputStyle::JSON:
    outputJson(keys.get(), vals.get());
    break;
  case OutputStyle::MinJSON:
    outputJson(keys.get(), vals.get(), true);
    break;
  }
}
