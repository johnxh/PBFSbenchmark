#include <cilk/cilk.h>
#include <cilk/reducer.h>
#include "bag.h"

#ifndef REDUCER_BAG_H_INCLUDED
#define REDUCER_BAG_H_INCLUDED

class BagView {
public:
    Bag* bag;
    typedef Bag* value_type;
    BagView() {
		bag = new Bag();	
	}

    void reduce(BagView* bv) {
        bag->bag_union(bv->get_value());
    }

    void insert(int v) {
        bag->insert(v);
    }

    bool is_empty() {
        return bag->is_empty();
    }

    int get_size() {
        return bag->get_size();
    }

    int get_depth() {
        return bag->get_depth();
    }

    Bag* get_value() {
        return bag;
    }

	~BagView() {
		delete bag;
	}
};

// Monoid class.
//
typedef cilk::monoid_with_view<BagView> BagMonoid;

#endif
