#include <iostream>
#include <string>
#include "Lexer.hpp"
#include <stdio.h>
using std::cout;
using std::endl;

//整数
enum INTEGER_TAG{
    INTEGER_TAG_INIT,
    INTEGER_TAG_HEAD_ZERO,
    INTEGER_TAG_ONE_NINE,
    INTEGER_TAG_ONE_ZERO, 
};

Lexer::Lexer(char *buffer)
{
    buff=buffer;
}

token* Lexer::getNextToken(void)
{
    token *next=(token *) malloc(sizeof(token_tag));

    while(LL(1)!=EOF)
    {
        //空格
        if(LL(1)==' ')
        {
            consume();
            continue;
        }
        // 处理换行符
        if(LL(1)=='\n'||LL(1)=='\t')
        {
            lineNum++;
            consume();
            continue;
        }
       if(isdigit(LL(1)))
       {
            consume();
       }
      
       switch(LL(1))
       {
           case '"': break;
           case 'f':
           case '(':
           case  ')':
           case '{':
           case '}':
       }

    }
    return next;
}



void Lexer::consume()
{
    if(index>buff.size())
    {
        cout<<"error:index exceed:"<<index;
        cout<<endl;
        return;
    }
    index++;
}



char Lexer::LL(int k)
{
    if(index+k-1>buff.size()||buff[k]=='\0')
    {
        return EOF;
    }

    retrun buff[index+k-1];
}