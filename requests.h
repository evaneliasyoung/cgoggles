/**
*  @file      requests.h
*  @brief     The interface for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2019-04-19
*  @copyright Copyright 2019 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_REQUESTS_H_
#define CGOGGLES_REQUESTS_H_

#include "pch.h"
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

extern std::vector<std::string> requests;
extern OutputStyle style;
extern bool pretty;

extern OperatingSystem compOS;
extern System compSys;
extern Processor compCPU;
extern GraphicsList compGPU;
extern RAMList compRAM;
extern StorageList compStorage;
extern FileSystemList compFS;

void filterRequests();
void parseRequests(std::string *request);
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals);
void outputSimple(std::ostream& stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const char &del = '\n');
void outputJson(std::ostream& stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const bool &min = false);
void outputRequests(std::ostream& stream = std::cout);

#endif // CGOGGLES_REQUESTS_H_
