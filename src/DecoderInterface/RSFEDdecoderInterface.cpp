//
// Created by ziadf on 5/22/2025.
//

#include "../../include/DecoderInterface/RSFEDdecoderInterface.h"
void RSFEDdecoderInterface::Decode() {
    vector<int>message1;
    vector<int>received1=receivedencodedmessage.GetcodewordVector();
vector<string>errorloctions1;
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
        RSFEDdecoder rsdec(receivedencodedmessageone,m,n,k);
        messageone=rsdec.Getdecodedmessage();
        vector<int>m1=messageone.GetcodewordVector();

        for (int j=0;j<m1.size();j++) {
            message1.push_back(m1[j]);
        }
        vector<string>el1=rsdec.Geterrorlocations();
        for (int j=0;j<el1.size();j++) {
            string e=el1[j]+" in codeword number "+std::to_string(i+1)+" in error ";
            errorloctions1.push_back(e);
        }

    }

    Setmessage(message1);
    Seterrorlocations(errorloctions1);
}

RSFEDdecoderInterface::RSFEDdecoderInterface(int m_,int n_,int k_,EncodedMessage receivedencodedmessage_):receivedencodedmessage(receivedencodedmessage_){
    k=k_;
    m=m_;
    n=n_;
    Decode();
}

vector<int> RSFEDdecoderInterface::Getmessage() {
    return message;
}

vector<string> RSFEDdecoderInterface::Geterrorlocations() {
    return errorlocations;
    delete &errorlocations;
}

void RSFEDdecoderInterface::Setmessage(vector<int>message_) {
    message=message_;
}

void RSFEDdecoderInterface::Seterrorlocations(vector<string> errorlocations_){
    errorlocations = errorlocations_;
}
