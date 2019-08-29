/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (first[curDim] < second[curDim]) {
        return true;
    } else if (first[curDim] == second[curDim]) {
        if (second < first) {
            return false; 
        } else {
            return true;
        }
    } else {
        return false;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */


    double targetToPotential = 0;
    double targetToCurrBest = 0;

    //target to potential
    for (int i = 0; i < Dim; i++) {
        double toSquare = (target[i] - potential[i]);
        targetToPotential += (toSquare * toSquare);
    }

    //target to current best
    for (int i = 0; i < Dim; i++) {
        double toSquare = (target[i] - currentBest[i]);
        targetToCurrBest += (toSquare * toSquare);
    }

    if (targetToPotential < targetToCurrBest) {
        return true;
    }
    if (targetToPotential > targetToCurrBest) {
        return false;
    }
    return (potential <= currentBest);
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & newPoints, int left, int right, int pivotIndex, int curDim) {

   
    Point<Dim> pivotValue = newPoints.at(pivotIndex);

    newPoints.at(pivotIndex) = newPoints.at(right); 
    newPoints.at(right) = pivotValue;

    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (smallerDimVal(newPoints.at(i), pivotValue, curDim)) {
            Point<Dim> temp = newPoints.at(storeIndex);
            newPoints.at(storeIndex) = newPoints.at(i);
            newPoints.at(i) = temp;

            storeIndex++; 
        }
    }
    Point<Dim> temp = newPoints.at(storeIndex);
    newPoints.at(storeIndex) = newPoints.at(right);
    newPoints.at(right) = temp;



    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>> & newPoints, int left, int right, int offset, int curDim) {

    //XXX: offset is the k'th smallest element

    while (true) {
        if (left == right) {
            return newPoints.at(left);
        }

        int pivotIndex = (left + right) / 2;
        pivotIndex = partition(newPoints, left, right, pivotIndex, curDim);

        if (offset == pivotIndex) {
            return newPoints.at(offset);
        } else if (offset < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}

template <int Dim>
void KDTree<Dim>::buildKDTree(vector<Point<Dim>> newPoints, KDTree<Dim>::KDTreeNode *& subroot, int left, int right, int curDim) {
    if (left <= right) {
        int medianIndex = (left+right) / 2;

        subroot = new KDTree<Dim>::KDTreeNode(select(newPoints, left, right, medianIndex, curDim));

        
        buildKDTree(newPoints, subroot->left, left, medianIndex - 1, ( (curDim+1) % Dim ));
        buildKDTree(newPoints, subroot->right, medianIndex+1, right, ( (curDim+1) % Dim ));

        
        size++;
    } else {
        
        return; 
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    root = new KDTree<Dim>::KDTreeNode();
    size = 0;                   
    buildKDTree(newPoints, root, 0, newPoints.size() - 1, 0);
}

//deletes the subtree
template <int Dim>
void KDTree<Dim>::destroy(KDTree<Dim>::KDTreeNode * subroot) {
    if (subroot == NULL) {
        return;
    }

    destroy(subroot->left);
    destroy(subroot->right);

    delete subroot;
    size--;
}

//copies the subtree
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::copy(KDTree<Dim>::KDTreeNode * subroot) {
    if (subroot == NULL) {
        return NULL;
    }

    KDTree<Dim>::KDTreeNode * newNode = new KDTree<Dim>::KDTreeNode(subroot->point);
    size++;

    newNode->left = copy(subroot->left);
    newNode->right = copy(subroot->right);

    return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    /**
     * @todo Implement this function!
     */

    root = copy(other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
    /**
     * @todo Implement this function!
     */

    destroy(root);
    root = copy(rhs.root);

    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
    /**
     * @todo Implement this function!
     */

    destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::NNhelper(const Point<Dim>& query, Point<Dim>& currentBest, KDTree<Dim>::KDTreeNode* current, int curDim) const {
    //if you are leaf, we have reached bottom! Set current best to your point.
    if (current -> right == NULL && current -> left == NULL) {
        if (shouldReplace(query, currentBest, current -> point)) {
            currentBest = current -> point;
            
        }
    }
    //if you are have no right child, but query would suggest to look in right
    //subtree, we have reached bottom! Set current best to your point.
    if (current -> right == NULL && smallerDimVal(current -> point, query, curDim)) {
        if (shouldReplace(query, currentBest, current -> point)) {
            currentBest = current -> point;
            
        }
    }
    //if you are have no left child, but query would suggest to look in left
    //subtree, we have reached bottom! Set current best to your point.
    if (current -> left == NULL && !smallerDimVal(current -> point, query, curDim)) {
        if (shouldReplace(query, currentBest, current -> point)) {
            currentBest = current -> point;
            
        }
    }

    
    //recurse down the tree based on comparison of query's value in the curDim and
    //the current point's value in the curDim.
    //
    //Break ties by comparing query to the current point
    if (current -> right != NULL && smallerDimVal(current -> point, query, curDim)) {
        NNhelper(query, currentBest, current -> right, (curDim + 1) % Dim);
    } else if (current -> left != NULL && !smallerDimVal(current -> point, query, curDim)) {
        NNhelper(query, currentBest, current -> left, (curDim + 1) % Dim);
    }


    //on the way up, if your point is closer to the query than the currentBest,
    //replace currentBest with your point
    if (shouldReplace(query, currentBest, current -> point)) {
        currentBest = current -> point;
        //std::cout << "replaced! Cur best is now" << current -> point << std::endl;
    }

    //calculate the squared distance from currentBest to query
    double bestDist = 0;
    for (int i = 0; i < Dim; i++) {
        bestDist += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
    } 
    
    //if you have a left child and the current best distance is greater than the 
    //distance between the splitting plane at this node and the query, search in
    //in the left child

    if (current -> left != NULL && smallerDimVal(current -> point, query, curDim)) {
        if ((query[curDim] - current -> point[curDim]) * (query[curDim] - current -> point[curDim]) <= bestDist) {
            NNhelper(query, currentBest, current -> left, (curDim + 1) % Dim);
        }
    }

    //do the same for the right child
    if (current -> right != NULL && !smallerDimVal(current -> point, query, curDim)) {
        if ((query[curDim] - current -> point[curDim]) * (query[curDim] - current -> point[curDim]) <= bestDist) {
            NNhelper(query, currentBest, current -> right, (curDim + 1) % Dim);
        }
    }


    //return the best point!

    return currentBest;
}

    

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     */

    Point<Dim> bestStart = root->point;

    return NNhelper(query, bestStart, root, 0);
}



