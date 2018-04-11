#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cmath>
#include <queue>
#include <vector>


#include "ktiming.h"
#include"reducer_bag.h"
using namespace std;

int v0, v, e;
int * dist;
vector<vector<int> > list;

void init();
void bfs();
vector<int> get_neighbour(int v, vector<vector<int> > list);
void process_layer(BagView* bag, BagView* next, int d);
void process_pennant(Pennant* p, BagView* bag, int d);

void init() {
    ifstream fin;
	char* c; 
    fin.open("matrix.in"); 
    fin >> v >> e >> c;
    dist = new int [v];
    v0 = 0;
    dist[v0] = 0;
    for (int i = 1; i < v; ++i) {
        dist[i] = 0x7fffffff;
    }
    int v1, v2;
    for (int i = 0; i < e; ++i) {
        fin >> v1 >> v2 >> c;
        if (v1 != v2) {
            list[v1].push_back(v2);
            list[v2].push_back(v1);
        }
    
	}
	fin.close();
}

void bfs() {
    int d = 0; //level number
    
    // initialize list


    BagView* bag = new BagView();
    bag->insert(v0);
    
    while (!bag->is_empty()) {
        BagView* next_bag = new BagView();
		process_layer(bag, next_bag,d++);  
    }
}

int main(){
    init();

    clockmark_t begin_rm = ktiming_getmark(); 
    bfs();
    clockmark_t end_rm = ktiming_getmark();

    printf("Elapsed time in seconds: %f\n", ktiming_diff_sec(&begin_rm, &end_rm));
    return 0;
}


void process_layer(BagView* bag, BagView* next, int d){
    cilk_for (int i = 0; i < bag->get_depth(); i++){
        if (!bag->get_value()->S[i].is_empty()){
            process_pennant(&(bag->get_value()->S[i]),next,d);
        }
    }
}

void process_pennant(Pennant* p, BagView* bag, int d){
    if (p->k < 7){ // the penant is small enough to process in one run
        std::queue<Node*> q;
        q.push(p->root);
        while (q.size()){
            Node* front = q.back();
            q.pop();
            int v = front->val;
            vector<int> adj = list[v];
            cilk_for(int i = 0; i < adj.size(); i++){
                int v = adj.at(i);
                if (dist[v] == 0x7fffffff) {
                    dist[v] = d+1;
                    bag->insert(v);
                }
            }
            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
    } else { // recursively split the pennant
        Pennant* other = p->pennant_split();
        cilk_spawn process_pennant(p, bag, d);
        process_pennant(other, bag,d);
        cilk_sync;
    }
}

