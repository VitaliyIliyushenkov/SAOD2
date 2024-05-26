#pragma once
#include <string>

class Compressor {
public:
    static size_t compress(const std::string& inputFile, const std::string& outputFile);
    static void decompress(const std::string& inputFile, const std::string& outputFile);
    static size_t getFileSize(const std::string& fileName);

private:
    static std::string eliasGammaEncode(int number);
    static int eliasGammaDecode(const std::string& bits, size_t& offset);
};
