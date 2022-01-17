// Filename: linkedlist.cpp
// 
// Contains the class LinkedList that represents a linked list. This contains some basic operations, such as insert, delete, find, length
// 
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
LinkedList :: LinkedList()
{
	head = NULL;
}

// Insert(int val): Inserts the int val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: Int to insert into the linked list
// Output: Void, just inserts new Node
void LinkedList :: insert(int val)
{
	Node *to_add = new Node; // creates new Node
	to_add->data = val; // sets the data to hold input val
	
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
}

// find(int val): Finds a Node with data "val"
// Input: int to be found
// Output: a pointer to a Node containing val, if it exists. Otherwise, it returns NULL
// Technically, it finds the first Node in the list containing val
Node* LinkedList :: find(int val)
{
    Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    // curr will look over list. At every iteration, we will check if curr->data is val. If so, we are done. Otherwise, we proceed through the list.
    while(curr != NULL) //looping over list
    {
        if (curr->data == val) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through list
    }
    // if loop terminates, val not found
    return NULL;
}

// deleteNode(int val): Delete a Node with data val, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, only the first Node in the list is deleted. Note that this removes the node from the list
//         but does not free the corresponding memory
Node* LinkedList :: deleteNode(int val)
{
    Node* prev = NULL;
    Node* curr = head;
    while(curr != NULL) // loop over list, starting from head
    {
        if(curr->data == val) // we found Node with val, so break
            break; 
        //otherwise, proceed list
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    // at this point, curr points to Node with val. If curr is null, then val is not in the list.
    if (curr == NULL) // val not found
        return NULL; 
    // val is in list. Note that curr is not NULL. There is a case analysis now. If prev is null, then curr is head. So we delete head directly.
    // Otherwise, we delete the Node after prev.
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. Note that both curr and prev are not NULL
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    curr->next = NULL; // set next pointer of curr to NULL, to ensure no dangling references
    return curr;
}


// deleteAndFreeNode(int val): Delete a Node with data val and free the memory, if it exists. Otherwise, do nothing.
// Input: int to be removed
// Output: void. If there are multiple Nodes with val, only the first Node in the list is deleted. Note that this frees the memory of that deleted node
void LinkedList :: deleteAndFreeNode(int val)
{
    Node* ptr = deleteNode(val); // get pointer to node with val
    if (ptr != NULL) // if node actually exists
    {
        ptr->next = NULL; // just be extra safe, probably don't need this
        delete(ptr); // free that memory
    }
    return; //DONE!
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just deletes every Node of the list
void LinkedList :: deleteList()
{
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
    Node *temp = NULL;

	// curr will loop over list. At every iteration, we first store a pointer to the next Node, and then delete the current Node.
    while(curr != NULL){ // Looping over list
		temp = curr->next; // store pointer to next Node in the list
		delete(curr); // delete the current Node
		curr = temp; // update curr to proceed through list
	}
	head = NULL;
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print()
{
    string list_str = ""; // string that has list
	Node *curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	// curr will loop over list. It prints the content of curr, and then moves curr to next Node.
	while(curr != NULL){ // looping over list
        list_str = list_str + to_string(curr->data) + " "; //append string with current Node's data
		curr = curr->next; // proceed through list
	}
    if (list_str.length() > 0) // string is non-empty
        list_str.pop_back(); // remove the last (extra) space from string
    return list_str;
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length()
{
    int length = 0; // initialize length to zero
	Node *curr = head; // curr is ths current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	
	while(curr != NULL){ // looping over list
		length++; // increment length
		curr = curr->next; // proceed to next Node
	}
	return length;
}

// SOLUTIONS 

// REVERSE RECURSIVE
// Node* rev(Node* hed) {
//     if (hed == NULL || hed->next == NULL) {
//       return hed;
//     }
//     Node* rlh = rev(hed->next);
//     (hed->next)->next = hed;
//     hed->next = NULL;
//     return rlh;
// }
// void LinkedList :: reverse()
// {   
//     head = rev(head);
// }

// KTH DELETE
void LinkedList::kDel(int val, int k)
{
    Node* prev = NULL;
    Node* curr = head;
    int count = 0;
    while(curr != NULL) // loop over list, starting from head
    {
        if (curr->data == val) { // we found Node with val, see if count matches k
            count++;
            if (count==k) // if count matches k, we break
            {
                break; 
            }
        }
            //otherwise, proceed list
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    // at this point, curr points to Node with val. If curr is null, then val is not in the list.
    if (curr == NULL) // val not found
        return; 
    // val is in list. Note that curr is not NULL. There is a case analysis now. If prev is null, then curr is head. So we delete head directly.
    // Otherwise, we delete the Node after prev.
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. Note that both curr and prev are not NULL
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    curr->next = NULL; // set next pointer of curr to NULL, to ensure no dangling references
    delete(curr);
    return;
}
// This function returns the number k which corresponds to total occurrences of val in list;
int LinkedList::lDelFind(int val) // relies on kDel
{
    Node* curr = head;
    int count = 0;
    while(curr != NULL) // loop over list, starting from head
    {
        if (curr->data == val) { // we found Node with val, see if count matches k
            count++;
        }
        curr = curr->next; // move curr by one Node
    }
    return count;    
}
// Deletes last occurrence of nodes with val
void LinkedList::lDel(int val) // relies on kDel and lDelFind
{
    int foundK = lDelFind(val);
    kDel(val, foundK);
    return;
}

// Function deletes all but the first occurrence of a node with val
void LinkedList::nfDel(int val)
{
    cout<<"nfDel ENTERED"<<endl;
    int count = 0;
    Node* curr = head;
    while(curr!=NULL)
    {
        if (curr->data==val)
        {
            count++;
            cout<<"Count: "<<count<<endl;
        }
        curr = curr->next;
    }
    if (count>1)
    {
        for (int i=1; i<count; i++)
        {
            kDel(val, 2); // Just repeats a kth delete to the 2nd occurence a bunch
            cout<<"Just deleted 2nd occurrence: "<<print()<<endl;
        }
    }
    return;
}


int LinkedList::finder(int k) // finds the k'th Node's val in linked list
{
    Node* curr = head;
    for (int i=1; i<k; i++) // REMEMBER head is always first node!
    {
        curr = curr->next;
    }
    return curr->data;
}
bool LinkedList::isPalindrome()
{   
    // starts with pointer to last node of first half (left)
    // and first node of second half (right)
    // Pointers move from the center and spread out 1 at a time over each iteration checking for sameness
    // Loop ends if sameness is broken or enough iterations passed
    int len = length();
    if (len==0 || len==1) // corner case if none or 1 item is in list
    {
        return true;
    }
    if (len==2) // corner case if 2 items are in list
    {
        return (finder(1) == finder(2) ? true : false);
    }
    int left = len/2; // to be subtracted from
    int right = (len%2 == 0 ? (len/2)+1 : (len/2)+2); // to be added to
    cout<<(len%2 == 0 ? "EVEN" : "ODD")<<endl;
    while (left > 0 && right < len+1)
    {
        cout<<"left is: "<<left<<" of val: "<<finder(left)<<" || right is: "<<right<<" of val: "<<finder(right)<<endl;
        if (finder(left) == finder(right))
        {
            left--;
            right++;
        }
        else 
        {
            return false;
        }
    }
    return true;
}

// FORWARD ROTATE
void LinkedList::rotate(int x)
{
    int n = length();
    int x_fix = x%n;
    Node* curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = head; // circularization is done
    for (int i=0; i<(n-x_fix); i++) // move to node just before slice
    {
        curr = curr->next;
    }
    head = curr->next;
    curr->next = NULL;
    return;
}

// REVERSE ROTATE
void LinkedList::revrotate(int x)
{
    Node* curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = head; // circularization is done
    curr = curr->next; // move curr back to head
    for (int i=1; i<x; i++) // move to node just before slice
    {
        curr = curr->next;
    }
    head = curr->next;
    curr->next = NULL;
    return;
}
 

/* The function removes duplicates from a SORTED LIST */
void LinkedList::dedup()
{
    /* Pointer to traverse the linked list */
    Node* curr = head;
 
    /* Pointer to store the next pointer of a node to be deleted*/
    Node* nex;
     
    /* do nothing if the list is empty */
    if (curr == NULL)
    {
        return;
    } 
    /* Traverse the list till last node */
    while (curr->next != NULL)
    {
    /* Compare current node with next node */
    if (curr->data == (curr->next)->data)
    {
        /* The sequence of steps is important*/       
        nex = (curr->next)->next;
        delete(curr->next);
        curr->next = nex;
    }
    else /* This is tricky: only advance if no deletion */
    {
        curr = curr->next;
    }
    }
}
// TEST QUESTION
// void LinkedList :: rotateToHead(int val)
// {
//     if (find(val)==NULL)
//     {
//         return;
//     }
//     Node* curr = head;
//     while (curr->next != NULL)
//     {
//         curr = curr->next;
//     }
//     curr->next = head; // finished circularization
//     while ((curr->next)->data != val)
//     {
//         curr = curr->next;
//     }
//     head = curr->next;
//     curr->next = NULL;
//     return;
// }

// REVERSE ON K INDEX, CAN BE USED FOR FULL REVERSE OR K REVERSE
void LinkedList::reverse(int val) // CALL reverse(length()) to reverse whole list
{
// IMPLEMENT FUNCTION
	if (val < 1 || length() < 1) 
	{
		return;
	}
	if (val > length())
	{
		val = length();
	}
	Node* prev = NULL;
	Node* curr = head;
	Node* next = NULL;
	for (int c=0; c < val; c++)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head->next = curr;
	head = prev;
}
void LinkedList::reverse()
{
    cout<<"Found the reverse"<<endl;
    return reverse(length());
}

void LinkedList::reversetail(int val)
{
    reverse(); // perform full reverse
    reverse(val); // perform reverse on tail
    reverse(); // put back to OG orientation
}