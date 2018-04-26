# PBFSbenchmark

Implementation of a Parallel BFS algorithm proposed by Leiserson and Schardl: http://supertech.csail.mit.edu/papers/pbfs.pdf

Currently it is implemented in Cilk++ with locking on bag_union. It doesn't take advantage of the reducer runtime environment because reducer_bag is not working properly.

To achieve the speedup in the paper, one need to incorporate bag_insert into the reducer and create a customized memory allocator (as malloc sys calls work sequentially.)
