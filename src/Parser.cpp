#include "Parser.hpp"
#include "Lexer.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
void Parser::match(tokenType type)
{
    if(LL(1).type==type)
    {
        index++;
    }
    else {
        exit(1);
    }
}

token Parser::LL(int k)
{
    if((index+k-1)>=TOKEN_CACHE_SIZE)
    {

    }

    return TokenCache[index+k-1];
}


bool Parser::parse()
{
 
    return true;
}

Parser::Parser(Lexer* lr)
{
    lexer=lr;
    for(int i=0;i<TOKEN_CACHE_SIZE;i++)
    {
        TokenCache[i]=lexer->getNextToken();
        if(TokenCache[i].type==TOKEN_EOF)
            break;
        cout<<"<"<<TokenCache[i].txt<<","<<TokenCache[i].type<<">"<<endl;
    }
    
}