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
enum INTEGER_TAG{
    INTEGER_TAG_INIT,
    INTEGER_TAG_HEAD_ZERO,
    INTEGER_TAG_ONE_NINE,
    INTEGER_TAG_ONE_ZERO, 
};

map<string,tokenType> rwtab;


Lexer::Lexer(char *buffer)
{
    buff=buffer;
    rwtab[string("function")] = TOKEN_FUNCTION;
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
            index++;
            continue;
        }
        //标识符
        if(isalpha(buff[index])||buff[index]=='_')
        {
            while ((isalpha(buff[index])||isdigit(buff[index]))&&buff[index]!='\0')
            {
                next.txt+=buff[index];
                index++;
            }
          map<string,tokenType>::iterator iter;  
           if((iter = rwtab.find(next.txt))==rwtab.begin()) 
           {
               next.type=rwtab[next.txt];
               return next;
           }
           else{
                next.type=TOKEN_IDENTIFIER;
                return next; 
           }
    
        }
        else if(isdigit(buff[index]))
        {

        }
        switch(buff[index])
        {
            case '(':next.txt+=buff[index];next.type=TOKEN_LP;index++;return next;
            case ')':next.txt+=buff[index];next.type=TOKEN_RP;index++;return next;
            case '{':next.txt+=buff[index];next.type=TOKEN_LC;index++;return next;
            case '}':next.txt+=buff[index];next.type=TOKEN_LC;index++;return next;
            case ';':next.txt+=buff[index];next.type=TOKEN_SEMICOLON;index++;return next;
        }
    }
    next.type=TOKEN_EOF;
    return next;
}



