#include <unistd.h>
#include <chrono>

#include "Analyzer.h"
//TODO: логи
//принт по заданию
//интерфейс


#ifndef NDEBUG
    #define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", \
                            __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define log_info(M, ...)
#endif


int main(int argc, char *argv[])
{
    // if (argc != 2) {
    //     std::cout << "Введите название директории\n";
    // }
    // std::string filePathName = argv[1];
    
    int countCoreSystem = sysconf(_SC_NPROCESSORS_ONLN);

    std::string filePathName = "/home/lyalyashechka/kasper/SearchThreats/testDirs";
    
    Analyzer analyzer;
    
    auto start = std::chrono::high_resolution_clock::now();
    analyzer.startAnalyzing(filePathName, countCoreSystem);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    
    std::cout<< millisecond;   
    log_info("End of program");
}