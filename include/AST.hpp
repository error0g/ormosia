#include"Lexer.hpp"

#ifndef _AST_
#define _AST_

class AST
{

    public:
        AST* left=nullptr;
        AST* right=nullptr;
        AST();
        ::token* token=nullptr;
        AST(::token* token,AST* lt,AST* rt);
};

class BinOp:public AST
{
    public: 
        BinOp();
        BinOp(::token* token,AST* lt,AST* rt):AST(token,lt,rt){}
};

class NUM :public AST
{
   public:
        NUM();
        NUM(::token* token):AST(token,nullptr,nullptr){}
};

#endif