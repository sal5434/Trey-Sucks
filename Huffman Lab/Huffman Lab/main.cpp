//// main.cpp - Huffman Code Lab
// Written by Sarah Lakos

#include <iostream>
#include <string.h>
#include <map>
#include "TreeNode.h"
#include "SymbolPriority.h"
#include "PriorityQueue.h"

#include <vector>
#include <cassert>

using namespace std;

typedef map<char, string> HuffmanMap;

bool operator==(const TreeNode<SymbolPriority>& lhs, 
                const TreeNode<SymbolPriority>& rhs)
{
    return lhs.d_value.Priority == rhs.d_value.Priority;
}

bool operator>(const TreeNode<SymbolPriority>& lhs, 
                const TreeNode<SymbolPriority>& rhs)
{
    return lhs.d_value.Priority > rhs.d_value.Priority;
}

bool operator<(const TreeNode<SymbolPriority>& lhs, 
                const TreeNode<SymbolPriority>& rhs)
{
    return lhs.d_value.Priority < rhs.d_value.Priority;
}

ostream& Print(TreeNode<SymbolPriority> *node, int level = 0)
{
    if (!node) 
    {
        return cout;
    }
    int amount = 4 * level;
    for(int i = 0; i < amount; ++i)
    {
        cout << ' ';
    }
    cout << node->d_value << endl;
    Print(node->d_left_p, level + 1);
    Print(node->d_right_p, level + 1);
    return cout;
}

TreeNode<SymbolPriority>* MakeTree(const string& message)
{
	// map<char, string> temp; // Temporary map that relates character to priority
    vector<SymbolPriority> temp; // Temporary vector of SymbolPriority

    for (int i = 0; '\0' != message[i]; ++i)   // for each character in msg
    {
        unsigned int j;

        for (j = 0; j < temp.size(); ++j)      // for each char in msg so far
        {
            if (temp[j].Symbol == message[i])  // if repeat character
            {
                ++temp[j].Priority;
                break;
            }
        }
        if (j >= temp.size()) // not found previously
        { 
            temp.push_back(SymbolPriority(message[i], 1));
        }
    }

    PriorityQueue<TreeNode<SymbolPriority>*> myQueue;

    for (unsigned int i = 0; i < temp.size(); ++i)      // for each char in msg
    {
        myQueue.Push(  new TreeNode<SymbolPriority>(temp[i])  );
    }
   

    while (myQueue.Size() > 1) 
    { 

        // pop the top off into left, and the next top off into right.

        TreeNode<SymbolPriority> *left = myQueue.Top();
        myQueue.Pop();
        TreeNode<SymbolPriority> *right= myQueue.Top();
        myQueue.Pop();

       // Print(left) << endl;;
       // Print(right) << endl;;

        // Create a new node with a symbol of '*' and a prio that is the
        // sum of the left->d_value.Priority and the right->d_value.Priority.
        // assign the left child and right child from above.
        
        TreeNode<SymbolPriority>* newNode = new TreeNode<SymbolPriority>(
			SymbolPriority('*',
            		left->d_value.Priority + right->d_value.Priority), 
			left, 
			right);

       //  Print(newNode) << endl;;

        // finally push the new node back into the queue

        myQueue.Push(newNode);
    }

    // At this point the queue has 1 element (or 0 if msg was empty).

    return myQueue.IsEmpty() ? 0 : myQueue.Top();
}


string HuffmanCode(const char                      symbol, 
                   const TreeNode<SymbolPriority>* huffman, 
		   string                          code)
    // Searches for a character in the Huffman tree and returns its code.
{
    if (huffman->IsLeaf()) // base case
    {
        if (symbol == huffman->d_value.Symbol) // match
        {
            return code;
        }
        else 
        {
            return ""; // not a match
        }
    }

    string result = HuffmanCode(symbol, huffman->d_left_p, code + "0");

    if ("" == result) 
	{
        result = HuffmanCode(symbol, huffman->d_right_p, code + "1");
	}

    return result;
}

