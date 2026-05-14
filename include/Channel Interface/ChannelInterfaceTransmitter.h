//
// Created by ziadf on 5/18/2025.
//

#ifndef CHANNELINTERFACE_H
#define CHANNELINTERFACE_H


#include <string>
#include <vector>

#include "../Codeword/Encodedmessage.h"

class ChannelInterfaceTransmitter {
private:
    int m;               // GF(2^m)
    int n;
    int k;
    std::string filename;
    EncodedMessage recivedencodedmessage;

    std::string ConvertToBitString(int word);         // Convert int to m-bit string
    int ConvertFromBitString(const std::string& str); // Convert m-bit string to int

public:
    ChannelInterfaceTransmitter(int m, int n,int k);  // Constructor with field parameters

    void Transmit(EncodedMessage encodedmessages,  std::string filename_);
};

#endif // CHANNELINTERFACE_H
