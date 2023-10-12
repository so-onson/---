#include <unordered_set>

extern "C" void count_char(char* word, int* result) {
    std::unordered_set<char> distinctChars;
    while (*word != ' ' && *word != '\n') {
        distinctChars.insert(*word);
        ++word;
    }
    *result = static_cast<int>(distinctChars.size());
}
