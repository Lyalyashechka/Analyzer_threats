#pragma once

#include <string>
#include <mutex>
#include <atomic>
#include <filesystem>
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include "searchingString.h"

class Analyzer
{
public:
    void startAnalyzing(const std::string &pathName, const unsigned &countThread = 0);

    void analyzingOneFile(const std::filesystem::path &fileName);

    void printByTask();

private:
    void analyzingOneThread();

    void analyzingMultithread(const unsigned &countThread);

    std::filesystem::path getNextFileForAnalyzing();

    void processingJSFile(std::ifstream &file);

    void processingANYFileOtherJS(std::ifstream &file);

    std::mutex mtx;
    std::atomic<unsigned> countProcFiles{0};
    std::atomic<unsigned> countUNIXSus{0};
    std::atomic<unsigned> countMACSus{0};
    std::atomic<unsigned> countJSSus{0};
    std::atomic<unsigned> countErrors{0};

    std::filesystem::directory_iterator it_fspath;
    std::filesystem::directory_iterator it_end;
};