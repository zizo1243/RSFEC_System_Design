//
// Created by ziadf on 5/16/2025.
//

#ifndef RSFECDECODER_H
#define RSFECDECODER_H
#include <vector>
#include "../Codeword/Message.h"
#include "../Codeword//Encodedmessage.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"
#include "Syndrome.h"
#include "KeyequationEEA.h"
#include "Chiensearch.h"
#include "Forneyalgorithm.h"

class RSFECdecoder {
private :
    int n;
    int m;
    int k;
    GF2mAlpha a;
    Message decodedmessage;
    EncodedMessage receivedencodedmessage;
    void Decode();
public:
    RSFECdecoder(EncodedMessage receivedencodedmessage,int m,int n,int k);
    Message Getdecodedmessage();
};




#endif //RSDECODER_H
