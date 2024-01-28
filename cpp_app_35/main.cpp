#include "HTML_Validator.h"

int main() {
    std::string filePath;
    std::cout << "Enter the path to the HTML file: ";
    std::getline(std::cin, filePath);

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return 1;
    }

    std::string fileContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    inputFile.close();

    if (HTMLValidator::isValidHTML(fileContent)) {
        std::cout << "HTML file is valid" << std::endl;
    }
    else {
        std::cout << "HTML file is not valid" << std::endl;
    }

    return 0;
}
