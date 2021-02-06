#include <string>
#include "Lexer.hpp"
#include<map>
#include "AST.hpp"
#ifndef _PARSER_
#define _PARSER_
#define TOKEN_CACHE_SIZE 8
class Parser;

class Parser{

    private:
        int index=0;
        void match(tokenType type);
        token* LL(int k);
        token* TokenCache [TOKEN_CACHE_SIZE];
        Lexer *lexer;
        void consume();
        AST* expr();
        AST* term();
        AST* factor();
    public:
        Parser(Lexer *lr);
        bool Parser::parse(BinOp* ast);
};

#endif