#ifndef _AST_
#define _AST_
#include "Lexer.hpp"

enum NodeType
{
    STATEMENT,
    DEF_FUNCTION,
    DEF_VAR,
};

enum binExpression {
    ADD,
    
};

struct TreeNode
{
    NodeType type;
    TreeNode*  left;
    TreeNode*  right;
    union binExpression{
         
    };
}TreeNode;


#endif