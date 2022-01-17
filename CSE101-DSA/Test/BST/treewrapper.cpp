// Filename: treewrapper.cpp
//
// This is the main wrapper for the BST class.
// 
// After running make, the usage is:
//     ./treewrapper <INPUT_FILE> <OUTPUT_FILE>
// 
// The input file contains a list of operations performed on a BST. The operations are insert, delete, find, printing in/pre/post order 
// Each line is of the form:
// 
//         i <INT>: insert <INT> into BST
//         f <INT>: find if <INT> is in BST
//         d <INT>: delete <INT> from BST
//         pin: print tree in order
//         ppre: print tree pre-order
//         ppost: print tree post-order
// 
// The find and print operations generate output, which is either "found/didn't find <INT>" or the tree printed in the desired order.
// 
// The output file contains the output of all commands that lead to output.
// 
// In addition, the console output shows the operations performed, and also prints the tree (for every print command).
// 
// C. Seshadhri, Jan 2020

#include <iostream>
#include "bst.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector> 
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;


int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string command; // to store the next command and operation
    char *com, *dummy, *valstr, *op; // for using with strtok, strtol
    int val = 0, val2 = 0; // the value from the command

    BST myBST; // initializing the linked list
        

    while(getline(input,command)) // get next line of input, store as repeat
    {
        if (command.length() == 0) // command is empty
            continue;
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " \t"); //tokenize command on whitespace, first token is operation

        valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if(valstr != NULL) // first check if there is actually anything to convert into int
            val = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details. 
        
        // My hacky 2nd valstr to take in 2nd input field if there is one
        valstr = strtok(NULL, " \t");
        if(valstr != NULL) // first check if there is actually anything to convert into int
            val2 = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details. 
        
    
        if(strcmp(op,"i") == 0) // insert into list
        {
            cout << "Insert "+to_string(val) << endl;
            myBST.insert(val);
        }
        if(strcmp(op,"d") == 0) // delete from list
        {
            cout << "Delete "+to_string(val) << endl;
            free(myBST.deleteKey(val)); // delete the value, and free the memory
        }
        if(strcmp(op,"f") == 0) // delete from list
        {
            string message;
            if(myBST.find(val)) // yes, val is found in BST
                message = " found";
            else
                message = " not found";
            cout << to_string(val)+ message << endl;
            output << to_string(val)+ message << endl;
        }
        if(strcmp(op,"pin") == 0) // print tree in order
        {
            output << myBST.printInOrder() << endl; // write printed tree to file, and add new line
            cout << "Print In Order" << endl;
            cout << myBST.printInOrder() << endl; // printing to console
            continue; // move on to next command
        }
        if(strcmp(op,"ppre") == 0) // print tree pre order
        {
            output << myBST.printPreOrder() << endl; // write printed tree to file, and add new line
            cout << "Print Pre Order" << endl;
            cout << myBST.printPreOrder() << endl; // printing to console
            continue; // move on to next command
        }
        if(strcmp(op,"ppost") == 0) // print tree post order
        {
            output << myBST.printPostOrder() << endl; // write printed tree to file, and add new line
            cout << "Print Post Order" << endl;
            cout << myBST.printPostOrder() << endl; // printing to console
            continue; // move on to next command
        }
        
        if(strcmp(op,"height")==0) {
            output << myBST.printTreeHeight()<<endl;
            cout << "Printing tree height: " << endl;
            cout << myBST.printTreeHeight()<<endl;
            continue;
        }
        
        // function to test 2 output fields
        if(strcmp(op,"test")==0) {
            cout<<"Test of val: "<<val<<" and val2: "<<val2<<endl;
            continue;
        }
        
        // my lca function
        if(strcmp(op,"lca")==0) {
            cout<<"Least Common Ancestor of: "<<val<<" and: "<<val2<<endl;
            Node* x = myBST.lca(val,val2);
            if (x==NULL)
            {
                cout<<"null"<<endl;
                output<<"null"<<endl;
            }
            else
            {
                cout<<x->key<<endl;
                output<<x->key<<endl;
            }
            
            continue;
        }
        
        // width by level
        if(strcmp(op,"lwidth")==0) {
            cout<<"Width of level: "<<val<<endl;
            cout<<myBST.width(val)<<endl;
            continue;
        }
        
        // max width of tree
        if(strcmp(op,"w")==0) {
            cout<<"Width of tree: "<<endl;
            cout<<myBST.maxWidth()<<endl;
            output<<myBST.maxWidth()<<endl;
            continue;
        }
        

     }
     myBST.deleteBST(); // delete the tree from memory
     input.close();
     output.close();


}
