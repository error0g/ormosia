
#include "OVM_code.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <assert.h>
#include <streambuf>
#include "OpCodeBuffer.hpp"
using namespace std;

static stack<int> calcula;
static vector<byte> opCode;
static int pc;
void execute()
{
    for (pc = 0; pc < opCode.size(); pc++)
    {

        switch (opCode[pc])
        {

        case OVM_ADD:
        {
            int right = calcula.top();
            calcula.pop();
            int left = calcula.top();
            calcula.pop();
            calcula.push(left + right);
            break;
        }
        case OVM_SUB:
        {
            int right = calcula.top();
            calcula.pop();
            int left = calcula.top();
            calcula.pop();
            calcula.push(left - right);
            break;
        }
        case OVM_MUL:
        {
            int right = calcula.top();
            calcula.pop();
            int left = calcula.top();
            calcula.pop();
            calcula.push(left * right);
            break;
        }
        case OVM_DIV:
        {
            int right = calcula.top();
            calcula.pop();
            int left = calcula.top();
            calcula.pop();
            calcula.push(left / right);
            break;
        }
        case OVM_MOD:
        {
            int right = calcula.top();
            calcula.pop();
            int left = calcula.top();
            calcula.pop();
            calcula.push(left % right);
            break;
        }
        case OVM_PUSH:
        {
            calcula.push(opCode[++pc]);
            break;
        }
        case OVM_PRINT:
        {
            printf("%d \n", calcula.top());
            calcula.pop();
        }
        default:
            break;
        }
    }
}

int main(int argc, char **args)
{
    assert(argc >= 2);
    ifstream inFile(args[1], ios::in | ios::binary);
    assert(inFile.is_open());
    char b;
    while (inFile.peek() != EOF)
    {
        inFile.get(b);
        opCode.push_back(b);
    }
    execute();
    opCode.clear();
    inFile.close();
    return 0;
}