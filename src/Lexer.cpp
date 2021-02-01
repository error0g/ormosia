#include <iostream>
#include <string>
#include "Lexer.hpp"
#include <stdio.h>
#include <map>
using std::cout;
using std::endl;
using std::string;
using std::map;
//整数
enum DIGIT_TAG{
    DIGIT_TAG_INI,
    DIGIT_TAG_INT_POINT,
    DIGIT_TAG_INT_DOUBLE, 
};
//字符串
enum STRING_TAG
{
     STRING_TAG_OPEN,
     STRING_TAG_CLOSE,
};

map<string,tokenType> rwtab;


Lexer::Lexer(char *buffer)
{
    buff=buffer;
    rwtab[string("function")] = TOKEN_FUNCTION;
    rwtab[string("var")] = TOKEN_VAR;
    rwtab[string("int")] = TOKEN_INT;
    rwtab[string("double")] = TOKEN_DOUBLE;
    rwtab[string("char")] = TOKEN_CHAR;
    rwtab[string("bool")] = TOKEN_BOOL;
    rwtab[string("if")] =  TOKEN_IF;
    rwtab[string("else")] =  TOKEN_ELSE;
    rwtab[string("elseif")] =  TOKEN_ELSEIF;
    rwtab[string("for")] =  TOKEN_FOR;
    rwtab[string("while")] =  TOKEN_WHILE;
    rwtab[string("break")] =  TOKEN_BREAK;
    rwtab[string("true")] =  TOKEN_TRUE_T;
    rwtab[string("false")] =  TOKEN_FALSE_T;
    rwtab[string("continue")] =  TOKEN_CONTINUE;
    rwtab[string("null")] =  TOKEN_NULL_T;
    rwtab[string("return")] =  TOKEN_RETURN_T;
}

token* Lexer::getNextToken(void)
{
    token* next=NewToken();

    while(buff[index]!='\0')
    {
        
      
        if(buff[index]=='\n'||buff[index]=='\r'||buff[index]=='\t'||buff[index]==' ')
        {
           
            consume();
            continue;
        }
        //标识符 or 关键字
        if(isalpha(buff[index])||buff[index]=='_')
        {

            do{
                next->txt+=buff[index];
                consume();
            }
            while ((isalpha(buff[index])||isdigit(buff[index]))&&buff[index]!='\0');
            map<string,tokenType>::iterator iter = rwtab.find(string(next->txt));  
           if(iter!=rwtab.end()) 
           {
               next->type=rwtab[next->txt];
               return next;
           }
           else{
                next->type=TOKEN_IDENTIFIER;
                return next; 
           }
    
        }
        //数字
        if(isdigit(buff[index]))
        {
            DigitState(next);
            return next;
        }

        switch(buff[index])
        {
            case '(':TrySplit(next,TOKEN_LP);return next;
            case ')':TrySplit(next,TOKEN_RP);return next;
            case '{':TrySplit(next,TOKEN_LC);return next;
            case '}':TrySplit(next,TOKEN_RC);return next;
            case ';':TrySplit(next,TOKEN_SEMICOLON);return next;
            case '"':consume();StringState(next);return next;
            case '=':
            {
                TrySplit(next,TOKEN_ASSIGN_T);
                switch (buff[index])
                {
                  case '=':
                  {
                    TrySplit(next,TOKEN_EQ);break;
                  }
                }
                return next;
            }
            case '+':{
                TrySplit(next,TOKEN_ADD);
                switch (buff[index])
                {
                    case '+': TrySplit(next,TOKEN_INCREMENT);break;
                    case '=': TrySplit(next,TOKEN_ADD_ASSIGN_T);break;
                }
               return next;
            }
            case '-':{
                TrySplit(next,TOKEN_SUB);
                switch (buff[index])
                {
                    case '-': TrySplit(next,TOKEN_DECREMENT);break;
                    case '=': TrySplit(next,TOKEN_SUB_ASSIGN_T);break;
                }
               return next;
            }
            case '*':{
                TrySplit(next,TOKEN_MUL);
                switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_MUL_ASSIGN_T);break;
                }
               return next;
            }
           case '/':{
                TrySplit(next,TOKEN_DIV);
                switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_DIV_ASSIGN_T);break;
                }
               return next;
            }
           case '%':{
                TrySplit(next,TOKEN_MOD);
                switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_MOD_ASSIGN_T);break;
                }
               return next;
            }
          case '!':{
               TrySplit(next,TOKEN_EXCLAMATION);
               switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_NE);break;
                }
               return next;
          }
          case '>':{
               TrySplit(next,TOKEN_GT);
               switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_GE);break;
                }
               return next;
          }
          case '<':{
               TrySplit(next,TOKEN_LT);
               switch (buff[index])
                {
                    case '=': TrySplit(next,TOKEN_LE);break;
                }
               return next;
          }
          case '|':{
               consume();
               switch (buff[index])
                {
                    case '|': TrySplit(next,TOKEN_LOGICAL_OR);break;
                    default:exit(1);
                }
               return next;
          }
          case '&':{
               consume();
               switch (buff[index])
                {
                    case '&': TrySplit(next,TOKEN_LOGICAL_AND);break;
                    default:exit(1);
                }
               return next;
          }
            default:{exit(1);}
        }
    }

    //EOF
    next->type=TOKEN_EOF;
    return next;
}

