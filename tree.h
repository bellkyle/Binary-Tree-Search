//-----------------------------------------------------------
//  Purpose:    Header file for the BinaryTree class.
//  Author:     John Gauch
//-----------------------------------------------------------

#include <iostream>
#include <fstream>
using namespace std;

//-----------------------------------------------------------
// BinaryTree data node definition
//-----------------------------------------------------------
class Node
{
 //added more variables to handle additional information
 public:
   string name;
   int rank;
   int count;
   float percentage;
   Node *Left;
   Node *Right;
};

//-----------------------------------------------------------
// Define the BinaryTree class interface
//-----------------------------------------------------------
class BinaryTree
{
 public:
   // Constructor functions
   BinaryTree();
  ~BinaryTree();

   // General binary tree operations
   bool Search(string name);
   bool Insert(string name, int count, int rank, float percentage);
   bool Delete(string name);
   void Print();

 private:
   // Helper functions
   void DestroyHelper(Node * Tree);
   bool SearchHelper(string name, Node * Tree);
   bool InsertHelper(string name, int count, int rank, float percentage, Node * &Tree);
   bool DeleteNode(Node * &Tree);
   bool DeleteHelper(string name, Node * &Tree);
   void PrintHelper(Node * Tree);

   // Tree pointer
   Node *Root;
};
