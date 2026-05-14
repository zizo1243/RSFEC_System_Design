//
// Created by ziadf on 5/22/2025.
//

#ifndef RSFECDECODERINTERFACE_H
#define RSFECDECODERINTERFACE_H
#include"../../include/Channel Interface/ChannelInterfaceReceiver.h"
#include "../Codeword/Encodedmessage.h"
#include"../Codeword/Message.h"



class RSFECdecoderInterface {
private:
    int m;
    int n;
    int k;
    EncodedMessage receivedencodedmessage;
    vector<int>message;
    void Decode();
    void Setmessage(vector<int> message_);
public:
    RSFECdecoderInterface(int m,int n,int k,EncodedMessage receivedencodedmessage);
    vector<int>Getmessage();


};



#endif //RSFECDECODERINTERFACE_H
