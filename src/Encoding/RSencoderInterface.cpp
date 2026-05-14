//
// Created by ziadf on 5/22/2025.
//

#include "../../include/Encoding/RSencoderInterface.h"
#include"iostream"



void RSencoderInterface::Encode() {
    vector<int>encodedmessage1;
    if (message.size()%k!=0) {
        std::__throw_invalid_argument(" message size must be an multiple of k");
    }
    int numberofencodedmessage=message.size()/k;
    for (int i=0;i<numberofencodedmessage;i++){
        vector<int>m1(message.begin()+i*k,message.begin()+i*k+k);
        Message messageone;
        messageone.SetField(m);
        messageone.SetSize(k);
        messageone.SetcodewordVector(m1);
        EncodedMessage encodedmessageone;
        Rsencoder rs(m,n,k,messageone,gp);
encodedmessageone=rs.GetEncodedMessage();
        vector<int>em1=encodedmessageone.GetcodewordVector();
        for (int j=0;j<em1.size();j++) {
            encodedmessage1.push_back(em1[j]);
        }
    }
    encodedmessage=encodedmessage1;

}
RSencoderInterface::RSencoderInterface( int m_, int n_, int k_,vector<int> message_,Generatorpolynomial gp_): gp(gp_) {
message = message_;
    m=m_;
    n=n_;
    k=k_;
    Encode();
}
EncodedMessage RSencoderInterface::Getencodedmessage(){
    EncodedMessage en;
    en.SetField(m);
    en.SetSize(encodedmessage.size());
    en.SetcodewordVector(encodedmessage);
    return en;
}