// Makes the huffman map
HuffmanMap MakeHuffmanMap(const string& message, TreeNode<SymbolPriority>* tree)
{
	HuffmanMap result;
	for(unsigned int i = 0; i < message.size(); i++)
		result[message[i]] = HuffmanCode(message[i], tree, "");
	return result;
}

char HuffmanDecode(const string& code, const TreeNode<SymbolPriority>* huffman, int& index)
{
    if (huffman->IsLeaf())
    {
        return huffman->d_value.Symbol;
    }

    char ch = code[index++]; 

    if ('1' == ch) 
    {
        return HuffmanDecode(code, huffman->d_right_p, index);
    }
    else if ('0' == ch) 
    {
        return HuffmanDecode(code, huffman->d_left_p, index);
    }
    else if ('\0' == ch)
    {
        return '\0';  // null charactor 
    }
    else // if a character isn't a '0' or a '1'
    {
        return HuffmanDecode(code, huffman->d_left_p, ++index); 
    }
}

// Encodes the message
string Encode(const string& message, HuffmanMap HuffmanMap)
{
	string result;
	// Finds the encoded bit-string of each character and concantanates
	// them together into the final encoded string
	for(unsigned int i = 0; i < message.size(); i++)
	{
		result += HuffmanMap[message[i]];
		bool verbose = true;
		for (unsigned int j = 01; j < i; j++)
		{
			if (message[i] == message[i-j] || message[i] == message[0])
				verbose = false;
		}
		// Outputs the bit-String mapped to each unique character
		if (verbose)
			cout << message[i] << " " <<  HuffmanMap[message[i]] << endl;
	}
	return result;
}

string Decode(const string& code, const TreeNode<SymbolPriority>* huffman)
{
    string result;

    int index = 0;

    while (index < code.size())
    {
	char c = HuffmanDecode(code, huffman, index);

	result += c;
    }

    return result;
}


vector<unsigned char> ToBinary(const string& code)
{
    string s = code;

    // Pad the end of the local string with 0's until its length 
    // is a multiple of 8.

    while (s.length() % 8)
    {
	s += "0";
    }

	cout << "s = " << s << endl;

    assert(0 == s.length() % 8);

    // Now we need to allocate a vector of the right size with each
    // byte initialized to a value of '0';

    int size = s.length() / 8;

	cout << "size = " << size << endl;

    vector<unsigned char> result(size);

	cout << "result.size() = " << result.size() << endl;

    for (unsigned int i = 0; i < size; ++i)	// for each byte
    {
        for (int j = 0; j < 8; ++j)		// for each bit
        {
	    bool bit = '1' == s[8 * i + j];
		cout << "(" << i << ", " << j << ") bit = " << bit << endl;
	    result[i] <<= 1; // shifts over everything by one 
	    result[i] |= bit; // put into least significant poisition
		}
    }

    return result;
}

string FromBinary(const vector<unsigned char>& binary)
{
    string result;

    for (unsigned int i = 0; i < binary.size(); ++i)	// for each byte
    {
        for (int j = 7; j >= 0; --j)		// for each bit (MSB first)
        {
			result += binary[i] & (1 << j) ? '1' : '0';
		}
    }

    return result;
}

ostream& PrintHex(vector<unsigned char>& binary)
{
    for (unsigned int i = 0; i < binary.size(); ++i)
    {
		if (i)
		{
		    cout << ' ';
		}
		cout << (void*) binary[i] << flush;
    }

    return cout;
}

ostream& PrintDec(vector<unsigned char>& binary)
{
    for (unsigned int i = 0; i < binary.size(); ++i)
    {
		if (i)
		{
			cout << ' ';
		}
		cout << (int) binary[i] << flush;
    }
    return cout;
}

