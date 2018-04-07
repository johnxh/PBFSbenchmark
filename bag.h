#include <stdlib.h>

#ifndef Bag_H
#define Bag_H

# define S_DEFAULT 10

class Node {
public:
    int val;
    Node *left; 
	Node *right;

    Node() : val(0), left(nullptr), right(nullptr) {
    }

    Node(int v) : val(v),  left(nullptr), right(nullptr) {
    }

    Node(int v, Node *left, Node *right) :
        val(v), left(left), right(right) {
    }

    void set(int v) {
        val = v;
    }

	~Node(){
	}
};

class Pennant
{
public:
    int k;
    Node *root;
    Pennant() {
        k = 0;
        root = new Node();
    }

    Pennant(int a) {
        k = 0;
        root = new Node(a);
    }

    Pennant(int a, int b) {
        k = 1;
        root = new Node(a);
        root->left = new Node(b);
    }

    Pennant(int d, Node* n) {
        k = d;
        root = n;
    }

    void pennant_union(Pennant* y) {
        y->root->right = this->root->left;
        this->root->left = y->root;
        k++;
    }

    Pennant* pennant_split() {
        Node n;
        Pennant* y = new Pennant(--k, root->left);
        root->right = nullptr;
        y.root->right = nullptr;
        return y;
    }

	~Pennant(){
	}
};

class Bag {
public:
    int r;
    Pennant* S;   //backbone

    Bag() : r(S_DEFAULT), S(S_DEFAULT) {
    }

    Bag(int s) {
        r = s;
        S = new Pennant[r];
    }

    void insert(int v) {
        int k = 0;
        Pennant* x = new Pennant(v);
        while (S[k] != nullptr) { // TODO, when creating array, C++ will use the default ctor, so here should not be nullptr
            S[k]->pennant_union(x);
            x = S[k];
            S[k] = nullptr;
        }
        S[k] = x;
    }

    void bag_union(Bag* S) {
        int y = 0;
        for (int k = 0; k < r; ++k) {
            //TODO: (this[k],y) = FA(this[k], S[k], y)
        }
    }
};

#endif
