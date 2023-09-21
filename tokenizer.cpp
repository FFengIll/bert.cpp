#include "bert.h"
#include "ggml.h"
#include "tokenizers_cpp.h"
#include "tokenizer.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <thread>
#include <algorithm>

using tokenizers::Tokenizer;

// BertTokenizer(const std::string &path)
// {

//     // Read blob from file.
//     auto blob = LoadBytesFromFile(path);
//     // Note: all the current factory APIs takes in-memory blob as input.
//     // This gives some flexibility on how these blobs can be read.
//     this->tok = Tokenizer::FromBlobJSON(blob);
// }

BertTokenizer::BertTokenizer(const std::string &blob)
{

    // Read blob from file.
    // auto blob = LoadBytesFromFile(path);
    // Note: all the current factory APIs takes in-memory blob as input.
    // This gives some flexibility on how these blobs can be read.
    this->tok = Tokenizer::FromBlobJSON(blob);
}

BertTokenizer::~BertTokenizer()
{
    this->tok.reset();
}

std::string BertTokenizer::Decode(const std::vector<int> &ids)
{
    return tok->Decode(ids);
}

std::string BertTokenizer::Decode(const int32_t id)
{
    std::vector<int> ids(1, id);
    return tok->Decode(ids);
}

std::vector<int> BertTokenizer::Encode(const std::string &text)
{
    return tok.get()->Encode(text);
}

std::string BertTokenizer::LoadBytesFromFile(const std::string &path)
{
    std::ifstream fs(path, std::ios::in | std::ios::binary);
    if (fs.fail())
    {
        std::cerr << "Cannot open " << path << std::endl;
        exit(1);
    }
    std::string data;
    fs.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(fs.tellg());
    fs.seekg(0, std::ios::beg);
    data.resize(size);
    fs.read(data.data(), size);
    return data;
}

void BertTokenizer::PrintEncodeResult(const std::vector<int> &ids)
{
    std::cout << "tokens=[";
    for (size_t i = 0; i < ids.size(); ++i)
    {
        if (i != 0)
            std::cout << ", ";
        std::cout << ids[i];
    }
    std::cout << "]" << std::endl;
}
