#include <iostream>
#include <string>
#include "Lexer.hpp"
#include <stdio.h>
#include <map>
using std::cout;
using std::endl;
using std::map;
using std::string;
//整数
enum DIGIT_TAG
{
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

static map<string, tokenType> keyWordTab;

Lexer::Lexer(string buffer)
{
    this->buffer = buffer;
    keyWordTab[string("function")] = TOKEN_FUNCTION;
    keyWordTab[string("var")] = TOKEN_VAR;
    keyWordTab[string("int")] = TOKEN_INT;
    keyWordTab[string("double")] = TOKEN_DOUBLE;
    keyWordTab[string("char")] = TOKEN_CHAR;
    keyWordTab[string("bool")] = TOKEN_BOOL;
    keyWordTab[string("if")] = TOKEN_IF;
    keyWordTab[string("else")] = TOKEN_ELSE;
    keyWordTab[string("elseif")] = TOKEN_ELSEIF;
    keyWordTab[string("for")] = TOKEN_FOR;
    keyWordTab[string("while")] = TOKEN_WHILE;
    keyWordTab[string("break")] = TOKEN_BREAK;
    keyWordTab[string("true")] = TOKEN_TRUE_T;
    keyWordTab[string("false")] = TOKEN_FALSE_T;
    keyWordTab[string("continue")] = TOKEN_CONTINUE;
    keyWordTab[string("null")] = TOKEN_NULL_T;
    keyWordTab[string("return")] = TOKEN_RETURN_T;
}

token *Lexer::getNextToken(void)
{

    token *next = newToken();
    char currentCharacter = getCurrent();
    while (currentCharacter != '\0')
    {
        if (currentCharacter == '\n' || currentCharacter == '\r' || currentCharacter == '\t' || currentCharacter == ' ')
        {
            consume();
            currentCharacter = getCurrent();
            continue;
        }
        //标识符 or 关键字
        //字母开头 或 _ 开头认为是标识符 纯字母需要到关键字表查询类型方便语义分析阶段。
        if (isalpha(currentCharacter) || currentCharacter == '_')
        {
            do
            {
                next->txt += currentCharacter;
                consume();
            } while ((isalpha(currentCharacter) || isdigit(currentCharacter)) && currentCharacter != '\0');

            map<string, tokenType>::iterator iter = keyWordTab.find(string(next->txt));
            if (iter != keyWordTab.end())
            {
                setToken(next, keyWordTab[next->txt]);
                next->type = keyWordTab[next->txt];
                return next;
            }
            setToken(next, TOKEN_IDENTIFIER);
            return next;
        }

        //数字
        if (isdigit(currentCharacter))
        {
            digitState(next);
            return next;
        }
        //字符串
        if (currentCharacter == '"')
        {
            stringState(next);
            return next;
        }
        next->txt = currentCharacter;
        switch (currentCharacter)
        {
        case '(':
            setTokenAndconsume(next, TOKEN_LP);
            return next;
        case ')':
            setTokenAndconsume(next, TOKEN_RP);
            return next;
        case '{':
            setTokenAndconsume(next, TOKEN_LC);
            return next;
        case '}':
            setTokenAndconsume(next, TOKEN_RC);
            return next;
        case ';':
            setTokenAndconsume(next, TOKEN_SEMICOLON);
            return next;
        case '=':
        {
            setTokenAndconsume(next, TOKEN_ASSIGN_T);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
            {
                next->txt += getCurrent();
                setTokenAndconsume(next, TOKEN_EQ);
                break;
            }
            }
            return next;
        }
        case '+':
        {
            setTokenAndconsume(next, TOKEN_ADD);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '+':
                next->txt += getCurrent();
                setTokenAndconsume(next, TOKEN_INCREMENT);
                break;
            case '=':
                next->txt += getCurrent();
                setTokenAndconsume(next, TOKEN_ADD_ASSIGN_T);
                break;
            }
            return next;
        }
        case '-':
        {
            setTokenAndconsume(next, TOKEN_SUB);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '-':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_DECREMENT);
                break;
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_SUB_ASSIGN_T);
                break;
            }
            return next;
        }
        case '*':
        {
            setTokenAndconsume(next, TOKEN_MUL);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_MUL_ASSIGN_T);
                break;
            }
            return next;
        }
        case '/':
        {
            setTokenAndconsume(next, TOKEN_DIV);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_DIV_ASSIGN_T);
                break;
            }
            return next;
        }
        case '%':
        {
            setTokenAndconsume(next, TOKEN_MOD);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_MOD_ASSIGN_T);
                break;
            }
            return next;
        }
        case '!':
        {
            setTokenAndconsume(next, TOKEN_EXCLAMATION);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_NE);
                break;
            }
            return next;
        }
        case '>':
        {
            setTokenAndconsume(next, TOKEN_GT);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_GE);
                break;
            }
            return next;
        }
        case '<':
        {
            setTokenAndconsume(next, TOKEN_LT);
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '=':
                next->txt += currentCharacter;
                setTokenAndconsume(next, TOKEN_LE);
                break;
            }
            return next;
        }
        case '|':
        {
            consume();
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '|':
                next->txt += currentCharacter;
                setToken(next, TOKEN_LOGICAL_OR);
                break;
            default:
                exit(1);
            }
            return next;
        }
        case '&':
        {
            consume();
            currentCharacter = getCurrent();
            switch (currentCharacter)
            {
            case '&':
                next->txt += currentCharacter;
                setToken(next, TOKEN_LOGICAL_AND);
                break;
            default:
                exit(1);
            }
            return next;
        }
        default:
        {
            cout << "错误:" << next->txt << "#" << next->type << endl;
            cout << "代码:" << line << "index:" << index << endl;
            exit(1);
        }
        }
    }
    //EOF
    setToken(next, TOKEN_EOF);
    return next;
}