void Lexer::DigitState(token *next)
{   
  
    DIGIT_TAG tag;
    do{
       tag=DIGIT_TAG_INI;
       next->txt+=buff[index];
       consume();
    }
    while (isdigit(buff[index]));
    
    if(buff[index]=='.'&&tag==DIGIT_TAG_INI)
    {
        tag=DIGIT_TAG_INT_POINT;
        next->txt+=buff[index];
        consume();
    }
  
    
    if(tag==DIGIT_TAG_INT_POINT&&isdigit(buff[index]))
    {
        do{
            tag=DIGIT_TAG_INT_DOUBLE;
            next->txt+=buff[index];
            consume();
          }
          while (isdigit(buff[index]));
     
    }


    if(tag==DIGIT_TAG_INI)
    {
        next->type=TOKEN_INT_LITERAL;
    }
    else if(tag==DIGIT_TAG_INT_DOUBLE)
    {
        next->type=TOKEN_DOUBLE_LITERAL;
    }
    else {
         exit(1);
    }
}


void Lexer::StringState(token *next)
{

    STRING_TAG tag=STRING_TAG_OPEN;
    
    while (buff[index]!='\0')
    {
      if(tag==STRING_TAG_OPEN&&buff[index]=='"')
        {
            tag=STRING_TAG_CLOSE;
            consume();
            next->type=TOKEN_STRING_LITERAL;
            return ;
        }
        switch (buff[index])
        {
            case '\n':
            next->txt+='\n';consume();continue;
            //转义
            case '\\':
            {   
                consume();
                switch (buff[index])
                {
                    case 'n':next->txt+='\n'; break;
                    case '\\':next->txt+='\\'; break;
                    case '\'':next->txt+='\''; break;
                    case 't':next->txt+='\t'; break;
                    case '\"':next->txt+='\"'; break;
                default:
                    exit(1);
                }
                break;
            }
            default:
                next->txt+=buff[index];
        }
        consume();
    }
    if(tag==STRING_TAG_OPEN)
    {
        exit(1);
    }
   
}

void Lexer::TrySplit(token *next,tokenType type)
{
    next->txt+=buff[index];
    next->type=type;
    consume();
}
void Lexer::consume()
{

    if(buff[index]=='\n'||buff[index]=='\r')
    {
        column=0;
        line++;
    }
    else column++;
    
    index++;
}

int Lexer::getLine()
{
    return line; 
}
int Lexer::getColumn()
{
    return column; 
}

token* Lexer::NewToken()
{
    token* p=new token();

    if(tokenList==nullptr)
    {
        tokenList=p;
        return p;
    }

    p->next=tokenList;
    tokenList=p;
    return p;
}

void Lexer::FreeToken()
{
    token* p;
    while (tokenList!=nullptr)
    {
        p=tokenList->next;
        delete tokenList;
        tokenList=p;
    }
}