#include "Lexer.hpp"

#ifndef PARSER_AST
#define PARSER_AST

class AST
{

public:
    AST();
    AST(::token *tk, AST *lt, AST *rt)
    {
        token = tk;
        left = lt;
        right = rt;
    }
    AST *left = nullptr;
    AST *right = nullptr;
    ::token *token = nullptr;
};

class BinOp : public AST
{
public:
    BinOp();
    BinOp(::token *token, AST *lt, AST *rt) : AST(token, lt, rt) {}
};

class NUM : public AST
{
public:
    NUM();
    NUM(::token *token) : AST(token, nullptr, nullptr) {}
};

#endif