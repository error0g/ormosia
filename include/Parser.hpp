#include <string>
#include "Lexer.hpp"
#ifndef _PARSER_
#define _PARSER_
class Parser;

class Parser{

    private:
        int TOKEN_CACHE_SIZE=11;
        int index=0;
        void match(tokenType type);
        token LL(int k);
        token TokenCache [TOKEN_CACHE_SIZE];
        Lexer *lexer;
    public:
        Parser(Lexer *lr);
        bool parse();
};

#endif