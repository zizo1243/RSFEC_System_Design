//
// Created by ziadf on 5/18/2025.
//

#include "../../include/Channel Interface/ChannelInterfaceTransmitter.h"
#include <fstream>
#include"bitset"
#include<iostream>
#include <fstream>
#include <bitset>
#include <iostream>
#include <stdexcept>

#include "../../include/Channel Interface/ChannelInterfaceTransmitter.h"
#include <fstream>
#include"bitset"
#include<iostream>
#include <sstream>

ChannelInterfaceTransmitter::ChannelInterfaceTransmitter( int m_, int n_,int k_)
    :  m(m_), n(n_),k(k_) {

}
std::string ChannelInterfaceTransmitter::ConvertToBitString(int word) {
    if (word >= (1 << m)) {
        throw std::overflow_error("Word exceeds the size of GF(2^m).");
    }
    std::bitset<32> bits(word); // Bitset of 32 bits (just in case word is big)
    return bits.to_string().substr(32 - m); // Extract only the last m bits
}
int ChannelInterfaceTransmitter::ConvertFromBitString(const std::string& bitstring) {
    return std::stoi(bitstring, nullptr, 2); // Convert binary string to integer
}
void ChannelInterfaceTransmitter::Transmit(EncodedMessage encodedmessage,string filename_) {
    filename = filename_;
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    std::cout << "Transmitting as a continuous bitstream to file: " << filename << std::endl;
    file<<"Encoding scheme RS(n,k) in GF(2^m)";
    file<<"\n"<<"n="<<n<<"\n"<<"k="<<k<<"\n"<<"m="<<m<<"\n";
    int numberofencodedmessage=encodedmessage.GetcodewordVector().size()/n;
    std::vector<int> encodedmess = encodedmessage.GetcodewordVector();
    for (int i=0;i<numberofencodedmessage;i++){

        vector<int>word(encodedmess.begin()+i*n,encodedmess.begin()+i*n+n);
        for (int symbol: word) {
            file << ConvertToBitString(symbol);  // append all bits to the same line

        }
  // write newline at the end
  file << "\n";
    }
    file.close();
}





