//
// Created by ziadf on 5/17/2025.
//

#ifndef CHIENSEARCH_H
#define CHIENSEARCH_H
#include "../Galios Field operations/GF2mAlpha.h"
#include"algorithm"




class Chiensearch {
private:
    int m;
    int n;
    GF2mAlpha a;
    vector<int>errorlocations;
    vector<int>errorlocatorpolynomial;
    vector<string>errorlocationstring;
    void Seterrorlocations(vector<int>errorlocations_);
    void Chiensearchsolving();
    void Seterrorlocationstring(vector<string>errorlocationstring_);
    int numberoferrors;
public:
    Chiensearch(vector<int>errorlocatorpolynomial_,int m_,int n_);
    vector<int> Geterrorlocations();
    vector<string>Geterrorlocationstring();
    int Getnumberoferrors();

};



#endif //CHIENSEARCH_H
