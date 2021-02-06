#include "Parser.hpp"
#include "AST.hpp"
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

bool Parser::parse(BinOp* ast)
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
   // 运算符优先级表初始化
       level[TOKEN_SUB]=5;
       level[TOKEN_ADD]=5;
       level[TOKEN_INT_LITERAL]=6;
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


AST* Parser::expr()
{
    AST* node=term();
    bool plus_or_sub = LL(1)->type == TOKEN_ADD || LL(1)->type == TOKEN_SUB;
    while (plus_or_sub)
    {
        switch (LL(1)->type)
        {
        case TOKEN_ADD:
        {
            match(TOKEN_ADD);
            break;
        }
        case TOKEN_SUB:
        {
            match(TOKEN_SUB);
            break;
        }
        }
        
        node=new BinOp(LL(1),node,term());
        plus_or_sub = LL(1)->type == TOKEN_ADD || LL(1)->type == TOKEN_SUB;
    }
    return node;
}
AST* Parser::term()
{
    AST* node=factor();
    bool mul_or_div = LL(1)->type == TOKEN_MUL || LL(1)->type == TOKEN_DIV;
    while (mul_or_div)
    {
        switch (LL(1)->type)
        {
        case TOKEN_MUL:
        {
            match(TOKEN_MUL);
            break;
        }
        case TOKEN_DIV:
        {
            match(TOKEN_DIV);
            break;
        }
        }
        node=new BinOp(LL(1),node,factor());
        mul_or_div = LL(1)->type == TOKEN_MUL || LL(1)->type == TOKEN_DIV;
    }
    return node;
}
AST* Parser::factor()
{
    AST* node;
    bool SUB=false;
    switch (LL(1)->type)
    {
    case TOKEN_LP:
    {
        match(TOKEN_LP);
        return expr();
        match(TOKEN_RP);
        break;
    }
    case TOKEN_SUB:
    {
        match(TOKEN_SUB);
        SUB=true;
    }
    case TOKEN_INT_LITERAL:
    {
        match(TOKEN_INT_LITERAL);
        if(SUB)
        {
            LL(1)->txt="-"+LL(1)->txt;
        }
        break;
        node=new NUM(LL(1));
    }
    default:
    {
        cout << LL(1)->type << endl;
        throw "error:factor";
    }
    }
    return node;
}