#include "Parser.hpp"
#include "Lexer.hpp"
#include <iostream>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;

token *Parser::LL(int k)
{
    return TokenCache[(index + k - 1) % TOKEN_CACHE_SIZE];
}

bool Parser::parse()
{
    try
    {
        while (LL(1)->type != TOKEN_EOF)
        {
            expr();
            match(TOKEN_SEMICOLON);
        }
    }
    catch (const char *c)
    {
        std::cerr << c << '\n';
    }

    //释放内存
    lexer->FreeToken();
    return true;
}

map<tokenType, int> level;
//解析器初始化
Parser::Parser(Lexer *lr)
{
    //Token缓冲池初始化
    lexer = lr;
    for (int i = 0; i < TOKEN_CACHE_SIZE; i++)
    {
        consume();
    }
    //运算符优先级表初始化
    //    level[TOKEN_SUB]=5;
    //    level[TOKEN_ADD]=5;
    //    level[TOKEN_INT_LITERAL]=6;
}

void Parser::consume()
{

    TokenCache[index] = lexer->getNextToken();
    index = (index + 1) % TOKEN_CACHE_SIZE;
}

void Parser::match(tokenType type)
{
    if (LL(1)->type == type)
    {
        consume();
    }
    else
    {
        cout << LL(1)->type << ":" << type;
        throw "error:match";
    }
}

void Parser::expr()
{
    term();
    bool plus_or_sub = LL(1)->type == TOKEN_ADD || LL(1)->type == TOKEN_SUB;
    while (plus_or_sub)
    {
        switch (LL(1)->type)
        {
        case TOKEN_ADD:
        {
            match(TOKEN_ADD);
            term();
            break;
        }
        case TOKEN_SUB:
        {
            match(TOKEN_SUB);
            term();
            break;
        }
        }
        plus_or_sub = LL(1)->type == TOKEN_ADD || LL(1)->type == TOKEN_SUB;
    }
}

void Parser::term()
{
    factor();
    bool mul_or_div = LL(1)->type == TOKEN_MUL || LL(1)->type == TOKEN_DIV;
    while (mul_or_div)
    {
        switch (LL(1)->type)
        {
        case TOKEN_MUL:
        {
            match(TOKEN_MUL);
            factor();
            break;
        }
        case TOKEN_DIV:
        {
            match(TOKEN_DIV);
            factor();
            break;
        }
        }
        mul_or_div = LL(1)->type == TOKEN_MUL || LL(1)->type == TOKEN_DIV;
    }
}
void Parser::factor()
{
    switch (LL(1)->type)
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
        cout << LL(1)->type << endl;
        throw "error:factor";
    }
    }
}