#include "llrec.h"
#include <iostream>

using namespace std;
int main(){
	int p = 3;
	Node* h = new Node(1,NULL);
	Node* b = new Node(2, h);
	Node* c = new Node(5, b);
	Node* s;
	Node* l;
	llpivot (h, s, l, p);
	cout << s->val << " " << s->next->val << endl;
	cout << h->val <<  endl;


	
}