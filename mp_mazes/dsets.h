#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets {
private:
    std::vector<int> elems;

public:
    void addelements(int num);   
    int find(int elem);   
    void setunion(int a, int b);
    int size(int elem);

    void clear();
};

#endif
