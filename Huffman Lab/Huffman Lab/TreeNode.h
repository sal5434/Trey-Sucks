// TreeNode.h - Huffman Code Lab
// Written by Sarah Lakos
#include <iostream>
#include <string>

using namespace std;

template<typename DATA_TYPE> 
struct TreeNode
{
   DATA_TYPE d_value;
   TreeNode *d_left_p;
   TreeNode *d_right_p;

   bool      d_subtreeFlag;

   TreeNode(const DATA_TYPE&  value
	       , TreeNode         *left = 0
		   , TreeNode         *right = 0)
		   : d_value(value)
		   , d_left_p(left)
		   , d_right_p(right)
   {
   }

   bool IsLeaf() const
   {
      return !d_left_p && !d_right_p;
   }
};