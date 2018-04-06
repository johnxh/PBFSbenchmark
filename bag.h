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
        k = NULL;
        root = Node();
        root->left = Node();
    }
    Pennant(int a, int b) {
        k = NULL;
        root = Node(a);
        root->left = Node(b);
    }
    Pennant(int d, Node n) {
        k = d;
        root = n;
    }
    void pennant_union(Pennant y) {
        (y.root)->right = this->root->left;
        this->root->left = y.root;
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

class Bag {
public:
    Bag();
};