int main()
{
    cout << "Hello World!" << endl;

    PriorityQueue<TreeNode<SymbolPriority>*> myQueue;

    cout << " ---------------TESTING------------------" << endl << endl;
    {
        cout << "EMPTY TREE" << endl;
        TreeNode<SymbolPriority>* root = 0;
        Print(root) << endl;;
    }

    {
        cout << "TREE OF ONE" << endl;
        TreeNode<SymbolPriority> *root = new TreeNode<SymbolPriority>(SymbolPriority('*', 1)); 
        Print(root) << endl;
    }
    
    {
        cout << "TREE OF TWO" << endl;
        TreeNode<SymbolPriority> *root = new TreeNode<SymbolPriority>(SymbolPriority('*', 1),
                   new TreeNode<SymbolPriority>(SymbolPriority('b', 2)));
        Print(root) << endl;
        cout << "HUFFMAN CODE OF ONE CHARACTER" << endl;
        // string code = HuffmanCode('b', root, "");
        // cout << "Code: " << code << endl;
    }

    {
        cout << "TREE OF THREE" << endl;
          TreeNode<SymbolPriority> *root = new TreeNode<SymbolPriority>(SymbolPriority('*', 1),
                   new TreeNode<SymbolPriority>(SymbolPriority('b', 2)), 
                   new TreeNode<SymbolPriority>(SymbolPriority('*',3)));
          Print(root) << endl;
          cout << "HUFFMAN CODE OF ONE CHARACTER" << endl;
          //string code = HuffmanCode('b', root, "");
         // cout << "Code: " << code << endl;
          
        //cout << "Symbol: " << HuffmanDecode(code, root, index) << endl << endl;;
    }

    {
        cout << "TREE OF FOUR" << endl;
            TreeNode<SymbolPriority> *root = new TreeNode<SymbolPriority>(SymbolPriority('*', 1),
                   new TreeNode<SymbolPriority>(SymbolPriority('b', 2)),
                   new TreeNode<SymbolPriority>(SymbolPriority('*', 3),
                   new TreeNode<SymbolPriority>(SymbolPriority('d', 4))));
          Print(root) << endl;
          //cout << "HUFFMAN CODE OF ONE CHARACTER" << endl;
          //string code = HuffmanCode('d', root, "");
         // cout << "Code: " << code << endl;
    }

    {
	 cout << "TREE OF FIVE" << endl;
         TreeNode<SymbolPriority> *root = 
	     new TreeNode<SymbolPriority>(
               SymbolPriority('*', 10),
	       new TreeNode<SymbolPriority>(
                 SymbolPriority('b', 4)
	       ),
	       new TreeNode<SymbolPriority>(
		 SymbolPriority('*', 3),
                 new TreeNode<SymbolPriority>(
		   SymbolPriority('d', 2)
	         ),
                 new TreeNode<SymbolPriority>(
		   SymbolPriority('e', 1)
                 )
               )
             );

          Print(root) << endl;

          cout << "HUFFMAN CODE OF ONE CHARACTER" << endl;

          string code = HuffmanCode('d', root, "");

          cout << "Code: " << code << endl;

	  int index = 0;

	  char c =  HuffmanDecode(code, root, index);

    }

	cout << "--------------------------------------------------------" << endl;
	cout << "		START OF REAL PROGRAM			 " << endl;
	cout << "--------------------------------------------------------" << endl;


    cout << "Please enter a sentence: ";

    const int BUFFER_SIZE = 10 * 1000;
    char buffer[BUFFER_SIZE];

    cin.getline(buffer, BUFFER_SIZE);

    cout << '"' << buffer << '"' << endl;

    TreeNode<SymbolPriority> *huffman = MakeTree(buffer);

    Print(huffman) << endl;
	
	HuffmanMap hCode = MakeHuffmanMap(buffer, huffman);

    string code = Encode(buffer, hCode);

    cout << "code: " << code << endl;

    string result = Decode(code, huffman);

    cout << "result: " << result << endl;

    assert(result == buffer);

    vector<unsigned char> binary = ToBinary(code);

    cout << "  code: " << code << endl;
    cout << "BINARY: size = " << binary.size() << endl;

	PrintHex(binary) << endl;
    PrintDec(binary) << endl;

    string newCode = FromBinary(binary);

    cout << "    code: " << code << endl;
    cout << "new code: " << newCode << endl;

    system("pause");
    return 0;
}
