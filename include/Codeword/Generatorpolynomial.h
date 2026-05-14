#ifndef GENERATORPOLYNOMIAL_H
#define GENERATORPOLYNOMIAL_H

#include <vector>
#include <stdexcept>
#include "../../include/Galios Field operations/GF2mAlpha.h"

class Generatorpolynomial {
private:
    std::vector<int> generatorpolynomial;
    int m;
    GF2mAlpha gf;

public:
    // Constructor takes the generator polynomial vector, n, k and GF object
    Generatorpolynomial(const std::vector<int>& polynomial, int m, int n, int k);

    // Getter for the polynomial vector
    std::vector<int> GetGeneratorpolynomial() const;


};

#endif
