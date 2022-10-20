#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>


template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;
  int size() const;



private:
  /// Add whatever helper functions and data members you need below
  void heapify(size_t index);
  PComparator comp;
  int k_ary;
  std::vector<T> h;



};








// Add implementation of member functions here
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  return h.size()==0;
}

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  comp = c;
  if(m < 2){
    throw std::logic_error("can't have value under 2");
  }
  k_ary = m;

}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){
  
}

template <typename T, typename PComparator>
int Heap<T,PComparator>::size() const{
  return h.size();
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(size_t index){
  size_t leafid; //represents index of leaves of node at index
  size_t pri = k_ary*index + 1; //represents the highest priority (i.e. smallest) of the leaf nodes, starts as the leftmost node

  //if index is has no leaf node (i.e. is a leaf node), do nothing
  if(k_ary*index + 1 > h.size()-1){
    return;
  }
  //else check each leaf node and swap
  else{
    for(int i = 2; i <= k_ary; i++){
      leafid = k_ary*index + i;
      //if current leaf node index exists (i.e. not out of bounds)
      if(leafid < h.size()){
        //if the current leaf node has higher priority (according to c) then pri becomes current leaf node 
        if(comp(h[leafid], h[pri])){
          pri = leafid;
        }
      }
    }
    //if pri has higher priority than the node at the index we are looking at, then we can swap them
    if(comp(h[pri], h[index])){
      std::swap(h[pri], h[index]);
      heapify(pri);
    }
  }
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
    h.push_back(item);
    int loc = h.size()-1;
    int parent = (loc-1)/k_ary;
    while(loc >= 0 && comp(h[loc], h[parent])){ 
        std::swap(h[parent], h[loc]);
        loc = parent;
        parent = (loc-1)/k_ary;
    }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return h[0]; 
  

}


// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");

  }
  //if heap has just one node, we simply pop it and we are done
  if(h.size() == 1){
    h.pop_back();
    return;
  }
  //swaps highest priority node and node at last index then deletes the last node
  std::swap(h[0], h[h.size()-1]);
  h.pop_back();
  //calls heapify on the initial last node, which is now the highest priority node
  heapify(0);




}



#endif

