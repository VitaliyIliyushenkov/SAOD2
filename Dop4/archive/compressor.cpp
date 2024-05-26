#include "compressor.h"
#include <bitset>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iostream>
#include <sys/stat.h>



std::string intToBinaryString(int number) {
    // Эта функция преобразует целое число в двоичное представление в виде строки
    //intToBinaryString(97) вернёт "1100001"
    std::string binary;
    while (number > 0) {
        binary = (number % 2 == 0 ? "0" : "1") + binary;
        number /= 2;
    }
    return binary.empty() ? "0" : binary;
}

std::string Compressor::eliasGammaEncode(int number) {
    //Эта функция реализует кодирование методом Элиаса Гаммы
    //Для числа 97 (1100001 в двоичной) кодировка будет 00000001100001
    if (number <= 0) {
        throw std::invalid_argument("Number must be positive");
    }

    std::string binary = intToBinaryString(number);
    std::string prefix(binary.length() - 1, '0');
    return prefix + binary;
}

int Compressor::eliasGammaDecode(const std::string& bits, size_t& offset) {
    size_t originalOffset = offset;
    while (offset < bits.size() && bits[offset] == '0') {
        ++offset;
    }

    int length = offset - originalOffset + 1;
    if (offset + length > bits.size()) {
        throw std::runtime_error("Invalid Elias Gamma encoded string");
    }

    std::string binary = bits.substr(offset, length);
    offset += length;
    int decodedNumber = std::stoi(binary, nullptr, 2);

    if (decodedNumber <= 0) {
        throw std::invalid_argument("Decoded number must be positive");
    }

    return decodedNumber;
}

size_t Compressor::getFileSize(const std::string& fileName) {
    struct stat stat_buf;
    int rc = stat(fileName.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

size_t Compressor::compress(const std::string& inputFile, const std::string& outputFile) {
    //Символ 'a' (ASCII 97): eliasGammaEncode(97) вернёт 00000001100001
    std::ifstream input(inputFile, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::ofstream output(outputFile, std::ios::binary);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }

    char ch;
    std::string encodedBits;
    while (input.get(ch)) {
        std::string encoded = eliasGammaEncode(static_cast<unsigned char>(ch));
        encodedBits += encoded;
    }

    size_t bitCount = encodedBits.size();
    output.write(reinterpret_cast<const char*>(&bitCount), sizeof(size_t));

    std::bitset<8> bits;
    for (size_t i = 0; i < encodedBits.size(); i++) {
        bits[7 - (i % 8)] = encodedBits[i] == '1';
        if (i % 8 == 7 || i == encodedBits.size() - 1) {
            output << static_cast<char>(bits.to_ulong());
            bits.reset();
        }
    }

    input.close();
    output.close();

    return getFileSize(outputFile);
}


void Compressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile, std::ios::binary);
    if (!input.is_open()) {
        throw std::runtime_error("Cannot open input file");
    }

    std::ofstream output(outputFile);
    if (!output.is_open()) {
        throw std::runtime_error("Cannot open output file");
    }

    size_t bitCount;
    input.read(reinterpret_cast<char*>(&bitCount), sizeof(size_t));

    std::string bits;
    char ch;
    while (input.get(ch)) {
        bits += std::bitset<8>(ch).to_string();
    }

    if (bits.size() < bitCount) {
        throw std::runtime_error("Encoded data is corrupted or incomplete");
    }

    bits = bits.substr(0, bitCount);

    size_t offset = 0;
    while (offset < bitCount) {
        try {
            int decoded = eliasGammaDecode(bits, offset);
            output << static_cast<char>(decoded);
        }
        catch (const std::exception& e) {
            std::cerr << "Decoding error at offset " << offset << ": " << e.what() << std::endl;
            throw;
        }
    }

    input.close();
    output.close();
}
