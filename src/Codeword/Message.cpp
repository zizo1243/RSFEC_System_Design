#include <fstream>
#include <iostream>

#include "../../include/Codeword/Message.h"

void Message::InputMessage(const vector<int>& userData) {
    SetcodewordVector(userData);
}

void Message::InputBinary(const vector<int>& binaryData) {
    SetBinaryVector(binaryData);
}

vector<int> Message::OutputMessage()  {
    return GetcodewordVector();
}

vector<int> Message::OutputBinary() {
    return GetBinaryVector();
}

void Message::ReadCodewordFromFile(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<int> vec;
    int value;
    while (infile >> value) {
        if (value < 0 || value >= (1 << m)) {
            throw std::out_of_range("Value out of GF(2^m) range: " + std::to_string(value));
        }
        vec.push_back(value);
    }

    infile.close();
    SetcodewordVector(vec);
    SetSize(vec.size());
}

void Message::ReadBitsFromFile(const std::string &filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::vector<int> vec;
    std::string line;
    while (std::getline(infile, line)) {
        if (line.length() != m) {
            throw std::invalid_argument("Each line must be " + std::to_string(m) + " bits long.");
        }

        int value = 0;
        for (char c : line) {
            if (c != '0' && c != '1') {
                throw std::invalid_argument("Invalid bit character in file: " + line);
            }
            value = (value << 1) | (c - '0');
        }

        vec.push_back(value);
    }

    infile.close();
    SetcodewordVector(vec);
    SetSize(vec.size());
}



