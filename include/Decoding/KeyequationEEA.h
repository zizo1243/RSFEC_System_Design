//
// Created by ziadf on 5/17/2025.
//

#ifndef KEYEQUATIONEEA_H
#define KEYEQUATIONEEA_H
#include "Syndrome.h"
#include "../../include/Galios Field operations/GF2mAlpha.h"

class KeyequationEEA {
private:
    int m;
    int n;
    int k;
    //Syndrome syndrome;
    vector<int>syndrome;
    GF2mAlpha a;
    vector<int>errorlocatorpolynomial;
    vector<int>errorevaluatorpolynomial;
    void SolvingKeyequationEEA();
    void Seterrorlocatorpolynomial(vector<int>errorlocatorpolynomial);
    void Seterrorevaluatorpolynomial(vector<int> errorlocatorpolynomial);
public:
    KeyequationEEA(vector<int>syndrome,int m,int n,int k);
    vector<int>Geterrorlocatorpolynomial();
    vector<int>Geterrorevaluatorpolynomial();


};



#endif //KEYEQUATIONEEA_H
