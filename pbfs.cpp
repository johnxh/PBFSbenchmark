#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cmath>
#include <queue>
#include <vector>
#include <string>

#include "ktiming.h"
#include "reducer_bag.h"
using namespace std;

int v0, v, e;
int * dist;

void naive_bfs();
vector<vector<int> > list;
void init(char* fname, bool nw);
void bfs();
void process_layer(Bag* bag, Bag* next, int d);
void process_pennant(Pennant* p, Bag* bag, int d);

void init(char* fname, bool nw) {
    ifstream fin;
    string c; 
    fin.open(fname);
    fin >> v >> e >> c;
    list = vector<vector<int> >(v+1);
    dist = new int [v+1];
    v0 = 1;
    dist[v0] = 0;
    list[1] = vector<int>(10);
    for (int i = 2; i <= v; ++i) {
        list[i] = vector<int>(10);
        dist[i] = 0x7fffffff;
    }
    int v1, v2;
    for (int i = 0; i < e; ++i) {
        fin >> v1 >> v2;
        if (!nw) fin >> c;
        if (v1 != v2) {
            list[v1].push_back(v2);
            list[v2].push_back(v1);
        }
    
    }
    fin.close();
}

void naive_bfs(){
    std::queue<int> q;
    q.push(1);
    int d = 0;
    while(q.size()){
        d++;
        int size = q.size();
        for(int j = 0; j < size; j++){
            int i = q.front();
            q.pop();
            vector<int> adj = list[i];
            for(int k = 0; k < adj.size(); k++){
                int v = adj.at(k);
                if(dist[v] == 0x7fffffff){
                    dist[v] = d;
                    q.push(v);
                }
            }
        }
    }
}

void bfs() {
    int d = 0; //level number
    
    // initialize list
    Bag* bag = new Bag();
    bag->insert(v0);
    while (!bag->is_empty()) {
        Bag* next_bag = new Bag();
        process_layer(bag, next_bag,d++); 
        bag = next_bag;
    }
}

int main(int argc,char* argv[]){
    if (argc == 1) {
        cout << "Usage: pbfs <file path> <flags>" << endl;
        return 0;
    }
    bool no_weight = false, naive = false, print = false;
    if (argc > 2) {
        string flags(argv[2]);
        if (flags.find("n") != string::npos)
            naive = true;
        if (flags.find("p") != string::npos)
            print = true;
        if (flags.find("w") != string::npos)
            no_weight = true;
    }
    init(argv[1], no_weight);

    clockmark_t begin_rm = ktiming_getmark();
    if (naive)
        naive_bfs();
    else
        bfs();
    clockmark_t end_rm = ktiming_getmark();
    if (print) {
        for(int i = 1; i <= v; i++){
            cout << dist[i] << " "; 
        }
    }

    printf("Elapsed time in seconds: %f\n", ktiming_diff_sec(&begin_rm, &end_rm)); 
    return 0;
}


void process_layer(Bag* bag, Bag* next, int d){
    //printf("processing layer: %d\n", d);
    cilk_for (int i = 0; i < bag->get_depth(); i++){
        if (!bag->S[i]->is_empty()){
            process_pennant(bag->S[i],next,d);
        }
    }
}

void process_pennant(Pennant* p, Bag* bag, int d){
    if (p->k < 7){ // the penant is small enough to process in one run
        Bag* b = new Bag();
        std::queue<Node*> q;
        q.push(p->root);
        while (q.size()){
            Node* front = q.front();
            q.pop();
            int v = front->val;
            vector<int> adj = list[v];
            for(int i = 0; i < adj.size(); i++){
                int v2 = adj.at(i);
                if (dist[v2] == 0x7fffffff) {
                    dist[v2] = d+1;
                    b->insert(v2);
                }
            }
            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
       bag->bag_union(b);
    } else { // recursively split the pennant
        Pennant* other = p->pennant_split();
        Bag* bag_new = new Bag();
        cilk_spawn process_pennant(p, bag_new, d);
        process_pennant(other, bag, d);
        cilk_sync;
        bag->bag_union(bag_new);
    }
}

