#include <iostream>
#include <chrono>
#include "compressor.h"
#include "cli.h"

int main(int argc, char** argv) {
    CLI cli;
    if (!cli.parseArgs(argc, argv)) {
        cli.showHelp();
        return 1;
    }

    try {
        auto start = std::chrono::high_resolution_clock::now();

        if (cli.isCompress()) {
            std::cout << "Done!\n";
            std::cout << "Compressing file: " << cli.getInputFile() << std::endl;
            size_t originalSize = Compressor::getFileSize(cli.getInputFile());
            size_t compressedSize = Compressor::compress(cli.getInputFile(), cli.getOutputFile());
            std::cout << "Compression ratio: " << originalSize << " bytes / " << compressedSize << " bytes = "
                << static_cast<double>(originalSize) / compressedSize << std::endl;
        }
        else if (cli.isDecompress()) {
            std::cout << "Done!\n";
            std::cout << "Decompressing file: " << cli.getInputFile() << std::endl;
            Compressor::decompress(cli.getInputFile(), cli.getOutputFile());
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken: " << elapsed.count() << " sec\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
