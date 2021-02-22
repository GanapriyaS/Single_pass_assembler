#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include<map>
using namespace std;
#include "symbol_table.h"
#include "data_storage.h"

m_opcodeop m; //MOT
p_opcodeop p; //POT
opcode l1; //literals
opcode tii; //TII
branchcode b1;
registerr r;
SymbolTable sy;//symboltable
int pooltab[10];
string extnum(string h)
{
  for (int i = 0; i < h.size(); i++)
  {
    if (h[i]< 48 || h[i]>57)
    {
        h.erase(i,1);
        i--;
    }
  }
    return h;
}

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}
string* splitString(string line,int n)
{
  string *s=new string[n];
  string word= "";
  int v=0;
  for (char x:line)
  {
    if(x==' ' && word!="")
    {

      s[v]=word;
      word="";
      if(v<n-1)
      {
      v=v+1;
      }
    }
    if(x!=' ')
    {
    word=word+x;
    }
  }
  s[v]=word;
  return s;
}
string numprint(string h)
{
  for (int i = 0; i < h.size(); i++) {
  if (h[i]< 48 || h[i]>57)
  {
      h.erase(i, 1);
      i--;
  }
}
return h;
}
string literalprint1(string y)
{
  for (int i = 0; i < y.length(); i++) {
  if ((y[i] < 'A' || y[i] > 'Z') && (y[i] < 'a' || y[i] > 'z') && ( y[i]< 48 || y[i]>57))
  {
      y.erase(i, 1);
      i--;
  }
}
return y;
}
string literalprint(string y)
{
  for (int i = 0; i < y.length(); i++)
  {
    if ((y[i] < 'A' || y[i] > 'Z') && (y[i] < 'a' || y[i] > 'z') && ( y[i]< 48 || y[i]>57) && y[i]!='\'')
    {
        y.erase(i, 1);
        i--;
    }
  }
  return y;
}
//pass
void pass()
{
  int v=0;
  ifstream f;
  f.open("/home/GanapriyaS/Documents/SPOS/1 pass assembler/Input.txt");
  ofstream out;
  out.open("Code.txt");
  int n;
  int loc,k=0,o=0;
  string start;
  string line;
  while(getline(f,line))
  {
    n=(line.find("DS")==string::npos && line.find("DC")==string::npos && line.find(":")==string::npos)?2:3;
    string *s=new string[n];
    string word= "";
    s=splitString(line,n);
    int a,b;
    a=(n==3)?1:0;
    b=(n==3)?2:1;
    //label
    if(n==3)
    {
      if(s[0].find(":")!=string::npos)
      {
        if(sy.find(s[0])==-1)
          sy.insert(s[0],to_string(loc));
        else if(sy.find(s[0])!=-1)
          sy.modify(s[0],to_string(loc));
      }
      //DS
      else if(s[1].find("DS")!=string::npos)
      {
        if(sy.find(s[0])==-1)
          sy.insert(s[0],to_string(loc));
        else if(sy.find(s[0])!=-1)
          sy.modify(s[0],to_string(loc));
        string y=s[2];
        y=literalprint(y);
      out<<loc<<") - - ";

      if(isNumber(y))
      {
        out<<"-";
        loc=loc+stoi(y)-1;
      }
      else
      {
        y=literalprint1(y);
      loc=loc+int(y[0])-1;
        if(isNumber(y))
          out<<y;
        else
          out<<int(y[0]);
      }
      }

      //DC
      else if(s[1].find("DC")!=string::npos)
      {
        string y=s[2];
        y=literalprint(y);
        if(sy.find(s[0])==-1)
          sy.insert(s[0],to_string(loc));
        else if(sy.find(s[0])!=-1)
          sy.modify(s[0],to_string(loc));
        out<<loc<<") - - ";
        if(isNumber(y))
        {
          out<<'0' + stoi(y);
        }
        else
        {
            y=literalprint1(y);
            if(isNumber(y))
              out<<y;
            else
              out<<int(y[0]);
        }
      }
    }
    //start of program
    if(s[a]=="START")
    {
      start=s[b];
      out<<"01"<<" - "<<start;
      loc=stoi(start)-1;
    }
    //end or ltorg
    else if(s[a]=="END" || s[a]=="LTORG")
    {
      out<<loc<<") -"<<" - ";
      int h=0;
      for(auto const& [key,val]:l1.code)
      {
        if(h<k)
        {
          h++;
          continue;
        }
        if(h!=k)
          out<<"\n"<<loc<<") -"<<" - ";
        l1.code[key]=to_string(loc);
        string s=key;
        s=literalprint(s);
        if(isNumber(s))
        {
          out<<'0' + stoi(s);
        }
        else
        {
          s=literalprint1(s);
          if(isNumber(s))
            out<<s;
          else
            out<<stoi(s);
        }
        if(h!=o)
        {
        loc++;
      }
      if(h==o)
        break;
        h++;
      }
      k=o;
      if(s[a]=="END")
      {
        out<<"-";
        break;
      }

    }
    //invalid nmenomics
    else if(p.op1.code.find(s[a])==p.op1.code.end() && m.op.code.find(s[a])==m.op.code.end() && (line.find("DS")==string::npos && line.find("DC")==string::npos))
      cout<<"INVALID NMEMONICS";
    else if(line.find("DS")==string::npos && line.find("DC")==string::npos)
    {
      if(p.op1.code.find(s[a])!=p.op1.code.end()){out<<loc<<") "<<p.op1.code[s[a]]<<" ";}
      else if(m.op.code.find(s[a])!=m.op.code.end()){out<<loc<<") "<<m.op.code[s[a]]<<" ";}

      if(s[b]!="" && s[b].find(',')!=string::npos)
      {
        vector<string>v1;
        word="";
        for (auto x:s[b])
        {
          if(x==',' && word!="")
          {
            v1.push_back(word);
            word="";
          }
          if(x!=',')
          word=word+x;
        }
        v1.push_back(word);
        int cc=0;
        for(int i=0;i<v1.size();i++)
        {
    if(r.op2.code.find(v1[0])== r.op2.code.end() && cc==0)
    {
      out<<"- ";
      cc++;
    }
    if(r.op2.code.find(v1[i])== r.op2.code.end())
    {
        if(b1.op3.code.find(v1[i])== b1.op3.code.end())
        {
          if(s[b].find("=")!=string::npos)
          {
            string h=to_string(loc);
            if(l1.code.find(v1[i])==l1.code.end() )
                {
                  l1.code[v1[i]]=h;
                  o++;
                 out<<"--";
                  }
            else if(l1.code.find(v1[i])!=l1.code.end() )
            {
              out<<"--";
            }
            tii.code[h]=v1[i];
          }
          else
          {
            string h=to_string(loc);
            tii.code[h]=v1[i];
            int len=v1[i].length();
            char a[len+1];
            strcpy(a,v1[i].c_str());
            int zz=0,yy=0;
            for(auto x : a)
            {
              if(isalpha(x)!=0)
                zz++;
              if(isdigit(x)!=0)
                yy++;
            }
            if(zz==v1[i].length())
            {
                if(sy.find(v1[i])==-1)
                {
                  sy.insert(v1[i],"");
                  out<<"--";
                }
                else if(sy.find(v1[i])!=-1)
                  out<<"--";
            }
            else
            {
              out<<"--";
            }
        }


      }
        else if(b1.op3.code.find(v1[i])!= b1.op3.code.end())
        {
          out<<b1.op3.code[v1[i]]<<" ";
        }
    }
    else if(r.op2.code.find(v1[i])!= r.op2.code.end())
    {
      out<<r.op2.code[v1[i]]<<" ";
    }
  }
        }
      if(s[b]!="" && s[b].find(',')==string::npos)
      {
        if(r.op2.code.find(s[b])== r.op2.code.end())
        {
          out<<"- ";
        }
        if(r.op2.code.find(s[b])== r.op2.code.end())
        {
            if(b1.op3.code.find(s[b])== b1.op3.code.end())
            {
              if(s[b].find("=")!=string::npos)
              {
                string h=to_string(loc);
                if(l1.code.find(s[b])==l1.code.end() )
                    {
                      l1.code[s[b]]=h;
                      o++;
                     out<<"--";
                      }
                else if(l1.code.find(s[b])!=l1.code.end() )
                  out<<"--";
                tii.code[h]=s[b];
              }
              else
              {
                string h=to_string(loc);
                tii.code[h]=s[b];
                int len=s[b].length();
                char a[len+1];
                strcpy(a,s[b].c_str());
                int zz=0,yy=0;
                for(auto x : a)
                {
                  if(isalpha(x)!=0)
                    zz++;
                  if(isdigit(x)!=0)
                    yy++;
                }
                if(zz==s[b].length())
                {
                    if(sy.find(s[b])==-1)
                    {
                      sy.insert(s[b],"");
                      out<<"--";
                    }
                    else if(sy.find(s[b])!=-1)
                      out<<"--";
                }
                else
                {
                  out<<"--";
                }
            }

          }
            else if(b1.op3.code.find(s[b])!= b1.op3.code.end())
            {
              out<<b1.op3.code[s[b]]<<" ";
            }
        }
        else if(r.op2.code.find(s[b])!= r.op2.code.end())
        {
          out<<r.op2.code[s[b]]<<" ";
        }
      }
    }
    loc++;
    out<<endl;
  }
  out.close();
  f.close();
}
//forward reference
void backpatching()
{
  ifstream f;
  f.open("Code.txt");
  ofstream out;
  out.open("Machine code.txt");
  int j=0;
  string line;
  int v=0;
  while(getline(f,line))
  {
    string *s=new string[4];
    string word= "";
    s=splitString(line,4);
    out<<s[0]<<" "<<s[1]<<" "<<s[2];
    if(s[3].find("--")!=string::npos)
    {

      int pos=s[0].find(')');
      string k=tii.code[s[0].substr(0,pos)];
      if(sy.find(k)!=-1)
        out<<" "<<sy.head[sy.find(k)]->address;
      if(l1.code.find(k)!=l1.code.end() )
        out<<" "<<l1.code[k];
      }
    else
    out<<" "<<s[3];
out<<endl;
}
out.close();
f.close();
}

int main()
{
  p.open();
  m.open();
  r.open();
  b1.open();
  pass();
  backpatching();
  ifstream f;
  f.open("Input.txt");
  string str="";
  if(f)
  {
    ostringstream ss;
    ss << f.rdbuf();
    str = ss.str();
  }
  cout<<"\nINPUT FILE\n"<<endl;
  cout<<str;
  f.close();

  cout<<"\n\nMACHINE CODE FILE\n"<<endl;
  f.open("Machine code.txt");
  str="";
  if(f)
  {
    ostringstream ss;
    ss << f.rdbuf();
    str = ss.str();
  }
  cout<<str;
  f.close();
  cout<<endl;
  return 0;
}
