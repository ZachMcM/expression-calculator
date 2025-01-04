#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include <string>
using namespace std;

template <typename T>
class Stack {
  private: 
    T * data;
    int size;
    int capacity;

    void resize();

  public:
    Stack();
    ~Stack();

    void push(const T& value);
    T pop(); 
    bool isEmpty() const;
    int getSize() const;
    T peek() const; 
};

#endif // STACK_H