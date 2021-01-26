#include <fstream>
#include <iostream>
#include "Lexer.hpp"
#include "ORMO.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

int main(int argc,char  **args)
{   

   if(argc!=2)
   {
    cout<<"args is error"<<endl;
    return -1;
   }
   
   ifstream infile;
   infile.open(args[1]);
   if(!infile.is_open())
   {
     cout<<args[1]<<":file is error"<<endl;
     return -1;
   }
   int length;
   char *buffer;
   infile.seekg(0,std::ios::end);
   length=infile.tellg();
   infile.seekg(0,std::ios::beg);
   buffer=new char[length];
   infile.read(buffer,length);
   infile.close();

   Lexer lexer=Lexer(buffer);
   token *token=lexer.getNextToken();

   return 0;
}