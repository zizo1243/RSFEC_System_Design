//
// Created by ziadf on 5/17/2025.
//

#include "../../include/Decoding/RSdecoder.h"
#include"iostream"

void RSdecoder::Decode() {

    vector<int>receivedcodeword=receivedencodedmessage.GetcodewordVector();
    vector<int>message(k,0);
    for (int i=0;i<k;i++) {
        message[i]=receivedcodeword[i];
    }
    decodedmessage.SetField(m);
    decodedmessage.SetSize(k);
    decodedmessage.SetcodewordVector(message);
}

RSdecoder::RSdecoder(EncodedMessage receivedencodedmessage_, int m_, int n_, int k_):receivedencodedmessage(receivedencodedmessage_) ,m(m_),n(n_),k(k_){
    if (receivedencodedmessage.GetcodewordVector().size()!=n) {
        throw std::invalid_argument("the received encoded message size must be same as entered n");
    }
    if (n<=k) {
        throw std::invalid_argument("n must be greater than k");
    }
    if (m<2 || m>10) {
        throw std::invalid_argument("invalid entered m");
    }
    Decode();
}

Message RSdecoder::Getdecodedmessage() {
    return decodedmessage;
}
