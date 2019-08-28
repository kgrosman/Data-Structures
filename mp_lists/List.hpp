/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>


template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
    ListNode* cur = head_;
    while (cur != NULL) {
        ListNode* temp = cur;
        cur = cur -> next;
        delete temp;
    }
}

/*
template <typename T>
void List<T>::_copy(const List<T>& other) {
    length_ = other.length_;
    head_ = NULL;
    tail_ = NULL;

    ListNode* cur  = other.head_;

    while (cur != NULL) {
        this -> insertBack(cur -> data);
        cur = cur -> next;
    }
}
*/
/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inseed.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
    ListNode* newNode = new ListNode(ndata);
    newNode -> next = NULL;
    newNode -> prev = tail_;
    
    if (tail_ != NULL) {
        tail_ -> next = newNode;
    }

    if (head_ == NULL) {
        head_ = newNode;
    }

    tail_ = newNode;
    length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *s
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
   if (splitPoint == 0) {
      return start;
  }
  
  ListNode* cur  = start;
  
  for (int i = 1; i < splitPoint; i++) {
      if (cur == NULL) {
          return NULL;
      }
      cur = cur -> next;
  }
  ListNode* ans = cur -> next;
 if (cur -> next != NULL) {
      cur -> next -> prev = NULL;
 }
  cur -> next = NULL;
  //tail_ = cur;
  //length_ = splitPoint;
  return ans;

/*
  if (splitPoint == 1) {
      if (start == NULL) {
          return NULL;
      }
      ListNode* ans = start -> next;
      start -> next = NULL;
      start -> next -> prev = NULL;
      return ans;
  }



  for (int i = 1; i < splitPoint && curr -> next != NULL; i++) {
    curr = curr->next;
  }
  

  if (curr != NULL) {
      curr->next = NULL;
      if (curr -> next == NULL) {
          return NULL;
      }
      curr->next-> prev = NULL;
      return curr -> next;
  }

  return NULL;
  */
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moveore than once.
 */
template <typename T>
void List<T>::waterfall() {
    if (head_ == NULL) {
        return;
    }

    ListNode* cur = head_ -> next;
    ListNode* previ = head_;
    
    while(cur != NULL && cur != tail_) {

        ListNode* tcur = cur -> next -> next;
        ListNode* tprevi = previ -> next -> next;
       
        previ -> next = cur -> next;
        cur -> next -> prev = previ;
        
        cur -> next = NULL;
        cur -> prev = tail_;
        tail_ -> next = cur;
        tail_ = cur;


        cur = tcur;
        previ = tprevi;

    }

}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    if (startPoint == endPoint) {
        return;
    }
    ListNode* first = startPoint;
    ListNode* last = endPoint;


    ListNode* s = first -> next;
    for (ListNode* f = first; f != last;) {
        ListNode* newF = s;
        ListNode* newS = s -> next;

        f -> prev = s;
        s -> next = f;

        f = newF;
        s = newS;
    }

    first -> next = NULL;
    last -> prev = NULL;

    startPoint = last;
    endPoint = first;
        

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
   
    if (n == 1) {
        return;
    }


    ListNode* start = head_;
    ListNode* end = head_;
    bool keepGoin = true;



    int length = 0;
    for (ListNode* cur = head_; cur != NULL; cur = cur -> next) {
        length++;
    }
    int blocks = (length % n == 0) ? length / n : length / n + 1;
    ListNode** starts = new ListNode*[blocks];
    ListNode** ends = new ListNode*[blocks];
    int count = 0;
   

    while (keepGoin) {

        for (int i = 1; i < n && end != NULL; i++) {
            if (end -> next == NULL) {
                break;
            }
            
            end = end -> next;
        }
        
        ListNode* newStart;


        if (end -> next  == NULL) {
            keepGoin = false;
        } else { 
            newStart = end -> next;
        }
            reverse(start, end);
          
            starts[count] = start;
            ends[count] = end;
            count++;
        


        


        if (!keepGoin) {
           break;
        }
        start = newStart;
        end = newStart;
    
    
    }

    tail_ = ends[blocks - 1];
    head_ = starts[0];


    
    for (int i = 0; i < blocks - 1; i++) {
        if (ends[i] != NULL) {
            ends[i] -> next = starts[i + 1];
        }
            starts[i + 1] -> prev = ends[i];
    }

    delete starts;
    delete ends; 
    

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {

    ListNode* ans = (first -> data < second -> data) ? first : second;

    ListNode* prev = NULL;
    ListNode* cur = NULL;

  while (first != NULL || second != NULL) {
      prev = cur;
      if (first == NULL) {
          cur = second;
          second = second -> next;
      } else if (second == NULL) {
          cur = first;
          first = first -> next;
      } else if(first -> data < second -> data) {
          cur = first;
          first = first -> next;
      } else {
          cur = second;
          second = second -> next;
      }
      if (prev != NULL) {
        prev -> next = cur;
        cur -> prev = prev;
      }
  }



  return ans;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (chainLength == 1) {
      return start;
  }
  int length = 0;
  for (ListNode* cur = start; cur != NULL; cur = cur -> next) {
      length++;
  }

  int half = (int) length / 2;

  ListNode* split  = start;
  for (int i = 0; i < half; i++) {
      split = split -> next;
  }

  split -> prev -> next = NULL;
  split -> prev =  NULL;

  ListNode* first = mergesort(start, half);
  ListNode* second = mergesort(split, length - half);

  return merge(first, second);


}
