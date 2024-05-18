#pragma once
#include <string>

class CLI {
public:
    bool parseArgs(int argc, char** argv);
    void showHelp() const;
    bool isCompress() const;
    bool isDecompress() const;
    const std::string& getInputFile() const;
    const std::string& getOutputFile() const;

private:
    bool compress = false;
    bool decompress = false;
    std::string inputFile;
    std::string outputFile;
};
