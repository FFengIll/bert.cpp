#ifndef BERT_TOKENIZER_H
#define BERT_TOKENIZER_H

#include "tokenizers_cpp.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using tokenizers::Tokenizer;

class BertTokenizer
{
    std::unique_ptr<Tokenizer> tok;

public:
    BertTokenizer(const std::string &blob);
    ~BertTokenizer();
    std::string Decode(const std::vector<int> &ids);
    std::string Decode(const int32_t id);
    std::vector<int> Encode(const std::string &text);
    std::string LoadBytesFromFile(const std::string &path);
    void PrintEncodeResult(const std::vector<int> &ids);
};

#endif