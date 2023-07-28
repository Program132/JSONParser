#include <iostream>
#include <string_view>
#include <fstream>
#include <vector>
#include <optional>
#include <map>

#include "src/Tokenizer/Tokenizer.h"
#include "src/Key/Key.h"

std::optional<Token> ExpectKey(std::vector<Token>::const_iterator &current) {
    if (current->type == STRING) {
        auto returnt = current;
        current++;
        return *returnt;
    }
    return std::nullopt;
}

std::optional<Token> ExpectValue(std::vector<Token>::const_iterator& current) {
    if (current->type == INT || current->type == DOUBLE || current->type == STRING) {
        auto returnt = current;
        current++;
        return *returnt;
    }
    return std::nullopt;
}

std::optional<Token> ExpectOperator(std::vector<Token>::const_iterator& current, std::string_view o) {
    if (current->type == OPERATOR && current->content == o) {
        auto returnt = current;
        current++;
        return *returnt;
    }
    return std::nullopt;
}

void ParseCode(const std::vector<Token>& tokenList) {
    auto currentToken = tokenList.begin();

    if (!ExpectOperator(currentToken, "{").has_value()) {
        std::cerr  << "Forgot to open the first bloc" << std::endl;
    }

    int needClose = 1;

    std::map<std::string, Key> keys;

    while (needClose > 0) {
        auto key_name = ExpectKey(currentToken);
        if (!key_name.has_value()) {
            std::cerr  << "Forgot to say the key_name name" << std::endl;
        }

        if (!ExpectOperator(currentToken, ":").has_value()) {
            std::cerr  << "':' to include the key_value to the key_name" << std::endl;
        }

        auto key_value = ExpectValue(currentToken);
        if (!key_value.has_value()) {
            std::cerr  << "Forgot to say the key_name key_value" << std::endl;
        }

        if (!ExpectOperator(currentToken, ",").has_value() && ExpectKey(currentToken)) {
            std::cerr  << "',' to conclude the key_name" << std::endl;
        }

        Key key(key_name->content, key_value->content);
        if (key_value->type == INT) {
            key.type = "int";
        } else if (key_value->type == DOUBLE) {
            key.type = "double";
        } else {
            key.type = "string";
        }

        keys[key_name->content] = key;

        if (ExpectOperator(currentToken, "}").has_value()) { needClose-=1; }
        else if (ExpectOperator(currentToken, "{").has_value()) { needClose+=1; }
    }
}


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

    ParseCode(TokensCode);

    return 0;
}
