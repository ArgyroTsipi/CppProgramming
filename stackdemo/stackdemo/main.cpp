//
//  main.cpp
//  stackdemo
//
//  Created by Argyro on 10/3/21.
//

//#ifndef CONTEST

#include <iostream>

using namespace std;

template < typename T>
class stack {
 public:
    
     stack(int size) {
         array = new T[size];
         sizeOfStack = size;
         top = 0;
     }
    
     stack(const stack& s) {
        // array = s.array;
         top = s.top;
         sizeOfStack = s.sizeOfStack;
         array = new T[s.sizeOfStack];
         for(int i=0; i<s.top; i++){
           array[i] = s.array[i];
         }
     }
    
    ~stack() {
       // if(top != 0)
      delete[] array;
     }
     
     const stack & operator = (const stack & s) {
        delete[] array;
         sizeOfStack = s.sizeOfStack;
         
         array = new T[s.sizeOfStack];
         //array = s.array;
         //sizeOfStack = s.sizeOfStack;
         top = s.top;
         for(int i=0; i< s.top; i++){
             array[i] = s.array[i];
         }
         return *this;
     }
     
    bool empty() {
         if (top == 0) {
             return true;
         }
         else return false;
     }
    
    void push(const T & x) {
        array[top++] = x;
     }
     
     T pop() {
       //  top--;
         T value = array[--top];
         //top --;
         
         return value;
     }

     int size() {
         return top;
     }

     friend ostream & operator << (ostream & out, const stack & s) {
         out << "[" << flush;
         for (int element = 0; element < s.top; element++) {
             out << s.array[element] << flush;
             if (element +1 != s.top)
                 out << ", " << flush;
         }
         out << "]" << flush;
         return out;
     }
    
 private:
    T* array;
    int sizeOfStack;
    int top;
};

/*int main()
{
    // let’s play with integers...
    stack<int> s(10);
    cout << "s is empty : " << s << endl;
    s.push(42);
    cout << "s has one element : " << s << endl;
    s.push(17);
    s.push(34);
    cout << "s has more elements : " << s << endl;
    cout << "How many ? " << s.size() << endl;
    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;
    t = s;
    cout << "popping from s : " << s.pop() << endl;
    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;
    // now with doubles...
    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;
    // and with characters...
    stack<char> k(4);
    k.push('$');
    cout << "k contains a character " << k << endl;
    
}
 #endif */
