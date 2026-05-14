//
// Created by ziadf on 5/16/2025.
//
#include"iostream"
#include "../../include/Decoding/RSFECdecoder.h"


void RSFECdecoder::Decode() {
    int t2 = n - k;
    int t = t2 / 2;

    vector<int> recivedcodewordvector = receivedencodedmessage.GetcodewordVector();
    vector<int> correctedrecivedcodeword(n, 0);

    // Step 1: Compute syndrome
    Syndrome s(recivedcodewordvector, m, n, k);
    vector<int> syndromevector = s.Getsyndrome();

    // Step 2: Check if all syndromes are zero (no error)
    bool Zeroerrorindexing = std::all_of(syndromevector.begin(), syndromevector.end(), [](int x) { return x == 0; });

    if (Zeroerrorindexing) {
        // No errors detected, return received codeword as-is
        correctedrecivedcodeword = recivedcodewordvector;
    }
    else {
        try {

            KeyequationEEA key(syndromevector,m, n, k);
            vector<int>errorlocatorpoly=key.Geterrorlocatorpolynomial();
            Chiensearch ch(errorlocatorpoly,m,n);
            if (errorlocatorpoly.size()-1!=ch.Getnumberoferrors()) {
                correctedrecivedcodeword=recivedcodewordvector;
            }
            else {
                Forneyalgorithm fa(ch.Geterrorlocations(),key.Geterrorlocatorpolynomial(),key.Geterrorevaluatorpolynomial(),recivedcodewordvector,m,n,k);
                correctedrecivedcodeword=fa.GetCorrectedcodeword();
            }
        }catch(exception &e) {

            correctedrecivedcodeword=recivedcodewordvector;
            return;
        }


    }

    // Step 6: Extract message portion (first k symbols)
    vector<int> correctedmessage(k, 0);
    for (int i = 0; i < k; i++) {
        correctedmessage[i] = correctedrecivedcodeword[i];
    }

    // Step 7: Set decoded message
    decodedmessage.SetField(m);
    decodedmessage.SetSize(k);
    decodedmessage.SetcodewordVector(correctedmessage);

}

RSFECdecoder::RSFECdecoder(EncodedMessage receivedencodedmessage, int m, int n, int k): receivedencodedmessage(receivedencodedmessage),m(m),n(n),k(k),a(GF2mAlpha(m)){
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


Message RSFECdecoder::Getdecodedmessage() {

    return decodedmessage;
}