void Lexer::digitState(token *next)
{

    DIGIT_TAG tag;
    do
    {
        tag = DIGIT_TAG_INI;
        next->txt += getCurrent();
        consume();
    } while (getCurrent() != '\0' && isdigit(getCurrent()));

    //小数点匹配
    if (getCurrent() == '.' && tag == DIGIT_TAG_INI)
    {
        tag = DIGIT_TAG_INT_POINT;
        next->txt += getCurrent();
        consume();
    }
    //
    if (tag == DIGIT_TAG_INT_POINT && isdigit(getCurrent()))
    {
        do
        {
            tag = DIGIT_TAG_INT_DOUBLE;
            next->txt += getCurrent();
            consume();
        } while (isdigit(getCurrent()));
    }

    switch (tag)
    {
    case DIGIT_TAG_INI:
        setToken(next, TOKEN_INT_LITERAL);
        break;
    case DIGIT_TAG_INT_DOUBLE:
        setToken(next, TOKEN_DOUBLE_LITERAL);
        break;
    default:
        exit(1);
    }
}

void Lexer::stringState(token *next)
{
    consume(); //跳过 " 只需要字符串内容

    STRING_TAG tag = STRING_TAG_OPEN;
    while (getCurrent() != '\0')
    {
        //空字符串
        if (tag == STRING_TAG_OPEN && getCurrent() == '"')
        {
            setToken(next, TOKEN_STRING_LITERAL);
            return;
        }
        switch (getCurrent())
        {
        case '\n':
            next->txt += '\n';
            consume();
            continue;
        //转义
        case '\\':
        {
            consume();
            switch (getCurrent())
            {
            case 'n':
                next->txt += '\n';
                break;
            case '\\':
                next->txt += '\\';
                break;
            case '\'':
                next->txt += '\'';
                break;
            case 't':
                next->txt += '\t';
                break;
            case '\"':
                next->txt += '\"';
                break;
            default:
                exit(1);
            }
            break;
        }
        default:
            next->txt += getCurrent();
        }
        consume();
    }
    if (tag == STRING_TAG_OPEN)
    {
        exit(1);
    }
}
