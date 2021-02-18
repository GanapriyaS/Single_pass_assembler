#include <iostream>
using namespace std;
class HashMap{
   private:
      int *hash;
      bool*flag;
      int curr_size;
      int R;
   public:
      int size=100;
      HashMap() {
        curr_size=0;
        // cout<<"ENTER THE SIZE OF THE HASH TABLE:";
        // cin>>size;
        cout<<"ENTER THE VALUE OF R (PRIME NOS ONLY):";
        cin>>R;
         hash = new int[size];
         for (int i = 0; i < size; i++)
            hash[i]=0;
         flag=new bool[size];
         for (int i = 0; i < size; i++)
            flag[i]=true;
      }
      int HashFunc1(int k) {
         return k % size;
      }
      int HashFunc2(int k) {
         return R-(k%R);
      }
      int probe(int k)
      {
        int index1=HashFunc1(k);
        int i=0;
        int index2=HashFunc2(k);
        while(flag[(index1+i* index2)%size]!=true)
        {
          i++;
          if(i>=size)
          return -1;
        }
        return (index1+i* index2)%size;
      }
      int insertion(int k)
      {
        if (curr_size==size)
        {
          cout<<"FULL MEMORY!!!!\n";
          return -1;
        }
         int index=HashFunc1(k);
         if(flag[index]!=true )
          index=probe(k);
          if(index==-1)
          {
            cout<<"INSERATION FAILED!!!!\n";
            return -1;
          }
          hash[index]=k;
         flag[index]=false;
         curr_size++;
         return index;
      }
      int search(int k) {
         int index1=HashFunc1(k);
         int index2=HashFunc2(k);
         int i=0;
         while(hash[(index1 +i*index2)%size]!=k && flag[(index1 +i* index2)%size]==false)
         {
            i++;
           if(i>=size)
           {
           return -1;
            }
         }
         if(flag[(index1 +i*index2)%size]==true)
         return -1;
         if(hash[(index1 +i*index2)%size]==k)
         return (index1 +i*index2)%size;
         return -1;
      }
      int deletion(int k) {
         int index=search(k);
         if(index==-1)
         {
           cout<<"NOT FOUND\n";
           return -1;
         }
        flag[index]=true;
        curr_size--;
        return index;
      }
      void rehash()
      {
          curr_size=0;
          cout<<"ENTER THE SIZE OF THE ARRAY:";
          cin>>size;
          bool *temp_flag=new bool[size];
          int *hashtable=new int[size];
          hash=hashtable;
          delete[] hashtable;
          flag=temp_flag;
          delete[] temp_flag;
          for (int i = 0; i < size; i++)
             flag[i]=true;
      }
      void display()
      {
        int i=0;
        for(;i<size;i++)
        {
          if(flag[i]==false)
            cout<<hash[i]<<" ";
          else
            cout<<"-"<<" ";
        }
        cout<<endl;
      }
      ~HashMap() {
         delete[] hash;
         delete[] flag;
      }
};
