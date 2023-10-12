#include <iostream>
#include <string>

static constexpr size_t kMaxLength = 255;

extern "C" char* find_word(const char* input, size_t size, char* ans);

int main() {
    int n = 0;
    int count = 4;
    std::cout << "Input string" << std::endl;

    std::string inputStr;
    std::getline(std::cin, inputStr);
    inputStr += " ";

    if (inputStr.size() > kMaxLength) {
        std::cout << "Input should be <= 255 characters long" << std::endl;
        return -1;
    }

    char* word = new char[20];
    find_word(inputStr.c_str(), inputStr.size(), word);
    std::cout << word << std::endl;

    return 0;
}
