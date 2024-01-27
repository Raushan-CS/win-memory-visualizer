#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>
#include <fstream>
#include <sstream>

#pragma comment(lib, "psapi.lib")

struct MemoryInfo {
    DWORDLONG totalPhysicalMemory;
    DWORDLONG freePhysicalMemory;
    DWORDLONG usedPhysicalMemory;
    DWORDLONG totalVirtualMemory;
    DWORDLONG freeVirtualMemory;
    DWORDLONG usedVirtualMemory;
    DWORDLONG totalPageFile;
    DWORDLONG freePageFile;
    DWORDLONG usedPageFile;
};

MemoryInfo GetMemoryInfo() {
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    GlobalMemoryStatusEx(&memoryStatus);

    MemoryInfo memoryInfo;
    memoryInfo.totalPhysicalMemory = memoryStatus.ullTotalPhys;
    memoryInfo.freePhysicalMemory = memoryStatus.ullAvailPhys;
    memoryInfo.usedPhysicalMemory = memoryInfo.totalPhysicalMemory - memoryInfo.freePhysicalMemory;
    memoryInfo.totalVirtualMemory = memoryStatus.ullTotalVirtual;
    memoryInfo.freeVirtualMemory = memoryStatus.ullAvailVirtual;
    memoryInfo.usedVirtualMemory = memoryInfo.totalVirtualMemory - memoryInfo.freeVirtualMemory;
    memoryInfo.totalPageFile = memoryStatus.ullTotalPageFile;
    memoryInfo.freePageFile = memoryStatus.ullAvailPageFile;
    memoryInfo.usedPageFile = memoryInfo.totalPageFile - memoryInfo.freePageFile;

    return memoryInfo;
}

void CreateDotFile(const MemoryInfo& memoryInfo, const std::string& dotFileName) {
    std::ofstream dotFile(dotFileName);
    dotFile << "digraph G {\n";
    dotFile << "node[shape=record]\n";
    dotFile << "Memory [label=\"{Physical Memory|Total: " << memoryInfo.totalPhysicalMemory / 1024 / 1024 << " MB|Free: " << memoryInfo.freePhysicalMemory / 1024 / 1024 << " MB|Used: " << memoryInfo.usedPhysicalMemory / 1024 / 1024 << " MB} |{Virtual Memory|Total: " << memoryInfo.totalVirtualMemory / 1024 / 1024 << " MB|Free: " << memoryInfo.freeVirtualMemory / 1024 / 1024 << " MB|Used: " << memoryInfo.usedVirtualMemory / 1024 / 1024 << " MB} |{Page File|Total: " << memoryInfo.totalPageFile / 1024 / 1024 << " MB|Free: " << memoryInfo.freePageFile / 1024 / 1024 << " MB|Used: " << memoryInfo.usedPageFile / 1024 / 1024 << " MB}\"];\n";
    dotFile << "}\n";
    dotFile.close();
}

void GenerateMemoryGraph(const MemoryInfo& memoryInfo, const std::string& dotFileName, const std::string& pngFileName) {
    CreateDotFile(memoryInfo, dotFileName);
    std::stringstream command;
    command << "dot -Tpng " << dotFileName << " -o " << pngFileName;
    system(command.str().c_str());
}

int main() {
    MemoryInfo memoryInfo = GetMemoryInfo();
    GenerateMemoryGraph(memoryInfo, "memory.dot", "memory.png");
    std::cout << "Memory graph generated successfully.\n";
    return 0;
}
