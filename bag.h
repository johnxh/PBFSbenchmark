#include <stdlib.h>

#ifndef Bag_H
#define Bag_H

class Node {
public:
    int val;
    Node *left, *right;

    Node() : val(NULL), left(NULL), right(NULL) {
    }

    Node(int v) : val(v),  left(NULL), right(NULL) {
    }

    Node(int v, Node *left, Node *right) :
        val(v), left(left), right(right) {
    }

    void set(int v) {
        val = v;
    }
};

class Pennant
{
public:
    int k;
    Node *root;
    Pennant() {
        k = 0;
        root = Node();
    }

    Pennant(int a) {
        k = 0;
        root = Node(a);
    }

    Pennant(int a, int b) {
        k = 1;
        root = Node(a);
        root->left = Node(b);
    }

    Pennant(int d, Node n) {
        k = d;
        root = n;
    }

    void pennant_union(Pennant* y) {
        (y->root)->right = this->root->left;
        this->root->left = y->root;
        k++;
    }

    Pennant pennant_split() {
        Node n;
        Pennant y = new Pennant(--k, root->left);
        root->right = NULL;
        y.root->right = NULL;
        return y;
    }
};

#define S_DEFAULT 10
class Bag {
public:
    int r;
    Pennant* S[];   //backbone

    Bag() : r(S_DEFAULT), S(S_DEFAULT) {
    }

    Bag(int s) {
        r = s;
        S(s);
    }

    void insert(int v) {
        int k = 0;
        Pennant* x = new Pennant(v);
        while (S[k] != NULL) {
            S[k]->pennant_union(x);
            x = S[k];
            S[k] = NULL;
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
