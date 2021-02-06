#include "AST.hpp"
#include "Lexer.hpp"


 AST::AST(::token* tk,AST* lt,AST* rt)
{
    token=tk;
    left=lt;
    right=rt;
}
