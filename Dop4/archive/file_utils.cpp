#include "file_utils.h"
#include <fstream>

bool FileUtils::isValidFile(const std::string& fileName) {
    std::ifstream file(fileName);
    return file.good();
}
