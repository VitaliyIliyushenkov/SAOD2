#include "cli.h"
#include <iostream>

bool CLI::parseArgs(int argc, char** argv) {
    if (argc < 4) {
        return false;
    }

    std::string option = argv[1];
    if (option == "-c" || option == "--compress") {
        if (argc != 4) {
            return false;
        }
        compress = true;
        inputFile = argv[2];
        outputFile = argv[3];
    }
    else if (option == "-d" || option == "--decompress") {
        if (argc != 4) {
            return false;
        }
        decompress = true;
        inputFile = argv[2];
        outputFile = argv[3];
    }
    else {
        return false;
    }

    return true;
}

void CLI::showHelp() const {
    std::cout << "This is Elias gamma coding compressor for ASCII text files.\n";
    std::cout << "General options:\n";
    std::cout << "  -c [ --compress ] <input> <output>    Compress file\n";
    std::cout << "  -d [ --decompress ] <input> <output>  Decompress file\n";
    std::cout << "  -h [ --help ]                        Show help\n";
}

bool CLI::isCompress() const {
    return compress;
}

bool CLI::isDecompress() const {
    return decompress;
}

const std::string& CLI::getInputFile() const {
    return inputFile;
}

const std::string& CLI::getOutputFile() const {
    return outputFile;
}
