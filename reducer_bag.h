#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "bag.h"

#ifndef REDUCER_BAG_H_INCLUDED
#define REDUCER_BAG_H_INCLUDED

class BagView {
public:
    Bag* bag;
    typedef Bag* value_type;
    BagView*() : bag() {}
    BagView*() : 
    void reduce(BagView* bv) {
        bag->bag_union(bv);
    }

    void insert(int v) {
        bag->insert(v);
    }

    Bag* get_value() {
        return bag;
    }
};

// Monoid class.
//
typedef cilk::monoid_with_view<BagView> BagMonoid;

#endif