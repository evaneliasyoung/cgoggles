/**
*  @file      requests.h
*  @brief     The interface for the requests tools.
*
*  @author    Evan Elias Young
*  @date      2019-03-15
*  @date      2020-02-29
*  @copyright Copyright 2019-2020 Evan Elias Young. All rights reserved.
*/

#ifndef CGOGGLES_REQUESTS_H_
#define CGOGGLES_REQUESTS_H_

#include "pch.h"
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

extern std::vector<std::string> requests;
extern OutputStyle style;
extern bool pretty;

extern OperatingSystem compOS;
extern System compSys;
extern Processor compCPU;
extern Chassis compChassis;
extern GraphicsList compGPU;
extern RAMList compRAM;
extern StorageList compStorage;
extern FileSystemList compFS;

void filterRequests();
void parseRequests(std::string *request);
void gatherCategories(std::vector<std::string> *cats);
void gatherRequests(std::vector<std::string> *keys, std::vector<std::string> *vals, std::vector<std::string> *cats);
void outputSimple(std::ostream &stream, std::vector<std::string> *keys, std::vector<std::string> *vals, const char &del = '\n');
void outputValue(std::ostream &stream, std::vector<std::string> *vals);
void outputRequests(std::ostream &stream = std::cout);

#endif // CGOGGLES_REQUESTS_H_
