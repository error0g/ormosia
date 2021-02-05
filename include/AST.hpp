#ifndef _AST_
#define _AST_
#include "Lexer.hpp"
#include <string>

class AST
{
    private:

    protected:
        token* token;
    public:
        AST(::token* token);
};

class BinOp :public AST
{
    private:
       AST* left;
       AST* right;
    public: 
        BinOp(::token* token,AST* left,AST* right);
};

class NUM :public AST
{
   public:
        NUM(::token* token);   
};

#endif