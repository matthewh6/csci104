#include "stack.h"
#include <iostream>

using namespace std;

int main(){
    Stack<int> s;
    int fir = 1;
    int sec = 2;
    int thi = 3;

    s.push(fir);
    s.push(sec);
    s.push(thi);

    cout << "Stack size: " << s.size() << endl;
    cout << "Top (Should be 1): " << s.top() << endl;

    s.pop();
    s.pop();
    s.pop();
    cout << "Popped three times" << endl;
    cout << boolalpha << "Is empty: " << s.empty() <<endl;

    cout << "Stack size: " << s.size() << endl;



}