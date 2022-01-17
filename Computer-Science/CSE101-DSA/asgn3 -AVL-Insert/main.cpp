#include "avl.h"

#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace ::std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Ayo don't do dat" << endl;
        throw std::invalid_argument("Usage: ./treewrapper <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;  // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]);  // open input file
    output.open(argv[2]); // open output file

    string command;                  // to store the next command and operation
    char *com, *dummy, *valstr, *op; // for using with strtok, strtol
    int val = 0, val2 = 0;           // the value from the command

    AVL myAVL; // initializing the AVL

    while (getline(input, command)) // get next line of input, store as repeat
    {
        if (command.length() == 0)
        { // command is empty
            continue;
        }
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string

        // OP = METHOD TO PERFORM
        op = strtok(com, " \t"); //tokenize command on whitespace, first token is operation
        // 1ST INPUT FIELD
        valstr = strtok(NULL, " \t"); // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if (valstr != NULL)
        {                                     // first check if there is actually anything to convert into int
            val = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details.
        }
        // 2ND INPUT FIELD, My hacky 2nd valstr to take in 2nd input field if there is one
        valstr = strtok(NULL, " \t");
        if (valstr != NULL) {                  // first check if there is actually anything to convert into int
            val2 = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details.
        }

        // AVL METHODS HERE:
        // INSERT
        if (strcmp(op, "i") == 0) // insert into list
        {
            cout << "Insert " + to_string(val) << endl;
            myAVL.insert(val);
        }
        // PREORDER PRINT
        if (strcmp(op, "ppre") == 0) // print tree pre order
        {
            output << myAVL.printPreOrder() << endl; // write printed tree to file, and add new line
            cout << "Print Pre Order" << endl;
            cout << myAVL.printPreOrder() << endl; // printing to console
            continue;                              // move on to next command
        }

        if (strcmp(op, "r") == 0)
        {
            output << myAVL.range(val, val2) << endl;
            cout<<"Printing range from "<<val<<" to "<<val2<<endl;
            cout<<myAVL.range(val, val2)<<endl;
        }
    }
    // cout<<endl;
    // cout << "root: " << endl;
    // myAVL.root->print();   
    // cout << "root left: " << endl;
    // myAVL.root->left->print();
    // cout << "root right: " << endl;
    // myAVL.root->right->print();
    // cout <<endl<< "Print 12" <<endl;
    // Node* twel = myAVL.find(12);
    // twel->print();
    // cout <<endl<< "Print 7" <<endl;
    // Node* sev = myAVL.find(7);
    // sev->print();
    myAVL.pPreO();
    // myAVL.deleteAVL(); // delete the tree from memory
    input.close();
    output.close();
    return 0;
}
