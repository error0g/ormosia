#include <string>
#ifndef _LEXER_
#define _LEXER_
class Lexer;



enum tokenType
{
    TOKEN_EOF=-1,
    TOKEN_FUNCTION,     //函数
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSEIF,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_FOREACH,
    TOKEN_RETURN_T,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_NULL_T,
    TOKEN_TRUE_T,
    TOKEN_FALSE_T,
    TOKEN_IDENTIFIER,   //标识符
    TOKEN_DOUBLE_LITERAL, //小数
    TOKEN_INT_LITERAL, //整数
    TOKEN_STRING_LITERAL, //字符串
    TOKEN_LP, //(
    TOKEN_RP,// )
    TOKEN_LC,//{
    TOKEN_RC,//}
    TOKEN_SUB,
    TOKEN_ADD,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_DOT,
    TOKEN_NE,
    TOKEN_EQ,
    TOKEN_COMMA,
    TOKEN_LOGICAL_AND,
    TOKEN_LOGICAL_OR,
    TOKEN_SEMICOLON,
    TOKEN_ASSIGN_T,
    TOKEN_ADD_ASSIGN_T,
    TOKEN_SUB_ASSIGN_T,
    TOKEN_MUL_ASSIGN_T,
    TOKEN_DIV_ASSIGN_T,
    TOKEN_MOD_ASSIGN_T,
    TOKEN_INCREMENT,
    TOKEN_DECREMENT,
    TOKEN_EXCLAMATION,
};

typedef struct token_tag{
    std::string txt;
    tokenType type;
}token;

class Lexer
{
    private:
        char  *buff;
        int index=0;
        void DigitState(token *token);
        void StringState(token *token);
        void TrySplit(token *token,tokenType type);
    public:
        Lexer(char *buffer);
        token getNextToken(void);
};

#endif 