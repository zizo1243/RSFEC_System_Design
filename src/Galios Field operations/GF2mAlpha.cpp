//
// Created by ziadf on 5/15/2025.
//

#include "../../include/Galios Field operations/GF2mAlpha.h"

int GF2mAlpha::Getprimitivepolynomial(int m) {
    switch (m) {
    case 2:  return 0b111;
    case 3:  return 0b1011;
    case 4:  return 0b10011;
    case 5:  return 0b100101;
    case 6:  return 0b1000011;
    case 7:  return 0b10000011;
    case 8:  return 0b100011011;
    case 9:  return 0b1000010001;
    case 10: return 0b10000001001;
    default:
        throw std::invalid_argument("Primitive polynomial for this m is not defined.");
    }
}

GF2mAlpha::GF2mAlpha(int m_) {
    m = m_;
    primitivepoly = Getprimitivepolynomial(m_);
    fieldsize = 1 << m;
    logtable.resize(fieldsize, -1);
    antilogtable.resize(fieldsize * 2, 0);
    Inittables();
}

void GF2mAlpha::Inittables() {
    int value = 1;
    for (int i = 0; i < fieldsize - 1; ++i) {
        antilogtable[i] = value;
        logtable[value] = i;
        value <<= 1;
        if (value & fieldsize) {
            value ^= primitivepoly;
        }
    }
    for (int i = fieldsize - 1; i < 2 * (fieldsize - 1); ++i) {
        antilogtable[i] = antilogtable[i - (fieldsize - 1)];
    }
}

int GF2mAlpha::Logalpha(int value) const {
    if (value == 0)
        throw std::invalid_argument("undefined symbol.");
    return logtable[value];
}

int GF2mAlpha::Alphapower(int i) const {
    return antilogtable[i % (fieldsize - 1)];
}

int GF2mAlpha::Multiply(int a, int b)  {
    if (a == 0 || b == 0) return 0;
    int log_a = logtable[a];
    int log_b = logtable[b];
    return antilogtable[(log_a + log_b) % (fieldsize - 1)];
}

int GF2mAlpha::Divide(int a, int b) const {
    if (b == 0) throw std::invalid_argument("divisor cannot equal 0.");
    if (a == 0) return 0;
    int log_a = logtable[a];
    int log_b = logtable[b];
    return antilogtable[(log_a - log_b + (fieldsize - 1)) % (fieldsize - 1)];
}

int GF2mAlpha::Add(int a, int b) {
    return Modolus(a ^ b);
}

int GF2mAlpha::Inverse(int a) {
    if (a == 0) throw std::invalid_argument("Division by zero is not allowed.");
    for (int i = 1; i < fieldsize - 1; i++) {
        if (Multiply(a, i) == 1) return i;
    }
    return fieldsize-1;
}

int GF2mAlpha::Getfieldsize() {
    return fieldsize;
}

int GF2mAlpha::Modolus(int val) {
    if (val >= fieldsize) {
        return Modolus(val - fieldsize);
    } else {
        return val;
    }
}

vector<int> GF2mAlpha::Diffrentiator(const vector<int> FX) {
    vector<int>fx(FX.begin() + 1, FX.end());
    for (int i = 0; i < fx.size(); i++) {
        fx[i] =Multiply(fx[i], i + 1);
    }
    return fx;
}

vector<int> GF2mAlpha::Polydivide(vector<int> &numerator, vector<int> &denominator, vector<int> &quotient_out) {
    std::vector<int> num = numerator;

    std::vector<int> quotient(num.size() - denominator.size() + 1, 0);
    while (num.size() >= denominator.size()) {
        int l = num.size() - denominator.size();  // shift amount
        double scale = Divide(num.back(), denominator.back());  // leading term division
        quotient[l] = scale;

        // Subtract scaled divisor * x^l from num
        for (int i = 0; i < denominator.size(); ++i) {
            num[l + i] = Add(num[l + i], Multiply(scale, denominator[i]));
        }

        num.pop_back();
    }
    while (num.back() == 0) {
        num.pop_back();
    }

    quotient_out = quotient;
    return num;  // remainder
}
vector<int>shift_poly(vector<int>& x) {
    vector<int>result = x;
    result.push_back(0);
    return result;
}

int GF2mAlpha::Power(int x, int n) {
    int b = 1;
    for (int i = 0; i < n; ++i) {
        b = Multiply(b, x);
    }
    return Modolus(b);
}

int GF2mAlpha::Subsituteinequation(vector<int> equation, int x) {
    int result = equation[0];  // Start with highest-degree coefficient
    for (int i = 1; i <equation.size(); ++i) {
        result = Multiply(result, x);
        result = Add(result, equation[i]);
    }
    return result;
}


vector<int> GF2mAlpha::Polyadd(const vector<int>& a, const vector<int>& b) {
    vector<int> result;
    int m = min(a.size(), b.size());
    int n = max(a.size(), b.size());
    for (int i = 0; i < m; i++) {
        result.push_back(Add(a[i], b[i]));
    }
    if (a.size() > b.size()) {
        for (int i = m; i < n; i++) result.push_back(a[i]);
    } else {
        for (int i = m; i < n; i++) result.push_back(b[i]);
    }
    return result;
}

vector<int> GF2mAlpha::Polymul(const vector<int>& a, const vector<int>& b) {
    vector<int> result(a.size() + b.size() - 1, 0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            result[i + j] = Add(result[i + j], Multiply(a[i], b[j]));
        }
    }
    return result;
}

vector<int> GF2mAlpha::Setinfield(vector<int> x) {
    vector<int> y(x.size(), 0);
    for (int i = 0; i < x.size(); i++) {
        y[i] = Modolus(x[i]);
    }
    return y;
}
