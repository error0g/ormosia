#include <string>
#ifndef PARSER_LEXER
#define PARSER_LEXER
class Lexer;
using std::string;
/**
 * 词法解析器 
 **/
enum tokenType
{
    TOKEN_EOF,
    TOKEN_FUNCTION,
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
    TOKEN_IDENTIFIER,
    TOKEN_DOUBLE_LITERAL,
    TOKEN_INT_LITERAL,
    TOKEN_STRING_LITERAL,
    TOKEN_LP,
    TOKEN_RP,
    TOKEN_LC,
    TOKEN_RC,
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
    TOKEN_GT,
    TOKEN_GE,
    TOKEN_LT,
    TOKEN_LE,
    TOKEN_INT,
    TOKEN_DOUBLE,
    TOKEN_CHAR,
    TOKEN_VAR,
    TOKEN_BOOL,
};

//token数据结构
struct token
{
    std::string txt;
    tokenType type;
    token *next;
    unsigned int line;
    int pos;
    int endpos;
};

class Lexer
{
private:
    string buffer;
    int index = 0;
    void digitState(token *token);
    void stringState(token *token);
    int line = 1;
    int row = 0;

    /**
     *  字符串处理
     **/
    void consume() //字符索引移动
    {

        const char currentChar = getCurrent();
        if (currentChar == '\n' || currentChar == '\r')
            line++;
        if (index < buffer.length())
            index++;
    };

    char getCurrent() { return buffer[index]; }

    void setTokenAndconsume(token *next, tokenType type)
    {
        setToken(next, type);
        consume();
    }
    //将元素且分开并保存到token
    void setToken(token *next, tokenType type)
    {
        next->type = type;
        next->line = this->line;
    }
    /**
     * token 内存管理
     **/
    token *tokenList = nullptr;
    //TODO 优化成一行代码
    token *newToken()
    {
        token *p = new token();

        if (tokenList == nullptr)
        {
            tokenList = p;
            return p;
        }
        p->next = tokenList;
        tokenList = p;
        return p;
    }
    void freeToken()
    {
        token *p;
        while (tokenList != nullptr)
        {
            p = tokenList->next;
            delete tokenList;
            tokenList = p;
        }
    }

public:
    Lexer(string buffer);
    token *getNextToken(void);
};

#endif
