//
// Created by ziadf on 5/16/2025.
//

#ifndef RSENCODER_H
#define RSENCODER_H

#include <vector>
#include "../Codeword/Message.h"
#include "../Codeword/Encodedmessage.h"
#include "../Codeword/Generatorpolynomial.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"

class Rsencoder {
private:
    int m;
    int n;
    int k;
    GF2mAlpha a;
    Message message;
    Generatorpolynomial g;
    EncodedMessage encodedmessage;
    std::vector<int> mess;
    std::vector<int> parity;
    std::vector<int> codeword;
    std::vector<int> genpoly;
    void Setparity(vector<int> parity);
    void Encode();
public:
    Rsencoder(int m_, int n_, int k_, const Message& msg, const Generatorpolynomial& gp);
    vector<int>Getparity();
    EncodedMessage GetEncodedMessage();
};

#endif
