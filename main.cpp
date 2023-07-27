#include <iostream>
#include <fstream>
#include <vector>

#include "src/Tokenizer/Tokenizer.h"

int main(int argc, char** argv) {
    std::string pos_FileName;
    if (argc == 2) {
        pos_FileName = argv[1];
    } else {
        std::cout << "File : ";
        std::cin >> pos_FileName;
        std::cout << std::endl;
    }

    std::ifstream file {pos_FileName};
    if (!file) {
        std::cerr << "Did not find the file!" << std::endl;
        return -1;
    }

    std::string contentFile((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    std::vector<Token> TokensCode = TokenBuilder::CodeToTokens(contentFile);

    for (auto const& e : TokensCode) { std::cout << e << std::endl; }

    return 0;
}
