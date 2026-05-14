#include "../../include/Encoding/RSencoder.h"
#include"iostream";

Rsencoder::Rsencoder(int m_, int n_, int k_, const Message& msg, const Generatorpolynomial& gp)
    : m(m_), n(n_), k(k_), message(msg), g(gp), a(GF2mAlpha(m))
{
    mess = message.GetcodewordVector();
    genpoly = g.GetGeneratorpolynomial();
    Encode();
}

void Rsencoder::Encode() {
    vector<int>codeword1(n, 0);
    if (mess.size() != k) {
        throw invalid_argument("Message length must be equal to k.");
    }
    if (n < k) {
        throw invalid_argument("n must be smaller than k");
    }
    // Initialize parity vector with zeros
    vector<int> parity(n - k, 0);
    // Update parity vector
    for (int j = 0; j < k; ++j) {
        // Extract subset of parity (parity[2:2*t])
        vector<int> parity_subset(parity.begin() + 1, parity.end());
        // Append a zero to the subset
        parity_subset.push_back(0);
        // Compute (message[j] + parity[0]) * generator_polynomial1
        int coeff = a.Multiply(a.Add(mess[j], parity[0]), genpoly[0]);
        vector<int>gen_poly1(genpoly.begin() + 1, genpoly.end());
        vector<int> term(gen_poly1.size(), 0);
        for (size_t i = 0; i < gen_poly1.size(); ++i) {
            term[i] = a.Multiply(gen_poly1[i], coeff);
        }

        // Update parity
        for (size_t i = 0; i < parity_subset.size(); ++i) {
            parity[i] = a.Add(parity_subset[i], term[i]);
        }
    }
    // Construct the encoded message
    for (int i = 0;i < k;i++) {
        codeword1[i] = mess[i];
    }
    for (int i = 0;i < n - k;++i) {
        codeword1[i + k] = parity[i];
    }
    codeword=codeword1;
    Setparity(parity);
}

void Rsencoder::Setparity(vector<int> parity1) {
    parity =parity1;
}

vector<int> Rsencoder::Getparity(){
    return parity;
}


EncodedMessage Rsencoder::GetEncodedMessage() {
    encodedmessage.SetField(m);
    encodedmessage.SetSize(n);
    encodedmessage.SetcodewordVector(codeword);
    return encodedmessage;
}
