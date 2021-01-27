#include <string>
#ifndef _LEXER_
#define _LEXER_
class Lexer;



enum tokenType
{
    TOKEN_EOF=-1,
    TOKEN_FUNCTION,     //函数
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
    TOKEN_SEMICOLON
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
    
    public:
        Lexer(char *buffer);
        token getNextToken(void);
};

#endif 