#include "../../include/Codeword/Generatorpolynomial.h"

Generatorpolynomial::Generatorpolynomial(const std::vector<int>& polynomial, int m,int n, int k)
    : gf(GF2mAlpha(m))
{
    int expectedsize = n - k + 1;
    if (polynomial.size() != expectedsize) {
        throw std::invalid_argument("Generator polynomial size must be n - k + 1");
    }

    // Check all coefficients are valid field elements (0 <= coeff < field size)
    int fieldsize = gf.Getfieldsize();
    for (int coeff : polynomial) {
        if (coeff < 0 || coeff >= fieldsize) {
            throw std::invalid_argument("Generator polynomial contains coefficients outside of field");
        }
    }

    // If all checks passed, assign
    generatorpolynomial = polynomial;
}

std::vector<int> Generatorpolynomial::GetGeneratorpolynomial() const {
    return generatorpolynomial;
}

