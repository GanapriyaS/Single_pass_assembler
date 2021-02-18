#include <iostream>
using namespace std;
#include "double_hashing.h"
HashMap HashMapTable;
  class sym {
    public:
      string identifier;
      string address;
     sym()
     {
       this->identifier = "";
       this->address = "";
     }
     sym(string key,string address)
      {
          this->identifier = key;
          this->address = address;
      }
      void print()
      {
          cout<<"------------------------------------------------------------\n";
          cout << "IDENTIFIER       "<< "ADDRESS       "<< endl;
          cout<<"------------------------------------------------------------\n";
          cout<<identifier<<"              "<<address<<endl;
      }
      friend class SymbolTable;
};

class SymbolTable {
public:
    sym* head[100];
    SymbolTable()
    {
        for (int i = 0; i < 100; i++)
            head[i] = NULL;
   }
    int convert(string id);
    void insert(string id,string address);
    int find(string id);

    void deletion(string id);
    void modify(string id,string address);
    string add(int index)
    {
      sym* start = head[index];
      return start->address;
    }

};
int SymbolTable::convert(string id)
{
  int asciiSum = 0;

    for (int i = 0; i < id.length(); i++) {
        asciiSum = asciiSum + (char)id[i];
    }
    return asciiSum;
}
void SymbolTable::modify(string id,string no)
{
    int index=-1;
    int i=convert(id);
    index= HashMapTable.search(i);
    if(index!=-1)
    {
      sym* start = head[index];
      if (start != NULL)
      {
      start->address = no;
      }
    }
}

// Function to delete an identifier
void SymbolTable::deletion(string id)
{   int index=-1;
    int i=convert(id);
    index=HashMapTable.deletion(i);
    if (index==-1)
    {
      return;
    }
    else
    {
      head[index]==NULL;
      cout<<"IDENTIFIER "<<id<<" DELETED"<<endl;
    }
}
int SymbolTable::find(string id)
{
    int index=-1;
    int i=convert(id);
    index=HashMapTable.search(i);
    if (index==-1)
    {
      return -1;
    }
    sym* start = head[index];
    if (start == NULL)
    {
      return -1;
    }
    return index;
}
void SymbolTable::insert(string id, string address)
{
    int index=-1;
    int i=convert(id);
    index=HashMapTable.insertion(i);
    if(index!=-1)
    {
      sym* p = new sym(id, address);
      head[index]=p;
    }
}
