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
   char *buffer=nullptr;
   infile.seekg(0,std::ios::end);
   length=infile.tellg();
   infile.seekg(0,std::ios::beg);
   buffer=new char[length];
   buffer[length]='\0';
   infile.read(buffer,length);
   infile.close();


/*-----------------buffer-test-start----------------------*/
   cout<<"------------------------------------------------"<<endl;
   cout<<buffer<<endl;  


/*-----------------lexer-test-start-----------------------*/
   cout<<"------------------------------------------------"<<endl;
   Lexer lexerTest=Lexer(buffer);
   token* next=lexerTest.getNextToken();
   while (next->type!=TOKEN_EOF)
   {
      cout<<"<"<<next->txt<<","<<next->type<<">"<<endl;
      next=lexerTest.getNextToken();
   }
/*-----------------lexer-test-end-----------------------*/

/*-----------------Parser-test-start----------------------*/
  cout<<"------------------------------------------------"<<endl;
   Lexer lexer=Lexer(buffer);
   Parser parser(&lexer);
   bool t=parser.parse();
/*-----------------Parser-test-end-----------------------*/


   delete[] buffer;
   return 0;
}