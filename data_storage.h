#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include<map>
using namespace std;
class opcode;
class opcode
{
public:
  map<string,string>code;
  friend class m_opcodeop;
  friend class p_opcodeop;
  friend class branchcode;
  friend class registerr;
};
class m_opcodeop
{

public:
  opcode op;
  void open()
  {
  ifstream fp;
  fp.open("/home/GanapriyaS/Documents/SPOS/1 pass assembler/Machine opcode(MOT).txt");
  string line;
  while(getline(fp,line))
  {
    string s[2];
    string word= "";
    int i=0;
    for (auto x:line)
    {
      if(x==' ')
      {
        s[i]=word;
        word="";
        i++;
      }
      else
      word=word+x;
    }
    s[i]=word;
    op.code[s[0]]=s[1];
  }
  fp.close();
}
};
class p_opcodeop
{

public:
  opcode op1;
  void open()
  {
  ifstream fp;
  fp.open("/home/GanapriyaS/Documents/SPOS/1 pass assembler/Pseudo opcode(POT).txt");
  string line;
  while(getline(fp,line))
  {
    string s[2];
    string word= "";
    int i=0;
    for (auto x:line)
    {
      if(x==' ')
      {
        s[i]=word;
        word="";
        i++;
      }
      else
      word=word+x;
    }
    s[i]=word;
    op1.code[s[0]]=s[1];
  }
  fp.close();
}
};
class registerr
{
public:
  opcode op2;
  void open()
  {
  ifstream fp;
  fp.open("/home/GanapriyaS/Documents/SPOS/1 pass assembler/Registers.txt");
  string line;
  while(getline(fp,line))
  {
    string s[2];
    string word= "";
    int i=0;
    for (auto x:line)
    {
      if(x==' ')
      {
        s[i]=word;
        word="";
        i++;
      }
      else
      word=word+x;
    }
    s[i]=word;
    op2.code[s[0]]=s[1];
  }
  fp.close();
  }
};
class branchcode
{
public:
  opcode op3;
  void open()
  {
  ifstream fp;
  fp.open("/home/GanapriyaS/Documents/SPOS/1 pass assembler/Branchcode.txt");
  string line;
  while(getline(fp,line))
  {
    string s[2];
    string word= "";
    int i=0;
    for (auto x:line)
    {
      if(x==' ')
      {
        s[i]=word;
        word="";
        i++;
      }
      else
      word=word+x;
    }
    s[i]=word;
    op3.code[s[0]]=s[1];
  }
  fp.close();
  }
};
