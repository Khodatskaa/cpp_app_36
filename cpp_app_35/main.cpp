#include "FileWork.h"

int main() {
    std::string filePath;
    std::cout << "Enter the path to the file: ";
    std::getline(std::cin, filePath);

    int choice;
    do {
        std::cout << "\nFile Operations Menu:" << std::endl;
        std::cout << "1. Search for a string" << std::endl;
        std::cout << "2. Replace a string" << std::endl;
        std::cout << "3. Display file content" << std::endl;
        std::cout << "4. Flip file content" << std::endl;
        std::cout << "5. Create or overwrite a file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string searchString;
            std::cout << "Enter the string to search: ";
            std::getline(std::cin, searchString);
            FileWork::searchAndDisplayStats(filePath, searchString);
            break;
        }
        case 2: {
            std::string oldString, newString;
            std::cout << "Enter the string to replace: ";
            std::getline(std::cin, oldString);
            std::cout << "Enter the new string: ";
            std::getline(std::cin, newString);
            FileWork::replaceAndDisplayStats(filePath, oldString, newString);
            break;
        }
        case 3:
            FileWork::displayFileContent(filePath);
            break;
        case 4:
            FileWork::flipFileContent(filePath);
            break;
        case 5:
            FileWork::createFile(filePath);
            break;
        case 0:
            std::cout << "Exiting the program.." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please enter a valid option" << std::endl;
        }
    } while (choice != 0);

    return 0;
}
