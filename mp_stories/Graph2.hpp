#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <set>

#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <iostream>

//typedef std::reference_wrapper<Edge> E_byRef;
//typedef std::reference_wrapper<Vertex> V_byRef;
//typedef typename std::list<E_byRef>::iterator edgeListIter;

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 */ 
template <class V, class E>
int spHelper(Graph<V, E> g, string start, string end, std::list<std::string> & path, std::set<std::string> visited) {
    if (start == end) {
        //path list filled with vertices, so # edges = # vertices - 1
        path.push_front(start);
        return 1;
    }

    int res = -1;
    std::list<std::string> winningPath;
    
    std::list<std::reference_wrapper<E>> edges = g.incidentEdges(start); 

    std::set<std::string> newVisited = visited;
    for (auto it = edges.begin(); it != edges.end(); it++) {
        string neighbor;
        if ((*it).get().source().key() == start) {
            neighbor = (*it).get().dest().key();
        } else {
            neighbor = (*it).get().source().key();
        }

        if (newVisited.find(neighbor) == newVisited.end()) {
            newVisited.insert(neighbor);
        }
    }

    for (auto it = edges.begin(); it != edges.end(); it++) {
        string neighbor;
        if ((*it).get().source().key() == start) {
            neighbor = (*it).get().dest().key();
        } else {
            neighbor = (*it).get().source().key();
        }

        if (visited.find(neighbor) == visited.end()) {
            //neighbor hasn't been visited
            std::list<std::string> newPath;

            int helperRes = spHelper(g, neighbor, end, newPath, newVisited); 
            if (helperRes == -1) {
                continue;
            }
            if (res == -1 || helperRes + 1 < res) {
                res = helperRes + 1;
                winningPath = newPath;
            }

        }
    }



    if (res < 0) {
        return -1;
    }
    winningPath.push_front(start);
    path = winningPath;
    return res;
}


template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  std::list<std::string> path;
  std::set<std::string> visited;
  visited.insert(start);
  spHelper(*this, start, end, path, visited);
  
  return path;
}

