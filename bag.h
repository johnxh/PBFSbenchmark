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
        delete(left);
        delete(right);
	}
};

class Pennant
{
public:
    int k;
    Node *root;
    Pennant() {
        k = -1;
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

    bool is_empty() {
        return k == -1;
    }

    Pennant* pennant_split() {
        Node n;
        Pennant* y = new Pennant(--k, root->left);
        root->right = nullptr;
        y->root->right = nullptr;
        return y;
    }

	~Pennant(){
        delete(root);
	}
};

class Bag {
public:
    int r;
    Pennant* S;   //backbone

    Bag() : r(S_DEFAULT) {
        S = new Pennant[S_DEFAULT];
    }

    Bag(int s) : r(s) {
        S = new Pennant[r];
    }

    void insert(int v) {
        int i = 0;
        Pennant* x = new Pennant(v);
        while (!S[i].is_empty()) {
            S[i].pennant_union(x);
            x = S[i];
            S[i++].k = -1;
        }
        S[i] = x;
    }

    void bag_union(Bag* P) {
        Pennant* y = new Pennant();
        for (int i = 0; i < r; ++i) {
            if (S[i].is_empty()) {
                if (P->S[i].is_empty()) {
                    if (!y->is_empty()) {
                        S[i] = y;
                        y = new Pennant();
                    }
                } else { // !P.S[i].is_empty()
                    if (y->is_empty()) {
                        S[i] = P->S[i];
                        P->S[i] = new Pennant();
                    }
                }
            }
            else { // !this.S[i].is_empty()
                if (P->S[i].is_empty()) {
                    if (!y->is_empty()) {
                        y->pennant_union(&S[i]);
                        S[i] = new Pennant();
                    }
                } else {  // !P.S[i].is_empty()
                    if (y->is_empty()) {
                        S[i].pennant_union(&(P->S[i]));
                        y = S[i];
                        S[i] = new Pennant();
                        P->S[i] = new Pennant();
                    } else {
                        y->pennant_union(&(P->S[i]));
                    }
                } 
            }
        }
        delete(P);
    }

    bool is_empty() {
        for (int i = 0; i < r; ++i) {
            if (!S[i].is_empty()) {
                return false;
            }
        }
        return true;
    }

    int get_size() {
        int sum = 0;
        int mult = 1;
        for (int i = 0; i < r; ++i) {
            if (!S[i].is_empty()) {
                sum += mult;
            }
            mult = mult << 1;
        }
        return sum;
    }

    int get_depth() {
        int ret = -1;
        for (int i = 0; i < r; ++i) {
            if (!S[i].is_empty()) {
                ret = i;
            }
        }
        return ret + 1;
    }

    ~Bag(){
        delete []S;
    }
};

#endif
