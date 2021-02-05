#include <string>
#include "Lexer.hpp"
#include<map>
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
        void expr();
        void term();
        void factor();
    public:
        Parser(Lexer *lr);
        bool parse();
};

#endif