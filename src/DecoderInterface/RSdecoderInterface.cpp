//
// Created by ziadf on 5/22/2025.
//

#include "../../include/DecoderInterface/RSdecoderInterface.h"

#include "../../include/Decoding/RSdecoder.h"

void RSdecoderInterface::Decode() {
    vector<int>message1;
    vector<int>received1=receivedencodedmessage.GetcodewordVector();

    if (received1.size()%n!=0) {
        std::__throw_invalid_argument(" received codeword size must be an multiple of n");
    }
    int numberofencodedmessage;
    numberofencodedmessage = received1.size()/n;
    for (int i=0;i<numberofencodedmessage;i++){
        vector<int>r1(received1.begin()+i*n,received1.begin()+i*n+n);
        EncodedMessage receivedencodedmessageone;
        receivedencodedmessageone.SetField(m);
        receivedencodedmessageone.SetSize(n);
        receivedencodedmessageone.SetcodewordVector(r1);
        Message messageone;
        RSdecoder rsdec(receivedencodedmessageone,m,n,k);
        messageone=rsdec.Getdecodedmessage();
        vector<int>m1=messageone.GetcodewordVector();

        for (int j=0;j<m1.size();j++) {
            message1.push_back(m1[j]);
        }

    }

    Setmessage(message1);
}

RSdecoderInterface::RSdecoderInterface(int m_,int n_,int k_,EncodedMessage receivedencodedmessage_):receivedencodedmessage(receivedencodedmessage_){
  k=k_;
  m=m_;
  n=n_;
    Decode();
}

vector<int> RSdecoderInterface::Getmessage() {
    return message;
}
void RSdecoderInterface::Setmessage(vector<int>message_) {
    message=message_;

}
