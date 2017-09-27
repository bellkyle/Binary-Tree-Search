//-----------------------------------------------------------
//  Purpose:    Implementation of BinaryTree class.
//  Author:     John Gauch
//-----------------------------------------------------------
#include "tree.h"
#include <cstring>
#include <stdlib.h>

#define TRIAL_MAIN
//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
BinaryTree::BinaryTree()
{
   Root = NULL;
}

//-----------------------------------------------------------
// Destructor function helper function.
//-----------------------------------------------------------
void BinaryTree::DestroyHelper(Node * Tree)
{
   // Delete node and it's children
   if (Tree != NULL)
   {
      DestroyHelper(Tree->Left);
      DestroyHelper(Tree->Right);
      delete Tree;
   }
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
BinaryTree::~BinaryTree()
{
   // Call tree destroy function
   DestroyHelper(Root);
}

//-----------------------------------------------------------
// Search helper function.
//-----------------------------------------------------------
bool BinaryTree::SearchHelper(string name, Node * Tree)
{
   // Data name not found
   if (Tree == NULL)
      return false;

   // Data name found
   //print out the information from the name that is found
   else if (Tree->name == name)
   {
      cout << "Name: " << Tree->name << endl;
      cout << "Rank: " << Tree->rank << endl;
      cout << "Count: " << Tree->count << endl;
      cout << "Percentage: " << Tree->percentage << endl;
      return true;
   }

   // Recursively search for data name
   else if (Tree->name > name)
      return (SearchHelper(name, Tree->Left));
   else
      return (SearchHelper(name, Tree->Right));
}

//-----------------------------------------------------------
// Search for data in the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Search(string name)
{
   // Call tree searching function
   return (SearchHelper(name, Root));
}

//-----------------------------------------------------------
// Insert helper function.
//-----------------------------------------------------------
//added more parameters to handle all of the information
bool BinaryTree::InsertHelper(string name, int count, int rank, float percentage, Node * &Tree)
{
   // Insert data into the tree
   if (Tree == NULL)
   {
      //inserting all of the data
      Tree = new Node;
      Tree->name = name;
      Tree->count = count;
      Tree->rank = rank;
      Tree->percentage = percentage;
      Tree->Left = NULL;
      Tree->Right = NULL;
      return true;
   }

   // Recursively search for insertion position
   else if (Tree->name > name)
      return (InsertHelper(name, count, rank, percentage, Tree->Left));
   else
      return (InsertHelper(name, count, rank, percentage, Tree->Right));
}

//-----------------------------------------------------------
// Insert data into the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Insert(string name, int count, int rank, float percentage)
{
   // Call tree insertion function
   return (InsertHelper(name, count, rank, percentage, Root));
}

//-----------------------------------------------------------
// Delete a single node from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::DeleteNode(Node * &Tree)
{
   Node *Temp = Tree;

   // Node has 0 children
   if ((Tree->Left == NULL) && (Tree->Right == NULL))
      Tree = NULL;

   // Node has 1 child
   else if (Tree->Left == NULL)
      Tree = Tree->Right;
   else if (Tree->Right == NULL)
      Tree = Tree->Left;


   // Node has 2 children
   else
   {
      // Find leftmost node in right subtree
      Node *Parent = Tree;
      Temp = Tree->Right;
      while (Temp->Left != NULL)
      {
	 Parent = Temp;
	 Temp = Parent->Left;
      }

      // Replace deleted data with leftmost name
      if (Parent == Tree)
	 Parent->Right = Temp->Right;
      else
	 Parent->Left = Temp->Right;
      Tree->name = Temp->name;
   }

   // Delete node
   delete Temp;
   return true;
}

//-----------------------------------------------------------
// Delete helper function.
//-----------------------------------------------------------
bool BinaryTree::DeleteHelper(string name, Node * &Tree)
{
   // Data name not found
   if (Tree == NULL)
      return false;

   // Data name found and deleted
   else if (Tree->name == name)
      return (DeleteNode(Tree));

   // Recursively search for node to delete
   else if (Tree->name > name)
      return (DeleteHelper(name, Tree->Left));
   else
      return (DeleteHelper(name, Tree->Right));
}

//-----------------------------------------------------------
// Delete data from the binary tree.
//-----------------------------------------------------------
bool BinaryTree::Delete(string name)
{
   // Call tree deletion function
   return (DeleteHelper(name, Root));
}

//-----------------------------------------------------------
// Print helper function.
//-----------------------------------------------------------
void BinaryTree::PrintHelper(Node * Tree)
{
   // Check terminating condition
   if (Tree != NULL)
   {
      // Print left subtree
      PrintHelper(Tree->Left);

      // Print node name
      cout << Tree->name << " ";

      // Print right subtree
      PrintHelper(Tree->Right);
   }
}

//-----------------------------------------------------------
// Print all records in the binary tree.
//-----------------------------------------------------------
void BinaryTree::Print()
{
   // Call tree printing function
   PrintHelper(Root);
   cout << endl;
}

#ifdef TREE_MAIN
//-----------------------------------------------------------
// Main program tests the BinaryTree class.
//-----------------------------------------------------------
int main()
{
   BinaryTree tree;
   string name;
   int count;
   int rank;
   float percentage;
   //Entering the file name
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
   //entering loop to enter all of the names from the file into the tree
   while(!din.eof())
   {
      din >> name;
      din >> count;
      din >> percentage;
      din >> rank;
      tree.Insert(name, count, rank, percentage);
   }
   din.close();
   //loop to search for the name
   while (name != "quit")
   {
      cout << "Enter a name to search or enter 'quit' to exit the program" << endl;
      cin >> name;
      if(name != "quit")
      {
         //searching for the name
         if(!tree.Search(name))
            cout << "Did not find the name" << endl;
      }
   }
   tree.Print();
}

#endif
