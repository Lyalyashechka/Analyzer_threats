#pragma once

#include <vector>
#include <stdio.h>
#include <stdint.h>


struct MessageHeader
{
    int id;

    uint32_t sizeMessage = 0;
};


struct Message
{
    MessageHeader header;

    std::vector<uint8_t> body;

    template<typename dataType>
    friend Message& operator << (Message &msg, const dataType& data)
    {
        size_t currentSize = msg.body.size();

        msg.body.resize(currentSize + sizeof(dataType));

        memcpy(msg.body.data() + currentSize, &data, sizeof(dataType));

        msg.header.sizeMessage = msg.body.size();

        return msg;
    } 


    template<typename dataType>
    friend Message& operator >> (Message &msg, dataType& data)
    {
        size_t newSize = msg.body.size() - sizeof(dataType);

        memcpy(&data, msg.body.data() + newSize, sizeof(dataType));

        msg.body.resize(newSize);

        msg.header.sizeMessage = msg.body.size();

        return msg;
    }
};
