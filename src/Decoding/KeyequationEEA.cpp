//
// Created by ziadf on 5/17/2025.
//

#include "../../include/Decoding/KeyequationEEA.h"
#include <algorithm>
#include <iostream>
KeyequationEEA::KeyequationEEA(vector<int> syndrome_, int m_, int n_, int k_):syndrome(syndrome_),m(m_),n(n_),k(k_),a(GF2mAlpha(m_)){
   // as all the polynomial fuctions works for vector assendengilly execpt susitute in equation
    SolvingKeyequationEEA();
}

void KeyequationEEA::SolvingKeyequationEEA() {
    int c = 0;//Non-zero syndrome check
    for (int i = 0;i < syndrome.size();i++) {
        if (syndrome[i] != 0) {
            c=c+1;
        }
    }

    if (c == 0) {
        vector<int>errorlocatorpolynomial(1,0);
        vector<int>errorevaluatorpolynomial(1,0);
        Seterrorlocatorpolynomial(errorlocatorpolynomial);
        Seterrorevaluatorpolynomial(errorevaluatorpolynomial);
    }
    else {

        int t2 = n - k;
        int t = t2 / 2;
        std::reverse(syndrome.begin(),syndrome.end());
        vector<int>r_1(t2 + 1, 0);
        r_1[t2] = 1;
        vector<int>r_0 = syndrome;
        while (r_0.back() == 0) {
            r_0.pop_back();
        }
        vector<int>B_1 = { 0 };
        vector<int>B_0 = { 1 };
        vector<int>v_1 = { 1 };
        vector<int>v_0 = { 0 };
        bool indexingfordegree = true;
        vector<int>q;
        vector<int>r_temp;
        vector<int>B_temp;
        vector<int>v_temp;
        while (indexingfordegree) {
            r_temp = a.Polydivide(r_1, r_0, q);
            vector<int>x = a.Polymul(q, B_0);
            B_temp = a.Polyadd(B_1, x);
            vector<int>y = a.Polymul(q, v_0);
            v_temp = a.Polyadd(v_1, y);

            if (r_temp.size() < t+1) {
                indexingfordegree = false;
            }
            else {
                r_1 = r_0;
                B_1 = B_0;
                v_1 = v_0;
                r_0 = r_temp;
                B_0 = B_temp;
                v_0 = v_temp;

            }
        }
        reverse(B_temp.begin(), B_temp.end());
        reverse(r_temp.begin(), r_temp.end());
        for (int i = 0;i < B_temp.size();i++) {
            B_temp[i] = a.Divide(B_temp[i], a.Subsituteinequation(B_temp, 0));
        }
        for (int i = 0;i < r_temp.size();i++) {
            r_temp[i] = a.Divide(r_temp[i], a.Subsituteinequation(B_temp, 0));
        }// TO NORMALIZE THE ERROR LOCATOR AND EVALUATOR POLYNOMIAL
        Seterrorlocatorpolynomial(B_temp);
        Seterrorevaluatorpolynomial(r_temp);

    }
}

void KeyequationEEA::Seterrorlocatorpolynomial(vector<int> errorlocatorpolynomial_) {
    errorlocatorpolynomial=errorlocatorpolynomial_;
}

void KeyequationEEA::Seterrorevaluatorpolynomial(vector<int> errorevaluatorpolynomial_) {
    errorevaluatorpolynomial=errorevaluatorpolynomial_;
}

vector<int> KeyequationEEA::Geterrorlocatorpolynomial() {
    return errorlocatorpolynomial;
}

vector<int> KeyequationEEA::Geterrorevaluatorpolynomial() {
    return errorevaluatorpolynomial;
}
