#pragma once
#include <string>

class Compressor {
public:
    static void compress(const std::string& inputFile, const std::string& outputFile);
    static void decompress(const std::string& inputFile, const std::string& outputFile);

private:
    static std::string eliasGammaEncode(int number);
    static int eliasGammaDecode(const std::string& bits, size_t& offset);
};
