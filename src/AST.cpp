#include "AST.hpp"

void AST::AST(::token* tk)
{
    token=tk;
}

void BinOp::BinOp(::token tk,AST* lt,AST* rt)
{
    token=tk;
    left=lt;
    right=rt;
} 
NUM::NUM(::token* tk)
{
    token=tk;
}