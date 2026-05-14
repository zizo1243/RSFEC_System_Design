//
// Created by ziadf on 5/22/2025.
//

#ifndef CHANNELINTERFACERECEIVER_H
#define CHANNELINTERFACERECEIVER_H
#include "iostream"
#include "ChannelInterfaceTransmitter.h"
class ChannelInterfaceReceiver {
private:
    int m;               // GF(2^m)
    int n;
    int k;
    std::string filename;
    EncodedMessage receivedencodedmessage;

    std::string ConvertToBitString(int word);         // Convert int to m-bit string
    int ConvertFromBitString(const std::string& str); // Convert m-bit string to int
public:
    ChannelInterfaceReceiver(int m,int n,int k);
    EncodedMessage Receive( std::string filename_);

};



#endif //CHANNELINTERFACERECEIVER_H
