#pragma once

#include <vector>
#include <stdio.h>
#include <stdint.h>

#include "AnalyzInformation.h"

#define typeAnalyzInfo 0
#define typeString     1

struct MessageHeader
{
    int type;

    size_t sizeStringData = 0;
};


struct Message
{
    MessageHeader header;

    AnalyzInformation analyzData;

    std::string stringData;

    void setStringData(std::string string)
    {
        stringData = string;

        header.sizeStringData = stringData.length();
    }
};
