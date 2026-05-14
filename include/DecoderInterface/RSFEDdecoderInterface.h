//
// Created by ziadf on 5/22/2025.
//

#ifndef RSFEDDECODERINTERFACE_H
#define RSFEDDECODERINTERFACE_H

#include "../Codeword/Encodedmessage.h"
#include "../../include/Channel Interface/ChannelInterfaceReceiver.h"
#include "../Codeword/Message.h"
#include "../Decoding/RSFEDdecoder.h"
class RSFEDdecoderInterface {
private:
    int m;
    int n;
    int k;
    EncodedMessage receivedencodedmessage;
    vector<int>message;

    vector<string>errorlocations;
    void Decode();
    void Setmessage(vector<int> message_);
    void Seterrorlocations(vector<string> errorlocations_);
public:
    RSFEDdecoderInterface(int m_,int n_,int k_,EncodedMessage receivedencodedmessage);
    vector<int>Getmessage();
    vector<string>Geterrorlocations();



};



#endif //RSFEDDECODERINTERFACE_H
