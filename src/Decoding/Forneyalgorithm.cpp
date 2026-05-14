//
// Created by ziadf on 5/17/2025.
//

#include "../../include/Decoding/Forneyalgorithm.h"

#include <algorithm>
#include <ranges>

#include"iostream"
/// This Algorithm donot use the Coorect Forney ALgorithm mentioned in all papers this is another algorithm usese by flipping each symbol till reaching correct code word
/// but it can be integrated to suit the correct forney algorithm, I used another algorithm because forney algorithm doexnot works
void Forneyalgorithm::Correctingrecivedcodeword() {
    // Precompute the original syndrome and key equation
    correctedcodeword=receivedcodeword;
    Syndrome original_syndrome(receivedcodeword, m, n, k);
    vector<int> syndrome = original_syndrome.Getsyndrome();
    KeyequationEEA original_keyeq(syndrome, m, n, k);
    int original_lambda_degree = original_keyeq.Geterrorlocatorpolynomial().size() - 1;

    // Cache field size for efficiency
     int fieldsize = a.Getfieldsize();

    for (int i = 0; i < n; ++i) {
     if (errorlocations[i] == 1) {
        int best_candidate = correctedcodeword[i];
      int min_lambda_degree = original_lambda_degree;

    // Save a copy to avoid modifying original vector repeatedly
    vector<int> testword1 = correctedcodeword;
    vector<int> testword2 = correctedcodeword;
    int o=fieldsize;
    for (int j = 0; j < fieldsize/2; ++j) {
        if (j == correctedcodeword[i]) continue; // Skip current value
        testword1[i] = j;
        testword2[i] = o;

   // Compute syndrome and lambda for the test codeword
       Syndrome test_syndrome1(testword1, m, n, k);
    Syndrome test_syndrome2(testword2, m, n, k);
      KeyequationEEA test_keyeq1(test_syndrome1.Getsyndrome(), m, n, k);
       KeyequationEEA test_keyeq2(test_syndrome2.Getsyndrome(), m, n, k);
       int test_degree1 = test_keyeq1.Geterrorlocatorpolynomial().size() - 1;
       int test_degree2 = test_keyeq2.Geterrorlocatorpolynomial().size() - 1;

    // Accept the symbol if degree decreases
     if (test_degree1 < min_lambda_degree) {
          min_lambda_degree = test_degree1;
          best_candidate = j;
          if (test_degree1 == 0) break; // Optimization: minimal possible
       }
       if (test_degree2 < min_lambda_degree) {
        min_lambda_degree = test_degree2;
         best_candidate = o;
         if (test_degree2 == 0) break; // Optimization: minimal possible
      }
        o--;
     }

     correctedcodeword[i] = best_candidate;
    }
     }

    SetCorrectedcodeword(correctedcodeword);

}

void Forneyalgorithm::SetCorrectedcodeword(vector<int> correctedcodeword_) {
    correctedcodeword = correctedcodeword_;
}

Forneyalgorithm::Forneyalgorithm(vector<int> errorlocations_, vector<int> errorlocatorpolynomial_,vector<int>errorevaluatorpolynomial_,vector<int>receivedcodeword_, int m_, int n_, int k_):errorlocations(errorlocations_),errorlocatorpolynomial(errorlocatorpolynomial_),errorevaluatorpolynomial(errorevaluatorpolynomial_),receivedcodeword(receivedcodeword_),m(m_),n(n_),k(k_),a(GF2mAlpha(m_)) {
    Correctingrecivedcodeword();
}

vector<int> Forneyalgorithm::GetCorrectedcodeword() {
    return correctedcodeword;
}


