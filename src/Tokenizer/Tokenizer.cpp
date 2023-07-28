#include "Tokenizer.h"

std::ostream &operator<<(std::ostream &flux, const Token &token) {
    flux << "(" <<  token.content << ", " << token.lineNumber << ", " << Types_STR[token.type] << ")";
    return flux;
}

std::vector<Token> TokenBuilder::CodeToTokens(std::string_view code) {
    std::vector<Token> Tokens;
    Token current_token;

    for (auto const& element : code) {
        switch (element) {
            case '9':
            case '8':
            case '7':
            case '6':
            case '5':
            case '4':
            case '3':
            case '2':
            case '1':
            case '0':
                if (current_token.type == WHITESPACE) {
                    current_token.type = INT;
                    current_token.content.append(1, element);
                } else if (current_token.type == POSSIBLE_DOUBLE) {
                    current_token.type = DOUBLE;
                    current_token.content.append(1, element);
                } else {
                    current_token.content.append(1, element);
                }
                break;
            
            case '"':
                if (current_token.type == WHITESPACE) {
                    current_token.type = POSSIBLE_STRING;
                    current_token.content.append(1, element);
                } else if (current_token.type == POSSIBLE_STRING) {
                    current_token.type = STRING;
                    current_token.content.append(1, element);
                    ConcludeToken(current_token, Tokens);
                }
                break;

            case '.':
                if (current_token.type == INT) {
                    current_token.type = POSSIBLE_DOUBLE;
                    current_token.content.append(1, element);
                }
                break;

            case '\n':
                ConcludeToken(current_token, Tokens);
                current_token.lineNumber += 1;
                break;

            case '{':
            case '}':
            case ':':
            case ',':
                ConcludeToken(current_token, Tokens);
                current_token.type = OPERATOR;
                current_token.content.append(1, element);
                ConcludeToken(current_token, Tokens);
                break;

            default:
                if (current_token.type == WHITESPACE || current_token.type == INT) {
                    ConcludeToken(current_token, Tokens);
                } else {
                    current_token.content.append(1, element);
                }
                break;
        }
    }
    ConcludeToken(current_token, Tokens);
    return Tokens;
}

void TokenBuilder::ConcludeToken(Token &token, std::vector<Token> &tokenList) {
    if (token.type != WHITESPACE) {
        tokenList.push_back(token);
    }

    token.type = WHITESPACE;
    token.content.erase();
}
