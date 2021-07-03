#include <unistd.h>
#include <chrono>

#include "Analyzer.h"
#include "config.h"

void printTime_MinSecMs(const long long &ms);
void printAnalyzResult(const AnalyzInformation &res, const long long &ms);

int main(int argc, char *argv[])
{
    log_info("Start program in Debug mode");
    if (argc != 2)
    {
        std::cout << "Pass the path to the directory in the command line parameters\n";
        return 1;
    }
    if (!std::filesystem::is_directory(argv[1]))
    {
        std::cout << "This directory not found\n";
        return 1;    
    }
    std::string filePathName = argv[1];

    int countCoreSystem = sysconf(_SC_NPROCESSORS_ONLN);
    log_info("Count threads: %d", countCoreSystem);

    std::shared_ptr<I_Analyzer> analyzer(new Analyzer());

    auto start = std::chrono::high_resolution_clock::now();
    log_info("Start scaning");
    analyzer->startAnalyzing(filePathName, countCoreSystem);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long millisecond = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    AnalyzInformation res = analyzer->getResultAnalyz();
    printAnalyzResult(res, millisecond);
    
    log_info("End of program");
}

void printTime_MinSecMs(const long long &ms)
{
    int milSec = ms % 1000;
    int sec = ((ms - milSec) / 1000) % 60;
    int min = ((ms - milSec) / 1000) / 60;
    std::cout << min << ":" << sec << ":" << milSec << " (min:sec:ms)" << std::endl;
}

void printAnalyzResult(const AnalyzInformation &res, const long long &ms)
{
    std::cout << "====== Scan result ======" << std::endl
              << "Processed files: " << res.countProcFiles << std::endl
              << "JS detects: " << res.countJSSus << std::endl
              << "Unix detects: " << res.countUNIXSus << std::endl
              << "macOS detects:" << res.countMACSus << std::endl
              << "Errors: " << res.countErrors << std::endl
              << "Exection time: ";
    printTime_MinSecMs(ms);
    std::cout << "=========================" << std::endl;
}