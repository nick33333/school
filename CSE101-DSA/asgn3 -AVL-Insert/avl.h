#ifndef AVL_H
#define AVL_H
#include <string>
using namespace std;

class Node
{
    public:
        int key; // MAIN NODE COMPONENENTS
        int subTreeNodeCount = 1; 
        int height = 1; // Each node has height of 1 by default
        int balanceFactor();
        Node *left, *right, *parent; // MAIN NODE COMPONENENTS
        Node() // Default constructor
        {
            left = right = parent = NULL;
        }
        Node(int val) // Construct Node with key
        {
            key = val;
            left = right = parent = NULL;
        }
        void print();
};

class AVL
{
    // private: 
    //     Node* root; // PUBLIC FOR DEBUGGING

    public:
        Node* root; // PUBLIC FOR DEBUGGING
        AVL(); // default constructor, sets root to NULL
        void insert(int val); // DONE
        void insert(Node* n1, Node* n2, int* h); // DONE
        Node* find(int val);
        Node* find(Node* start, int val);
        Node* minNode(Node* start);
        Node* maxNode(Node* start);
        // PRINT METHODS
        string printPreOrder(Node* start);
        string printPreOrder(); 
        void pPreO(Node* start);
        void pPreO();
        // DELETE METHODS
        Node* deleteKey(int val);
        Node* deleteNode(Node* start);
        void deleteAVL();
        void deleteAVL(Node* start);
        // SOLUATION METHODS
        int range(Node* start, int n1, int n2);
        int range(int n1, int n2);
};

#endif
