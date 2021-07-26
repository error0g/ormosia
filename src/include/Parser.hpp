#include <string>
#include "Lexer.hpp"
#include <map>
#include "AST.hpp"
#include <vector>
#ifndef PARSER_MIAN
#define PARSER_MAIN
#define TOKEN_CACHE_SIZE 8
class Parser;

class Parser
{

private:
    int index = 0;
    void match(tokenType type);
    token *CurrentToken(int k);
    token *tokenCache[TOKEN_CACHE_SIZE];
    Lexer *lexer;
    void consume();
    AST *expr();
    AST *term();
    AST *factor();

public:
    Parser(Lexer *lr);
    std::vector<AST *> build();
};

#endif