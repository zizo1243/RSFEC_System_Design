//
// Created by ziadf on 5/16/2025.
//

#ifndef CODEWORD_H
#define CODEWORD_H

#include <vector>
#include "../Galios Field operations/GF2mAlpha.h"
using namespace std;

class Codeword {
protected:
    int m;
    int k;
    GF2mAlpha a;
    vector<int> mess;
    vector<int> mess0b;


public:
    Codeword();
    void SetField(int m_);
    void SetSize(int k_);
    void SetcodewordVector(const vector<int>& data);
    void SetBinaryVector(const vector<int>& data0b);
    vector<int> GetcodewordVector() ;
    vector<int> GetBinaryVector();
void Setvectorcodewords(Codeword codeword1_) ;


protected:
    void FromBinary();
    void ToBinary();


};

#endif
