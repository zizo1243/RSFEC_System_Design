//
// Created by ziadf on 5/17/2025.
//

#ifndef FORNEYALGORITHM_H
#define FORNEYALGORITHM_H
#include "../Galios Field operations/GF2mAlpha.h"
#include "Syndrome.h"
#include "KeyequationEEA.h"
class Forneyalgorithm {
private:
    int m;
    int n;
    int k;
    GF2mAlpha a;
    vector<int>receivedcodeword;
    vector<int>correctedcodeword;
    vector<int>errorlocations;
    vector<int>errorlocatorpolynomial;
    vector<int>errorevaluatorpolynomial;
void Correctingrecivedcodeword();
    void SetCorrectedcodeword(vector<int>correctedcodeword_);
public:
    Forneyalgorithm(vector<int>errorlocations,vector<int>errorlocatorpolynomial,vector<int>errorevaluatorpolynomial_,vector<int>receivedcodeword,int m,int n,int k);
    vector<int>GetCorrectedcodeword();


};



#endif //FORNEYALGORITHM_H
