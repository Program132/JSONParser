#pragma once

#include <iostream>
#include <vector>
#include <string_view>

enum Types {
    WHITESPACE,

    // Basics:
    INT,
    POSSIBLE_DOUBLE,
    DOUBLE,
    POSSIBLE_STRING,
    STRING,
    OPERATOR,
};

inline constexpr const char *Types_STR[] =  {
        "WHITESPACE",

        // Basics:
        "INT",
        "POSSIBLE_DOUBLE",
        "DOUBLE",
        "POSSIBLE_STRING",
        "STRING",
        "OPERATOR",
};

class Token {
public:
    Types type = WHITESPACE;
    std::string content;
    size_t lineNumber = 1;

    friend std::ostream& operator<<(std::ostream& flux, Token const& token);
};

class TokenBuilder {
public:
    static std::vector<Token> CodeToTokens(std::string_view code);
private:
    static void ConcludeToken(Token& token, std::vector<Token>& tokenList);
};