#include <fstream>
#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
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

   /* 读取文件*/
   int length;
   char *buffer;
   infile.seekg(0,std::ios::end);
   length=infile.tellg();
   infile.seekg(0,std::ios::beg);
   buffer=new char[length];
   infile.read(buffer,length);
   infile.close();

/*------------------test-start----------------------*/
   Lexer lexer=Lexer(buffer);
   Parser parser(&lexer);
   bool t=parser.parse();
   cout<<t;
 

/*------------------test-end-----------------------*/
   return 0;
}