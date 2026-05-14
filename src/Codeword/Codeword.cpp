//
// Created by ziadf on 5/16/2025.
//
#include "../../include/Codeword/Codeword.h"

#include <algorithm>
#include <stdexcept>

Codeword::Codeword() : m(0), k(0), a(3) {}

void Codeword::SetField(int m_) {

    m = m_;
    a = GF2mAlpha(m);
}

void Codeword::SetSize(int k_) {
    k = k_;
}

void Codeword::SetcodewordVector(const vector<int>& data) {

        if (data.size() != k)
            throw std::invalid_argument("Message size must equal k.");
        mess = a.Setinfield(data);

}

void Codeword::SetBinaryVector(const vector<int>& data0b) {
    mess0b = data0b;
    FromBinary();
}

vector<int> Codeword::GetcodewordVector()  {
    return mess;
}

vector<int> Codeword::GetBinaryVector() {
    ToBinary();
    return mess0b;
}


void Codeword::FromBinary() {
    if (mess0b.size() != k * m)
        throw std::invalid_argument("Binary size must equal k * m.");
    mess.clear();
    for (int i = 0; i + m <= mess0b.size(); i += m) {
        int word = 0;
        for (int j = 0; j < m; ++j) {
            word = (word << 1) | mess0b[i + j];
        }
        mess.push_back(word);
    }
}

void Codeword::ToBinary() {
    mess0b.clear();
    for (int value : mess) {
        for (int i = m - 1; i >= 0; --i) {
            int bit = (value >> i) & 1;
            mess0b.push_back(bit);
        }
    }
}


