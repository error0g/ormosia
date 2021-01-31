#include <string>
#ifndef _LEXER_
#define _LEXER_
class Lexer;



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

typedef struct token_tag{
    std::string txt;
    tokenType type;
    token_tag* next;
}token;

class Lexer
{
    private:
        char  *buff;
        int index=0;
        token* tokenList;
        void DigitState(token *token);
        void StringState(token *token);
        void TrySplit(token *token,tokenType type);
        int line=1;
        int column=0;
        token* NewToken();
    public:
        Lexer(char *buffer);
        token* getNextToken(void);
        int getLine();
        int getColumn();
        void consume();
        void FreeToken();
};


#endif 
