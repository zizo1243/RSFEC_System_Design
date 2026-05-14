//
// Created by ziadf on 5/16/2025.
//

#include "../../include/Decoding/Syndrome.h"
#include"iostream"
Syndrome::Syndrome(vector<int>r,int m,int n,int k_):m(m),n(n),k(k_),recivedcodeword(r),a(GF2mAlpha(m)) {
    //k=k_;
    Syndromecalculation();
}
void Syndrome::Syndromecalculation() {
    if (recivedcodeword.size() != n) {
        throw invalid_argument("recived code word size must be equal to n.");
    }
    if (n < k) {
        throw invalid_argument("n must be smaller than k");
    }
    // reverse(recived_code_word.begin(), recived_code_word.end());
    int t2 = n-k;
    vector<int>syndrome(t2,0);
    for (int i = 0;i <(t2);i++) {
        syndrome[i] = a.Subsituteinequation(recivedcodeword, a.Alphapower(i));
    }
    Setsyndrome(syndrome);

}
void Syndrome::Setsyndrome(vector<int>s1) {
    s=s1;

}
vector<int> Syndrome::Getsyndrome() {
    return s;

}

