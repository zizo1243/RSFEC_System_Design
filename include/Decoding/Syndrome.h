//
// Created by ziadf on 5/16/2025.
//

#ifndef SYNDROME_H
#define SYNDROME_H
#include "../../include/Galios Field operations/GF2mAlpha.h"



class Syndrome {
private:
    int m;
    int n;
    int k;
    vector<int>s;
    vector<int>recivedcodeword;
    GF2mAlpha a;

public:
    Syndrome(vector<int>r,int m,int n,int k);
    vector<int> Getsyndrome();
    void Syndromecalculation();
    void Setsyndrome(vector<int>s1);
};



#endif //SYNDROME_H
