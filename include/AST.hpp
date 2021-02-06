#include"Lexer.hpp"

#ifndef _AST_
#define _AST_

class AST
{

    public:
        AST* left;
        AST* right;
        AST();
        ::token* token;
        AST(::token* token,AST* lt,AST* rt);
};

class BinOp:public AST
{
    public: 
        BinOp();
        BinOp(::token* token,AST* lt,AST* rt):AST(token,lt,rt){};
};

class NUM :public BinOp
{
   public:
        NUM();
        NUM(::token* token):BinOp(token,nullptr,nullptr){}
};

#endif