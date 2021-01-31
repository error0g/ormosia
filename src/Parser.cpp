#include "Parser.hpp"
#include "Lexer.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;


token* Parser::LL(int k)
{
    return TokenCache[(index+k-1)%TOKEN_CACHE_SIZE];
}


bool Parser::parse()
{
    try
    {
        match(TOKEN_INT);
        match(TOKEN_IDENTIFIER);
        match(TOKEN_SEMICOLON);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    lexer->FreeToken();
    return true;
}

Parser::Parser(Lexer* lr)
{
    lexer=lr;
    for(int i=0;i<TOKEN_CACHE_SIZE;i++)
    {
        consume();
        cout<<lexer->getLine()<<","<<lexer->getColumn();
        cout<<"<"<<TokenCache[i]->txt<<","<<TokenCache[i]->type<<">"<<endl;
    }
    lexer->getNextToken();
}

void Parser::consume()
{
    TokenCache[index]=lexer->getNextToken();
    index=(index+1)%TOKEN_CACHE_SIZE;
}

void Parser::match(tokenType type)
{
    if(LL(1)->type==type)
    {
        consume();
    }
    else {
        cout<<LL(1)->type<<":"<<type;
        throw "error";
    }
}