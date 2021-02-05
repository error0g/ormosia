#include <fstream>
#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AST.hpp"
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
   buffer=new char[length+1];
   buffer[length]='\0';
   infile.read(buffer,length);
   infile.close();


/*-----------------buffer-test-start----------------------*/
   cout<<"------------------------------------------------"<<endl;
   cout<<buffer<<endl;  
   cout<<length<<endl;  
/*-----------------buffer-test-end----------------------*/

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

/*-----------------AST-test-start-----------------------*/
   token* token1=new token();
   token1->txt="1";
   token1->type=TOKEN_INT_LITERAL;
   token* token2=new token();
   token2->txt="2";
   token2->type=TOKEN_INT_LITERAL;

   NUM* num1(token1);
   NUM* num2(token2);
   // token* token3=new token();
   // token1->txt="+";
   // token2->type=TOKEN_ADD;

   // BinOp* op(&token3,&num1,&num2);

   

/*-----------------AST-test-end-----------------------*/
   delete[] buffer;
   return 0;
}