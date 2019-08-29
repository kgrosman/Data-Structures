#include "dsets.h"
void DisjointSets::addelements(int num) {
    while(num--) {
        elems.push_back(-1);
    }
}


int DisjointSets::find(int elem) {
    if (elems[elem] < 0) {
        return elem;
    }
    int k = find(elems[elem]);
    elems[elem] = k;
    return k;
}

void DisjointSets::setunion(int a, int b) {
    if (find(a) == find(b)) {
        return;
    }
    if (elems[find(a)] < elems[find(b)]) {
        elems[find(a)] += elems[find(b)];
        elems[find(b)] = find(a);
    } else {
        elems[find(b)] += elems[find(a)];
        elems[find(a)] = find(b);
    }
}

int DisjointSets::size(int elem) {
    return (-1) * elems[find(elem)];
}

void DisjointSets::clear() {
    elems.clear();

}







