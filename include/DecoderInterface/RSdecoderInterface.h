//
// Created by ziadf on 5/22/2025.
//

#ifndef RSDECODERINTERFACE_H
#define RSDECODERINTERFACE_H
#include"../../include/Channel Interface/ChannelInterfaceReceiver.h"
#include "../Codeword/Encodedmessage.h"


class RSdecoderInterface {

private:
    int m;
    int n;
    int k;
    EncodedMessage receivedencodedmessage;
    vector<int>message;
    void Decode();
    void Setmessage(vector<int> message_);
public:
    RSdecoderInterface(int m,int n,int k,EncodedMessage receivedencodedmessage);
vector<int>Getmessage();


};




#endif //RSDECODERINTERFACE_H
