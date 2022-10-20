#include "split.h"
#include <cstddef>

int main(){
  
  Node* g = NULL;
  Node f(6,g);
  Node e(5,&f);
  Node d(4,&e);
  Node c(3,&d);
  Node b(2,&c);
  Node a(1,&b);
  
  Node* an = &a;
 
  Node* odds = NULL;
  Node* evens = NULL;
  split(an, odds, evens);
}