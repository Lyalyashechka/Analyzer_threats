#pragma once

#include <string>
#include <filesystem>

#include "AnalyzInformation.h"

struct I_Analyzer
{
    virtual void startAnalyzing(const std::string &pathName, const unsigned &countThread = 0) = 0;

    virtual AnalyzInformation getResultAnalyz() = 0;


};
