#include <Windows.h>
#include <iostream>

int main()
{
    MEMORYSTATUSEX memStat;
    memStat.dwLength = sizeof(memStat);
    GlobalMemoryStatusEx(&memStat);

    std::cout << "Total physical memory: " << memStat.ullTotalPhys / 1024 / 1024 << " MB" << std::endl;
    std::cout << "Available physical memory: " << memStat.ullAvailPhys / 1024 / 1024 << " MB" << std::endl;
    std::cout << "Total virtual memory: " << memStat.ullTotalVirtual / 1024 / 1024 << " MB" << std::endl;
    std::cout << "Available virtual memory: " << memStat.ullAvailVirtual / 1024 / 1024 << " MB" << std::endl;
    std::cout << "Total page file: " << memStat.ullTotalPageFile / 1024 / 1024 << " MB" << std::endl;
    std::cout << "Available page file: " << memStat.ullAvailPageFile / 1024 / 1024 << " MB" << std::endl;

    return 0;
}
