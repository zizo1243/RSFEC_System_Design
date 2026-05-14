//
// Created by ziadf on 5/17/2025.
//
#ifndef RSFEDDECODER_H
#define RSFEDDECODER_H
#include <vector>
#include "../Codeword/Message.h"
#include "../Codeword/Encodedmessage.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"
#include "Syndrome.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"
#include "Syndrome.h"
#include "KeyequationEEA.h"
#include "Chiensearch.h"

class RSFEDdecoder {
private:
    int m;
    int n;
    int k;
    GF2mAlpha a;
    EncodedMessage receivedencodedmessage;
    Message decodedmessage;
    vector<string>errorlocations;
    void Decode();
    void Seterrorlocations();
public:
    RSFEDdecoder(EncodedMessage receivedencodedmessage_, int m_,int n_,int k_);

    vector<string>Geterrorlocations();
    Message Getdecodedmessage();



};




#endif //RSFEDDECODER_H
