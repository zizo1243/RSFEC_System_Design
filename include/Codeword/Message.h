//
// Created by ziadf on 5/16/2025.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include "Codeword.h"

class Message : public Codeword {
public:
    void InputMessage(const vector<int>& userData);
    void InputBinary(const vector<int>& binaryData);
    vector<int> OutputMessage() ;
    vector<int> OutputBinary();
    void ReadCodewordFromFile(const std::string& filename);
    void ReadBitsFromFile(const std::string& filename);

};

#endif
