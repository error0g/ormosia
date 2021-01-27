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
            case '(':next.txt+=buff[index];next.type=TOKEN_LP;index++;return next;
            case ')':next.txt+=buff[index];next.type=TOKEN_RP;index++;return next;
            case '{':next.txt+=buff[index];next.type=TOKEN_LC;index++;return next;
            case '}':next.txt+=buff[index];next.type=TOKEN_RC;index++;return next;
            case ';':next.txt+=buff[index];next.type=TOKEN_SEMICOLON;index++;return next;
            case '"':index++;StringState(&next);return next;
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
        }
        next->txt+=buff[index];
        index++;
    }
    if(tag==STRING_TAG_OPEN)
    {
        exit(1);
    }
   
}