#include "OVM_code.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include "Lexer.hpp"
#include "Parser.hpp"
#include <cstring>
#include <vector>
#include <string>
#include <assert.h>
#include <streambuf>
#include "OpCodeBuffer.hpp"
using namespace std;

static vector<byte> opCode;
void traversalTree(AST *ast)
{
    if (ast == nullptr)
        return;

    switch (ast->token->type)
    {
    case TOKEN_ADD:
    {
        traversalTree(ast->left);
        traversalTree(ast->right);
        opCode.push_back(OVM_ADD);
        break;
    }
    case TOKEN_SUB:
    {
        traversalTree(ast->left);
        traversalTree(ast->right);
        opCode.push_back(OVM_SUB);
        break;
    }
    case TOKEN_MUL:
    {

        traversalTree(ast->left);
        traversalTree(ast->right);
        opCode.push_back(OVM_MUL);
        break;
    }
    case TOKEN_DIV:
    {

        traversalTree(ast->left);
        traversalTree(ast->right);
        opCode.push_back(OVM_DIV);
        break;
    }
    case TOKEN_MOD:
    {
        traversalTree(ast->left);
        traversalTree(ast->right);
        opCode.push_back(OVM_MOD);
        break;
    }
    default:
    {
        opCode.push_back(OVM_PUSH);
        opCode.push_back(atoi(ast->token->txt.c_str()));
    }
    }
}

static void generateCodeToFile(string buffer)
{
    Lexer lexer(buffer);
    Parser parser(&lexer);
    vector<AST *> astList = parser.build();
    for (AST *ast : astList)
    {
        traversalTree(ast);
        opCode.push_back(OVM_PRINT);
    }
    ofstream out(".\\test\\Test.oo", ofstream::out);
    assert(!out.fail());
    //TODO 写文件
    for (byte b : opCode)
    {
        out << b;
    }
    out.close();
}

int main(int argc, char **args)
{

    assert(argc >= 2);
    ifstream inFile(args[1]);
    assert(inFile.is_open());
    string buffer((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    generateCodeToFile(buffer);
    opCode.clear();
}