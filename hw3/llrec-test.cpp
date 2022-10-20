#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------


struct isOdd
{ 
    bool operator()(const int& val)
    {
        if (val % 2 == 1)
        {
            return true;
        }
        
        return false;
    }
};

struct isDivisByThree
{ 
    bool operator()(const int& val)
    {
        if (val % 3 == 0)
        {
            return true;
        }
        
        return false;
    }
};

struct isLessThanTen
{ 
    bool operator()(const int& val)
    {
        if (val < 10)
        {
            return true;
        }
        
        return false;
    }
};




int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------


    Node* head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    
    // Test out your linked list code
    isOdd c1;
    isDivisByThree c2;
    isLessThanTen c3;

    //Case 1: Comparison = isOdd (if value is an odd number)
    Node* g = llfilter(head, c1);
    cout << "Filtered if odd number list: " << endl;
    print(g);
    dealloc(head);

    head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    //Case 2: Comparison = isDivisByThree (if value is divisible by three)
    Node* h = llfilter(head, c2);
    cout << "Filter if divisible by three list: " << endl;
    print(h);
    dealloc(head);

    head = readList(argv[1]);
    cout << "Original list: " << endl;
    print(head);

    //Case 3: Comparison = isLessThanTen (if value is less than ten)
    Node* i = llfilter(head, c3);
    cout << "Filter if less than ten list: " << endl;
    print(i);
    dealloc(head);



    
    return 0;

}
