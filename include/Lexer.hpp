#include <string>
#include "ORMO.hpp"
#ifndef _LEXER_
#define _LEXER_
class Lexer;

enum tokenType
{
    EOF(-1),
    FUNCTION,     //函数
    IDENTIFIER,   //标识符
    DOUBLE_LITERAL, //小数
    INT_LITERAL, //整数
    STRING_LITERAL, //字符串
    LP, //(
    RP,// )
    LC,//{
    RC,//}
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
        void consume();
        char LL(int k);
    
    public:
        Lexer(char *buffer);
        token* getNextToken(void);
};

#endif 