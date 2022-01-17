#include "avl.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void Node::print()
{
    int pKey = (parent != NULL ? parent->key : 999);
    int lKey = (left != NULL ? left->key : 999);
    int rKey = (right != NULL ? right->key : 999);

    cout << "K:" << key << "|L:" << lKey << " R:" << rKey << " P:" << pKey << "|NodeCT:" << subTreeNodeCount << endl;
    return;
}

AVL::AVL()
{
    root = NULL;
}

void AVL::insert(int val)
{
    Node *to_insert = new Node(val);
    if (root == NULL)
    {
        root = to_insert;
    }
    else
    {
        insert(root, to_insert);
    }
}

void AVL::insert(Node *start, Node *to_insert)
{ // Insert only occurs at leaf nodes, else recursively call
    if (start == NULL)
    {
        return;
    }
    start->subTreeNodeCount++;
    if (start->key <= to_insert->key)
    {
        if (start->right == NULL)
        {
            start->right = to_insert;
            to_insert->parent = start;
            return;
        }
        else
        { // Will need to recursively call insert to find leaf node
            insert(start->right, to_insert);
            return;
        }
    }
    else
    { // If start->key > to_insert->key
        if (start->left == NULL)
        {
            start->left = to_insert;
            to_insert->parent = start;
            return;
        }
        else
        { // Will need to recursively call insert to find leaf node
            insert(start->left, to_insert);
            return;
        }
    }
}

Node *AVL::find(Node *start, int val)
{
    if (start->key == val)
    {
        return start;
    }
    else if (start->key <= val)
    {
        return find(start->right, val);
    }
    else
    {
        return find(start->left, val);
    }
}
Node *AVL::find(int val)
{
    return find(root, val);
}

Node *AVL::minNode(Node *start)
{ // minNode of subtree is the leftmost node
    if (start == NULL)
    { // According to prof's ex code, this should not happen
        return NULL;
    }
    if (start->left == NULL)
    { // If start has no left node, we are at subTree's minNode
        return start;
    }
    else
    {
        return minNode(start->left);
    }
}

Node *AVL::maxNode(Node *start)
{ // maxNode of subtree is the rightmost Node
    if (start == NULL)
    {
        return NULL;
    }
    if (start->right == NULL)
    {
        return start;
    }
    else
    {
        return maxNode(start->right);
    }
}

string AVL::printPreOrder(Node *start)
{
    if (start == NULL) {
        return "";
    }
    string output = to_string(start->key); // Record start->key
    string leftpart = printPreOrder(start->left); // Recursive call on start->left
    string rightpart = printPreOrder(start->right); // Recursive call on start->right
    if (leftpart.length() != 0) { // Append leftpart to output in preorder fashion
        output = output + " " + leftpart;
    }
    if (rightpart.length() != 0) { // Append leftpart to output in preorder fashion
        output = output + " " + rightpart;
    }
    return output;
}
string AVL::printPreOrder() {
    return printPreOrder(root);
}
void AVL::pPreO(Node* start) {
    if (start == NULL) {
        return;
    }
    start->print();
    pPreO(start->left);
    pPreO(start->right);
    return;
}
void AVL::pPreO() {
    pPreO(root);
    return;
}
// Node* deleteKey(int val) {

// }

// Node* deleteNode(Node* start) {
//     if (start == NULL) {
//         return NULL;
//     }

// }

// void deleteAVL();
// void deleteAVL(Node* start);

// SOLUTION METHODS
int AVL::range(Node* start, int n1, int n2) {
    if (start == NULL) {
        return 0;
    }
    int count;
    if (start->key >= n1 && start->key <= n2) {
        count = 1;
    } else {
        count = 0;
    }
    int leftpart = range(start->left, n1, n2);
    int rightpart = range(start->right, n1, n2);

    return count + leftpart + rightpart;
}
int AVL::range(int n1, int n2) {
    return range(root, n1, n2);
}