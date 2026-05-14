//
// Created by ziadf on 5/22/2025.
//

#include "../../include/Channel Interface/ChannelInterfaceReceiver.h"
#include <fstream>
#include"bitset"
#include<iostream>
#include <fstream>
#include <bitset>
#include <iostream>
#include <stdexcept>
#include<algorithm>

#include "../../include/Channel Interface/ChannelInterfaceTransmitter.h"
#include <fstream>
#include"bitset"
#include<iostream>
#include <sstream>
ChannelInterfaceReceiver::ChannelInterfaceReceiver(int m_,int n_,int k_) {
    m=m_;
    n=n_;
    k=k_;
}
EncodedMessage ChannelInterfaceReceiver::Receive(std::string filename_) {
    filename = filename_;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    std::cout << "Receiving continuous bit stream from file " << filename << std::endl;

    std::string line;

    // 🚫 Skip header
    std::getline(file, line);

    std::vector<int> symbolVector;

    while (std::getline(file, line)) {
        // 🪓 Find position of 3rd comma
        int commaCount = 0;
        std::size_t pos = 0;
        while (pos < line.size() && commaCount < 3) {
            if (line[pos] == ',') {
                ++commaCount;
            }
            ++pos;
        }

        if (commaCount < 3 || pos + n * m > line.size()) {
            throw std::runtime_error("Invalid line format or bitstream too short.");
        }

        // 🔎 Extract bitstream of length n * m after 3rd comma
        std::string bitstream = line.substr(pos, n * m);

        if (bitstream.length() != static_cast<size_t>(n * m)) {
            throw std::runtime_error("Bitstream length mismatch.");
        }

        for (int i = 0; i < n; ++i) {
            std::string symbolBits = bitstream.substr(i * m, m);
            int symbol = ConvertFromBitString(symbolBits);
            symbolVector.push_back(symbol);
        }
    }

    file.close();

    receivedencodedmessage.SetField(m);
    receivedencodedmessage.SetSize(symbolVector.size());
    receivedencodedmessage.SetcodewordVector(symbolVector);

    return receivedencodedmessage;
}




std::string ChannelInterfaceReceiver::ConvertToBitString(int word) {
    if (word >= (1 << m)) {
        throw std::overflow_error("Word exceeds the size of GF(2^m).");
    }
    std::bitset<32> bits(word); // Bitset of 32 bits (just in case word is big)
    return bits.to_string().substr(32 - m); // Extract only the last m bits
}
int ChannelInterfaceReceiver::ConvertFromBitString(const std::string& bitstring) {
    return std::stoi(bitstring, nullptr, 2); // Convert binary string to integer
}



