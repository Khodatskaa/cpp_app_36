#ifndef HTML_VALIDATOR_H
#define HTML_VALIDATOR_H

#include <iostream>
#include <string>
#include <stack>
#include <fstream>

class HTMLValidator {
public:
    static bool isValidHTML(const std::string& content) {
        std::stack<std::string> tagStack;

        size_t pos = 0;
        while ((pos = content.find('<', pos)) != std::string::npos) {
            size_t endPos = content.find('>', pos + 1);
            if (endPos == std::string::npos) {
                std::cout << "Error: Found opening tag without closing tag" << std::endl;
                return false;
            }

            std::string tag = content.substr(pos + 1, endPos - pos - 1);    //substr - returns a newly constructed string object with its value initialized to a copy of a substring of this object
            if (tag.empty() || tag[0] == '/') {
                std::cout << "Error: Invalid tag found" << std::endl;
                return false;
            }

            if (tag.back() == '/') {
				tag.pop_back();
            }
            else if (tag[0] == '/') {
                if (tagStack.empty()) {
                    std::cout << "Error: Found closing tag without matching opening tag" << std::endl;
                    return false;
                }

                std::string openTag = tagStack.top();
                tagStack.pop();

                if (openTag != tag.substr(1)) {
                    std::cout << "Error: Mismatched opening and closing tags" << std::endl;
                    return false;
                }
            }
            else {
                tagStack.push(tag);
            }

            pos = endPos + 1;
        }

        if (!tagStack.empty()) {
            std::cout << "Error: Unmatched opening tags" << std::endl;
            return false;
        }

        return true;
    }
};

#endif 
