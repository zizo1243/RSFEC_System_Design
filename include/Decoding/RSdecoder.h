//
// Created by ziadf on 5/17/2025.
//

#ifndef RSDECODER_H
#define RSDECODER_H
#include "../Codeword/Message.h"
#include "../Codeword/Encodedmessage.h"
#include <vector>
#include "../Codeword/Message.h"
#include "../Codeword/Encodedmessage.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"
class RSdecoder {
private:
    int m;
    int n;
    int k;
    EncodedMessage receivedencodedmessage;
    Message decodedmessage;
    void Decode();
public:
    RSdecoder(EncodedMessage recivedencodedmessage,int m,int n,int k);
    Message Getdecodedmessage();


};



#endif //RSDECODER_H
