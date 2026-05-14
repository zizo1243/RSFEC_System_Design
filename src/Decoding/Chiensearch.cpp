//
// Created by ziadf on 5/17/2025.
//

#include "../../include/Decoding/Chiensearch.h"

void Chiensearch::Seterrorlocations(vector<int> errorlocations_) {
    errorlocations = errorlocations_;
}

void Chiensearch::Chiensearchsolving() {
    std::reverse(errorlocatorpolynomial.begin(), errorlocatorpolynomial.end());
    vector<int>error_locations(n, 0);
    vector<string>error_locationsstr;
    if (errorlocatorpolynomial.size() < 2) {
        error_locationsstr={"zero error as zero error locator polynomial"};
        Seterrorlocations(error_locations);
        Seterrorlocationstring(error_locationsstr);

    }
    else{
        for (int l = 1;l <a.Getfieldsize();l++) {
            int j = a.Logalpha(l);
            int p = a.Inverse(l);
            int k = a.Subsituteinequation(errorlocatorpolynomial, p);
            if (k == 0) {
                error_locations[n-j-1] = 1;
                numberoferrors++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (error_locations[i] == 1) {
                error_locationsstr.push_back(  "symbol number " + std::to_string(i+1));
            }
        }
        Seterrorlocations(error_locations);
        Seterrorlocationstring(error_locationsstr);
    }
}
void Chiensearch::Seterrorlocationstring(vector<string> errorlocationstring_) {
    errorlocationstring = errorlocationstring_;
}

Chiensearch::Chiensearch(vector<int> errorlocatorpolynomial_, int m_, int n_):errorlocatorpolynomial(errorlocatorpolynomial_) ,m(m_),n(n_),a(GF2mAlpha(m)){
numberoferrors = 0;
    Chiensearchsolving();
}

vector<int> Chiensearch::Geterrorlocations() {
    return errorlocations;
}

vector<string> Chiensearch::Geterrorlocationstring() {
    return errorlocationstring;
}
int  Chiensearch::Getnumberoferrors() {
    return numberoferrors;
}
