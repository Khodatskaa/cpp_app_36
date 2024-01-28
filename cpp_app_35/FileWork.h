#ifndef FILEWORK_H
#define FILEWORK_H

#include <iostream>
#include <string>
#include <fstream>

class FileWork {
public:
    static void searchAndDisplayStats(const std::string& filePath, const std::string& searchString) {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cout << "Error: Unable to open file " << filePath << std::endl;
            return;
        }

        std::string line;
        size_t lineCount = 0;
        size_t occurrences = 0;

        while (std::getline(inputFile, line)) {
            lineCount++;
            size_t found = line.find(searchString);
            while (found != std::string::npos) {
                occurrences++;
                found = line.find(searchString, found + 1);
            }
        }

        std::cout << "Search Statistics:" << std::endl;
        std::cout << "Total lines: " << lineCount << std::endl;
        std::cout << "Occurrences of '" << searchString << "': " << occurrences << std::endl;
    }
    static void replaceAndDisplayStats(const std::string& filePath, const std::string& oldString, const std::string& newString) {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cout << "Error: Unable to open file " << filePath << std::endl;
            return;
        }

        std::ofstream outputFile("temp.txt");
        if (!outputFile.is_open()) {
            std::cout << "Error: Unable to create temporary file" << std::endl;
            return;
        }

        std::string line;
        size_t occurrences = 0;

        while (std::getline(inputFile, line)) {
            size_t found = line.find(oldString);
            while (found != std::string::npos) {
                occurrences++;
                line.replace(found, oldString.length(), newString);
                found = line.find(oldString, found + 1);
            }
            outputFile << line << '\n';
        }

        inputFile.close();
        outputFile.close();

        if (std::rename("temp.txt", filePath.c_str()) != 0) {
            std::cout << "Error: Unable to replace the original file" << std::endl;
        }
        else {
            std::cout << "Replacement Statistics:" << std::endl;
            std::cout << "Occurrences replaced: " << occurrences << std::endl;
        }
    }

    static void displayFileContent(const std::string& filePath) {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cout << "Error: Unable to open file " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
    }
    static void flipFileContent(const std::string& filePath) {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cout << "Error: Unable to open file " << filePath << std::endl;
            return;
        }

        const size_t initialCapacity = 10;
        std::string* lines = new std::string[initialCapacity];
        size_t lineCount = 0;
        size_t capacity = initialCapacity;

        while (std::getline(inputFile, lines[lineCount])) {
            lineCount++;

            if (lineCount == capacity) {
                capacity *= 2;
                std::string* tempLines = new std::string[capacity];
                for (size_t i = 0; i < lineCount; ++i) {
                    tempLines[i] = lines[i];
                }
                delete[] lines;
                lines = tempLines;
            }
        }

        for (size_t i = lineCount; i > 0; --i) {
            std::cout << lines[i - 1] << std::endl;
        }

        delete[] lines;
    }
    static void createFile(const std::string& filePath) {
        std::ofstream outputFile(filePath);
        if (!outputFile.is_open()) {
            std::cout << "Error: Unable to create file " << filePath << std::endl;
            return;
        }

        std::string line;
        std::cout << "Enter the file content. Enter 'q' to quit" << std::endl;
        while (std::getline(std::cin, line)) {
            if (line == "q") {
                break;
            }
            outputFile << line << '\n';
        }
    }
};

#endif 
