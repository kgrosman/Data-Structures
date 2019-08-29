#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>

/**
 * @return The number of vertices in the Graph
 */
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
    // TODO: Part 2
    return vertexMap.size();
}


/**
 * The degree of the vertex. For directed: Sum of in-degree and out-degree
 * @return Returns the degree of a given vertex.
 * @param v Given vertex to return degree.
 */
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
    // TODO: Part 2
    if (adjList.find(v.key()) != adjList.end()) {
        return adjList.at(v.key()).size();
    } else {
        return 0;
    }
}


/**
 * Inserts a Vertex into the Graph.
 * @param key The key of the Vertex to insert
 * @return The inserted Vertex
 */
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
    // TODO: Part 2
    V & v = *(new V(key));
    vertexMap.insert({key, v});
    std::list<edgeListIter> k{};
    adjList[key] = k;
    return v;
}


/**
 * Removes a given Vertex
 * @param v The Vertex to remove
 */
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
    // TODO: Part 2
    
    
    for (typename std::list<edgeListIter>::iterator it = adjList[key].begin(); it != adjList[key].end(); it++) {

        if ((**it).get().dest().key() == key) {
            std::list<edgeListIter>& list = adjList.at((**it).get().source().key());
            for (typename std::list<edgeListIter>::iterator it2 = list.begin(); it2 != list.end(); it2++) {

                if ((**it2) .get().source().key() == key || (**it2).get().dest().key() == key) {
                    list.erase(it2);

                    
                }
            }
        }
        if ((**it).get().source().key() == key) {
            std::list<edgeListIter>& list = adjList.at((**it).get().dest().key());
            for (typename std::list<edgeListIter>::iterator it2 = list.begin(); it2 != list.end(); it2++) {
                if ((**it2) .get().source().key() == key || (**it2).get().dest().key() == key) {
                    list.erase(it2);
                }
            }

        } 

        
        
        edgeList.erase(*it);
        adjList[key].erase(it);
    }
    vertexMap.erase(vertexMap.find(key));
    adjList.erase(adjList.find(key));


}


/**
 * Inserts an Edge into the Graph.
 * @param v1 The source Vertex
 * @param v2 The destination Vertex
 * @return The inserted Edge
 */
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
    // TODO: Part 2
    E & e = *(new E(v1, v2));
    edgeList.insert(edgeList.begin(), e);

    std::list<edgeListIter>& Nv1 = adjList[v1.key()]; 
    Nv1.insert(Nv1.begin(), edgeList.begin());

    std::list<edgeListIter>& Nv2 = adjList[v2.key()]; 
    Nv2.insert(Nv2.begin(), edgeList.begin());

    return e;
}


/**
 * Removes an Edge from the Graph. Consider both the undirected and directed cases.
 * min(degree(key1), degree(key2))
 * @param key1 The key of the source Vertex
 * @param key2 The key of the destination Vertex
 */
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
    // TODO: Part 2
    if (edgeList.empty()) {
        return;
    }


    if (edgeList.front().get().directed()) {
        for (typename std::list<edgeListIter>::iterator it = adjList[key1].begin(); it != adjList[key1].end(); it++) {
            E edge = (*it)->get();
            if (edge.source().key() == key1 && edge.dest().key() == key2) {
                edgeList.erase(*it);
                adjList[key1].erase(it);
            }

        }
        for (typename std::list<edgeListIter>::iterator it = adjList[key2].begin(); it != adjList[key2].end(); it++) {
            E edge = (*it)->get();
            if (edge.source().key() == key1 && edge.dest().key() == key2) {
                adjList[key2].erase(it);
            }

        }
    } else {
        for (typename std::list<edgeListIter>::iterator it = adjList[key1].begin(); it != adjList[key1].end(); it++) {
            E edge = (*it)->get();
            if ((edge.source().key() == key1 && edge.dest().key() == key2) || (edge.source().key() == key2 && edge.dest().key() == key1)) {
                edgeList.erase(*it);
                adjList[key1].erase(it);
            }

        }
        for (typename std::list<edgeListIter>::iterator it = adjList[key2].begin(); it != adjList[key2].end(); it++) {
            E edge = (*it)->get();
            if ((edge.source().key() == key1 && edge.dest().key() == key2) || (edge.source().key() == key2 && edge.dest().key() == key1)) {
                adjList[key2].erase(it);
            }

        }
    }



}


/**
 * Removes an Edge from the Graph given by the location of the given iterator into the edge list.
 * @param it An iterator at the location of the Edge that
 * you would like to remove
 */
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
    // TODO: Part 2
    removeEdge(it -> get().source().key(), it -> get().dest().key()); 

}


/**
 * Return the list of incident edges from a given vertex.
 * For the directed case, consider all edges that has the vertex as either a source or destination.
 * @param key The key of the given vertex
 * @return The list edges (by reference) that are adjacent to the given vertex
 */
template <class V, class E>  
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
    // TODO: Part 2
    std::list<std::reference_wrapper<E>> edges;

    std::list<edgeListIter> eIters = adjList.at(key);
    for (auto it = eIters.begin(); it != eIters.end(); it++) {
        edges.push_front((*it)->get());
    }

    return edges;
}


/**
 * Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
 * When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
 * @param key1 The key of the source Vertex
 * @param key2 The key of the destination Vertex
 * @return True if v1 is adjacent to v2, False otherwise
 */
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
    // TODO: Part 2
    
    if (edgeList.empty()) {
        return false;
    }

    std::list<edgeListIter> eIters1 = adjList.at(key1);

    for (auto it = eIters1.begin(); it != eIters1.end(); it++) {
        if ((**it).get().source().key() == key1 && (**it).get().dest().key() == key2) {
            return true;
        }
    }

    if (!edgeList.front().get().directed()) {
        std::list<edgeListIter> eIters2 = adjList.at(key2);

        for (auto it = eIters2.begin(); it != eIters2.end(); it++) {
            if ((**it).get().source().key() == key2 && (**it).get().dest().key() == key1) {
                return true;
            }
        }
    }
    
    return false;
}

