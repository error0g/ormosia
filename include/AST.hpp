#ifndef _AST_
#define _AST_
#include "Lexer.hpp"
#include<string>



enum binExpression {
    ADD,
    
};

struct TreeNode
{
    string value;
    TreeNode*  left;
    TreeNode*  right;
    union binExpression{
         
    };
}TreeNode;


#endif