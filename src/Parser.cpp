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
       expr();
    }
    catch(const char *c)
    {
        std::cerr << c << '\n';
    }

    //释放内存
    lexer->FreeToken();
    return true;
}
//解析器初始化
Parser::Parser(Lexer* lr)
{
    //Token缓冲池初始化
    lexer=lr;
    for(int i=0;i<TOKEN_CACHE_SIZE;i++)
    {
        consume();
    }
   
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
        throw "error:match";
    }
}
void Parser::expr()
{
    term();expr_tail();
}
void Parser::expr_tail()
{
    switch(LL(1)->type)
    {
        case TOKEN_ADD: {
            match(TOKEN_ADD);
            term();
            expr_tail();
            break;
        }
        case TOKEN_SUB: {
            match(TOKEN_SUB);
            term();
            expr_tail();
              break;
        }
    }
}
void Parser::term()
{
    factor();
}
void Parser::factor()
{
    switch(LL(1)->type)
    {
        case TOKEN_LP:
        {
            match(TOKEN_LP);
            expr();
            match(TOKEN_RP);
            break;
        }
        case TOKEN_SUB:
        {
            match(TOKEN_SUB);
        }
        case TOKEN_INT_LITERAL:
        {
            match(TOKEN_INT_LITERAL);
            break;
        }
        default:
        {
            cout<<LL(1)->type<<endl;
            throw "error:factor";
        }
    }
}