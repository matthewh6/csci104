#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************
void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot){
	//Setting smaller and larger to NULL in case there is garbage data inside
	smaller = NULL;
	larger = NULL;
	
	if(head == NULL){
		return;
	}

	Node* temp = head->next;

	if(head->val <= pivot){
		smaller = head;
		smaller->next = NULL;
		head = NULL;
		llpivot(temp, smaller->next, larger, pivot);
		//delete temp;
	}
	else{
		larger = head;
		larger->next = NULL;
		head = NULL;
		llpivot(temp, smaller, larger->next, pivot);
		//delete temp;
	}
}

