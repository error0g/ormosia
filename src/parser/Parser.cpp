#include "Parser.hpp"
#include "AST.hpp"
#include "Lexer.hpp"
#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::vector;

token *Parser::CurrentToken(int k)
{
    return tokenCache[(index + k - 1) % TOKEN_CACHE_SIZE];
}
vector<AST *> Parser::build()
{
    vector<AST *> astList;

    try
    {
        while (CurrentToken(1)->type != TOKEN_EOF)
        {
            AST *tree = expr();
            match(TOKEN_SEMICOLON);
            astList.push_back(tree);
        }
    }
    catch (const char *c)
    {
        std::cerr << c << '\n';
    }

    return astList;
}
//解析器初始化
Parser::Parser(Lexer *lr)
{
    //Token缓冲池初始化
    lexer = lr;
    for (int i = 0; i < TOKEN_CACHE_SIZE; i++)
    {
        consume();
    }
}
void Parser::consume()
{
    tokenCache[index] = lexer->getNextToken();
    index = (index + 1) % TOKEN_CACHE_SIZE;
}
void Parser::match(tokenType type)
{
    if (CurrentToken(1)->type == type)
    {
        consume();
    }
    else
    {
        cout << CurrentToken(1)->type << ":" << type;
        throw "error:match";
    }
}
AST *Parser::expr()
{
    AST *node = term();
    bool IsExpr = CurrentToken(1)->type == TOKEN_ADD || CurrentToken(1)->type == TOKEN_SUB;
    while (IsExpr)
    {
        token *current = CurrentToken(1);
        switch (CurrentToken(1)->type)
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

        node = new BinOp(current, node, term());
        IsExpr = CurrentToken(1)->type == TOKEN_ADD || CurrentToken(1)->type == TOKEN_SUB;
    }
    return node;
}
AST *Parser::term()
{
    AST *node = factor();
    bool IsTerm = CurrentToken(1)->type == TOKEN_MUL || CurrentToken(1)->type == TOKEN_DIV || CurrentToken(1)->type == TOKEN_MOD;
    while (IsTerm)
    {
        token *current = CurrentToken(1);
        switch (CurrentToken(1)->type)
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
        case TOKEN_MOD:
        {
            match(TOKEN_MOD);
            break;
        }
        }
        node = new BinOp(current, node, factor());
        IsTerm = CurrentToken(1)->type == TOKEN_MUL || CurrentToken(1)->type == TOKEN_DIV || CurrentToken(1)->type == TOKEN_MOD;
        ;
    }
    return node;
}
AST *Parser::factor()
{
    AST *node;
    token *current = CurrentToken(1);
    bool SUB = false;
    switch (CurrentToken(1)->type)
    {
    case TOKEN_LP:
    {
        match(TOKEN_LP);
        node = expr();
        match(TOKEN_RP);
        break;
    }
    case TOKEN_SUB:
    {
        SUB = true;
        match(TOKEN_SUB);
    }
    case TOKEN_INT_LITERAL:
    {
        if (SUB)
        {
            CurrentToken(1)->txt = "-" + CurrentToken(1)->txt;
        }
        match(TOKEN_INT_LITERAL);
        node = new NUM(current);
        break;
    }
    default:
    {
        cout << "parser:" << CurrentToken(1)->type << endl;
        throw "parser error:factor";
    }
    }
    return node;
}