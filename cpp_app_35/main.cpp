#include "SmartPointer.h"

int main() {
    UniquePtr<int> uniquePtr(new int(42));
    std::cout << "UniquePtr value: " << *uniquePtr << std::endl;

    SharedPtr<int> sharedPtr1(new int(10));
    SharedPtr<int> sharedPtr2 = sharedPtr1;
    std::cout << "SharedPtr1 value: " << *sharedPtr1 << std::endl;
    std::cout << "SharedPtr2 value: " << *sharedPtr2 << std::endl;

    return 0;
}
