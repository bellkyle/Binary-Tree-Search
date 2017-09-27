#include "tree.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
   BinaryTree tree;
   string name;
   int count;
   int rank;
   float percentage;
   string fileName;
   cout << "Enter the name a the file" << endl;
   cin >> fileName;
   ifstream din;
   din.open(fileName.c_str());
   if(!din)
   {
      cout << "Could not open the file" << endl;
      return -1;
   }
   while(!din.eof())
   {
      din >> name;
      din >> count;
      din >> percentage;
      din >> rank;
      tree.Insert(name, count, rank, percentage);
   }
   din.close();
   while (name != "quit")
   {
      cout << "Enter a name to search or enter 'quit' to exit the program" << endl;
      cin >> name;
      if(name != "quit")
      {
         if(!tree.Search(name))
            cout << "Did not find the name" << endl;
      }
   }
   tree.Print();
}
