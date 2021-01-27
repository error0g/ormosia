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
    rwtab[string("int")] = TOKEN_INT_LITERAL;
    rwtab[string("double")] = TOKEN_DOUBLE_LITERAL;
    rwtab[string("if")] =  TOKEN_IF;
    rwtab[string("for")] =  TOKEN_FOR;
}

token Lexer::getNextToken(void)
{
    token next;
    
    while(buff[index]!='\0')
    {
        //空格
        if(buff[index]==' ')
        {
            index++;
            continue;
        }
        // 处理换行符
        if(buff[index]=='\n'||buff[index]=='\t')
        {
            // lineNum++;
            index++;
            continue;
        }
        //标识符 or 关键字
        if(isalpha(buff[index])||buff[index]=='_')
        {

            do{
                next.txt+=buff[index];
                index++;
            }
            while ((isalpha(buff[index])||isdigit(buff[index]))&&buff[index]!='\0');
            map<string,tokenType>::iterator iter = rwtab.find(string(next.txt));  
           if(iter!=rwtab.end()) 
           {
               next.type=rwtab[next.txt];
               return next;
           }
           else{
                next.type=TOKEN_IDENTIFIER;
                return next; 
           }
    
        }
        //数字
        if(isdigit(buff[index]))
        {
            DigitState(&next);
            return next;
        }

        switch(buff[index])
        {
            case '(':TrySplit(&next,TOKEN_LP);return next;
            case ')':TrySplit(&next,TOKEN_RP);return next;
            case '{':TrySplit(&next,TOKEN_LC);return next;
            case '}':TrySplit(&next,TOKEN_RC);return next;
            case ';':TrySplit(&next,TOKEN_SEMICOLON);return next;
            case '"':index++;StringState(&next);return next;
            case '=':
            {
                TrySplit(&next,TOKEN_ASSIGN_T);
                switch (buff[index])
                {
                  case '=':
                  {
                    TrySplit(&next,TOKEN_EQ);break;
                  }
                }
                return next;
            }
            case '+':{
                TrySplit(&next,TOKEN_ADD);
                switch (buff[index])
                {
                    case '+': TrySplit(&next,TOKEN_INCREMENT);break;
                    case '=': TrySplit(&next,TOKEN_ADD_ASSIGN_T);break;
                }
               return next;
            }

        
            default:{exit(1);}
        }
    }

    //EOF
    next.type=TOKEN_EOF;
    return next;
}

void Lexer::DigitState(token *next)
{   
  
    DIGIT_TAG tag;
    do{
       tag=DIGIT_TAG_INI;
       next->txt+=buff[index];
       index++;
    }
    while (isdigit(buff[index]));
    
    if(buff[index]=='.'&&tag==DIGIT_TAG_INI)
    {
        tag=DIGIT_TAG_INT_POINT;
        next->txt+=buff[index];
        index++;
    }
  
    
    if(tag==DIGIT_TAG_INT_POINT&&isdigit(buff[index]))
    {
        do{
            tag=DIGIT_TAG_INT_DOUBLE;
            next->txt+=buff[index];
            index++;
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
            index++;
            next->type=TOKEN_STRING_LITERAL;
            return ;
        }
        switch (buff[index])
        {
            case '\n':
            next->txt+='\n';index++;continue;
            case '\\':
            {   
                index++;
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
        index++;
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
    index++;
}