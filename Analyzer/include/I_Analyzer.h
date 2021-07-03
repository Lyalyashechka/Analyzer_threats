#pragma once

#include <string>
#include <filesystem>

struct AnalyzInformation
{
    unsigned countProcFiles;
    unsigned countUNIXSus;
    unsigned countMACSus; 
    unsigned countJSSus;
    unsigned countErrors;
};

struct I_Analyzer
{
    virtual void startAnalyzing(const std::string &pathName, const unsigned &countThread = 0){};

    virtual AnalyzInformation getResultAnalyz(){};
};
