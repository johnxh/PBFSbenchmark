#include <cstdlib>
#include <iostream>
#include <cilk/cilk.h>

#include"reducer_bag.h"

#define V0 0

void processPennant(BagView* bag);
void processLayer();

int main(){
	int v = 1000; // number of vertices
	int* dist = new int [v];
	dist[V0] = 0;
	for(int i = 1; i < v; i++){
		dist[i] = 0x7fffffff;
	}
	
	int d = 0; //level number
	
	BagView* nextBag = new BagView();
	BagView* bag = new BagView();
	bag->insert(V0);
	
	while(!bag->is_empty()){
		nextBag = 
	}
	

	return 0;
}

