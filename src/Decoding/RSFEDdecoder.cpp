//
// Created by ziadf on 5/17/2025.
//

#include "../../include/Decoding/RSFEDdecoder.h"
#include"iostream"

RSFEDdecoder::RSFEDdecoder(EncodedMessage receivedencodedmessage_, int m_, int n_, int k_):receivedencodedmessage(receivedencodedmessage_),m(m_),n(n_),k(k_) ,a(GF2mAlpha(m)){
    if (receivedencodedmessage.GetcodewordVector().size()!=n) {
        throw std::invalid_argument("the received encoded message size must be same as entered n");
    }
    if (n<=k) {
        throw std::invalid_argument("n must be greater than k");
    }
    if (m<2 || m>10) {
        throw std::invalid_argument("invalid entered m");
    }
    Seterrorlocations();
    Decode();



}

void RSFEDdecoder::Decode() {
    vector<int>receivedcodeword=receivedencodedmessage.GetcodewordVector();
    vector<int>message(k,0);
    for (int i=0;i<k;i++) {
        message[i]=receivedcodeword[i];
    }
    decodedmessage.SetField(m);
    decodedmessage.SetSize(k);
    decodedmessage.SetcodewordVector(message);

}

void RSFEDdecoder::Seterrorlocations() {
    vector<int> receivedcodewordvector = receivedencodedmessage.GetcodewordVector();
    Syndrome synd(receivedcodewordvector, m, n, k);
    vector<int> s = synd.Getsyndrome();
    int zerosyndromeindexing = 0;
    int t = (n - k) / 2;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != 0)
            zerosyndromeindexing++;
    }

    if (zerosyndromeindexing == 0) {
        errorlocations = {" no symbols"};
    }
    else {
        try {

            KeyequationEEA key(synd.Getsyndrome(),m, n, k);
            vector<int>errorlocatorpoly=key.Geterrorlocatorpolynomial();
            Chiensearch ch(errorlocatorpoly,m,n);
            if (errorlocatorpoly.size()-1!=ch.Getnumberoferrors()) {
                errorlocations={"number of symbols in error is greater than 15"};
            }
            else {

                errorlocations=ch.Geterrorlocationstring();
            }
        }catch(exception &e) {

            errorlocations={"number of symbols in error is greater than 15"};

        }


    }
}


vector<string> RSFEDdecoder::Geterrorlocations() {
    return errorlocations;
}

Message RSFEDdecoder::Getdecodedmessage() {
    return decodedmessage;
}
