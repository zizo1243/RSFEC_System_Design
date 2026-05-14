//
// Created by ziadf on 5/22/2025.
//
#include "RSencoder.h"

#ifndef RSENCODERINTERFACE_H
#define RSENCODERINTERFACE_H

class RSencoderInterface {
private:

    int m;
    int n;
    int k;
    vector<int> encodedmessage ;
    vector<int> message;
    Generatorpolynomial gp;
public:
    RSencoderInterface(int m,int n,int k,vector<int> messages_,Generatorpolynomial gp_ );

    EncodedMessage Getencodedmessage();



    void Encode();
};



#endif //RSENCODERINTERFACE_H
