#include <cstdlib>
#include <iostream>
#include <cilk/cilk.h>
#include <cmath>
#include <queue>
#include <vector>

#include"reducer_bag.h"
using namespace std;

#define V0 0
int * dist;

vector<int> get_neighbour(int v, vector<vector<int>> list);
void process_layer(BagView* bag, BagView* next, int d);
void process_pennant(Pennant* p, BagView* bag, int d);

int main(){
    int v = 1000; // number of vertices
    dist = new int [v];
    dist[V0] = 0;
    for(int i = 1; i < v; i++){
        dist[i] = 0x7fffffff;
    }
    
    int d = 0; //level number
    
    BagView* bag = new BagView();
    bag->insert(V0);
    
    while(!bag->is_empty()){
        BagView* nextBag = new BagView();  
    }
    

    return 0;
}

void get_neighbour(int v, vector<vector<int>> list){
    return list.at(v);    
}

void process_layer(BagView* bag, BagView* next, int d){
    cilk_for(int i = 0; i < bag->get_depth(); i++){
        if(!bag->get_value()->S[i].is_empty()){
            process_pennant(&(bag->get_value()->S[i]),next,d);
        }
    }
}

void process_pennant(Pennant* p, BagView* bag, int d){
    if(p->k < 7){ // the penant is small enough to process in one run
        std::queue<Node*> q;
        q.push(p->root);
        while(q.size()){
            Node* front = q.back();
            q.pop();
            int v = front->val;
            vector<int> adj = get_neighbour(v);
            cilk_for(int i = 0; i < adj.size(); i++){
                int v = adj.at(i);
                if(dist[v] == 0x7fffffff) {
                    dist[v] = d+1;
                    bag->insert(v);
                }
            }
            if(front->left) q.push(front->left);
            if(front->right) q.push(front->right);
        }
    }else { // recursively split the pennant
        Pennant* other = p->pennant_split();
        cilk_spawn process_pennant(p, bag, d);
        process_pennant(other, bag,d);
        cilk_sync;
    }
}

