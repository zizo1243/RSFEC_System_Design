

#ifndef GF2MALPHA_H
#define GF2MALPHA_H
#include <vector>
#include <stdexcept>
using namespace std;

class GF2mAlpha {
private:
    int m;
    int fieldsize;
    int primitivepoly;
    vector<int> logtable;
    vector<int> antilogtable;


public:
    int Getprimitivepolynomial(int m);
    void Inittables();

    GF2mAlpha(int m_);

    int Logalpha(int value) const;
    int Alphapower(int i) const;
    int Multiply(int a, int b) ;
    int Divide(int a, int b) const;
    int Add(int a, int b);
    int Inverse(int a);
    int Getfieldsize();
    int Modolus(int val);
    int Power(int x, int n);
    int Subsituteinequation(vector<int>equation, int x);
    vector<int> Polyadd(const vector<int>& a, const vector<int>& b);
    vector<int> Polymul(const vector<int>& a, const vector<int>& b);
    vector<int> Setinfield(vector<int> x);
    vector<int> Diffrentiator(const vector<int> FX);
    vector<int>Polydivide(vector<int>& numerator, vector<int>& denominator, vector<int>& quotient_out);
};

#endif // GF2MALPHA_H
