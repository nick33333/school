// Filename: listwrapper.cpp
//
// This is the main wrapper for the LinkedList class.
//
// After running make, the usage is:
//     ./listwrapper <INPUT_FILE> <OUTPUT_FILE>
//
// The input file contains a list of operations performed on a linked list. The operations are insert, delete, and print.
// Each line is of the form "i <INT>", "d <INT>", or "p". This means "insert", "delete", and "print" respectively. The second INT argument is for inserting/deleting that number.
//
// Only the print operations generate output, which is the list printed in order in a single line.
// The output file contains the output of all print commands.
//
// In addition, the console output shows the operations performed, and also prints the list (for every print command).
// Look at the associated pdf in this directory for more details.
//
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include <iostream>
#include "linkedlist.h"
#include <stack>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

// Node* rev(Node* head) {
//   if (head == NULL || head->next == NULL) {
//     return head;
//   }
//   Node* rlh = rev(head->next);
//   (head->next)->next = head;
//   head->next = NULL;
//   return rlh;
// }

// Node* rev(Node* head) {
//   if (head == NULL || head->next == NULL) {
//     return head;
//   }
//   Node* rlh = rev(head->next);
//   rlh->next = head;
//   head->next = NULL;
//   return head;
// }

int main(int argc, char **argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input;  // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]);  // open input file
    output.open(argv[2]); // open output file

    string command;                  // to store the next command and operation
    char *com, *dummy, *valstr, *op; // for using with strtok, strtol
    int val, val2;                   // the value from the command

    LinkedList myList; // initializing the linked list

    while (getline(input, command)) // get next line of input, store as repeat
    {
        if (command.length() == 0) // command is empty
            continue;
        com = strdup(command.c_str()); // annoying, first copy string into a "C-style" string
        op = strtok(com, " \t");       // tokenize command on whitespace, first token is operation

        // We first check if command is to print, since we do not need further parsing of command
        if (strcmp(op, "p") == 0) // print list
        {
            output << myList.print() << endl; // write printed list to file, and add new line
            cout << "Printing" << endl;
            cout << myList.print() << endl;   // printing to console
            continue;                         // move on to next command
        }

        if (strcmp(op, "r") == 0)
        {
            cout << "Reversing " + myList.print() << endl;
            //             myList.head = rev(myList.head);
            myList.reverse();
            cout << "My new reversed list " + myList.print() << endl;
        }

        valstr = strtok(NULL, " \t");         // next token is value, as string (check out documentation on strtok, to understand the parsing)
        if (valstr != NULL)                   // first check if there is actually anything to convert into int
            val = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details.

        if (strcmp(op, "i") == 0) // insert into list
        {
            cout << "Insert " + to_string(val) << endl;
            myList.insert(val);
        }

        if (strcmp(op, "d") == 0) // delete from list
        {
            cout << "Delete " + to_string(val) << endl;
            myList.deleteAndFreeNode(val);
        }

        if (strcmp(op, "revtail") == 0)
        {
            cout << "Tail Reversing " + myList.print() << endl;
            myList.reversetail(val);
            output << myList.print() << endl;
            cout << "My new tail reversed list " + myList.print() << endl;
        }

        if (strcmp(op, "ld") == 0) // delete last occurrence of val from list
        {
            cout << "Last Delete on " + to_string(val) << endl;
            myList.lDel(val);
        }
        if (strcmp(op, "nf") == 0) // delete all but first occurrence of val from list
        {
            cout << "All but first Delete on " + to_string(val) << endl;
            myList.nfDel(val);
        }
        if (strcmp(op, "ip") == 0 || strcmp(op, "pal") == 0) // checks list for palindrome status, true if list is palindrome
        {
            cout << "Checking palindrome status " << endl;
            string res = myList.isPalindrome() == true ? "Palindrome" : "Not Palindrome";
            output << res << endl;
            cout << res << endl;
        }
        if (strcmp(op, "dd") == 0) // Deduplicates list
        {
            cout << "Deduplicating list " << endl;
            myList.dedup();
        }
        if (strcmp(op, "rot") == 0) // rotates list by x
        {
            cout << "Rotating list by x = " + to_string(val) << endl;
            myList.rotate(val);
        }
        if (strcmp(op, "revrot") == 0) // revrotates list by x
        {
            cout << "RevRotating list by x = " + to_string(val) << endl;
            myList.revrotate(val);
        }
        // HACKY VAL2
        valstr = strtok(NULL, " \t");          // next token is value, as string (check out
        if (valstr != NULL)                    // first check if there is actually anything to convert into int
            val2 = strtol(valstr, &dummy, 10); // convert initial portion of valstr into an integer val, with base 10. Check out documentation on strtol for more details.

        if (strcmp(op, "kd") == 0) // delete kth from list
        {
            cout << "kth Delete on " + to_string(val) << " for " << to_string(val2) << "th occurrence" << endl;
            myList.kDel(val, val2);
        }

        if (op != NULL)
            delete (op); // just free memory of op string
    }
    myList.deleteList();
    input.close();
    output.close();
}
