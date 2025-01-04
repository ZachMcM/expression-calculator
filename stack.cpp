#include "stack.h"
#include <limits.h>

#define INIT_CAPACITY 8
#define INCREASE_FACTOR 2
#define CONSTANT_INCREMENT 32

template <typename T>
void Stack<T>::resize() {
    int newCapacity;
    T * temp;
    if (capacity * INCREASE_FACTOR > INT_MAX) {
        // not enough memory to proceed
        if (capacity + CONSTANT_INCREMENT > INT_MAX) {
            throw runtime_error("Stack ran out of memory");
        } else {
            // have to increase capacity with addition
            newCapacity = capacity + CONSTANT_INCREMENT;
            temp = new T[newCapacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = data[i];
            }
        }
    } else {
        // can regularly increase capacity
        newCapacity = capacity * INCREASE_FACTOR;
        temp = new T[newCapacity];
        for (int i = 0; i < capacity; i++) {
            temp[i] = data[i];
        }
    }

    delete[] data;
    data = temp;
    capacity = newCapacity;
}

template <typename T>
Stack<T>::Stack() {
    data = new T[INIT_CAPACITY];
    size = 0;
    capacity = INIT_CAPACITY;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] data;
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (size == capacity) {
        resize();
    }
    data[size] = value;
    size++;
}

template <typename T>
T Stack<T>::pop() {
    if (size == 0) {
        throw runtime_error("Stack is empty");
    }
    size--;
    return data[size];  // Note: fixed a bug here, it was returning data[size] before decrementing
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
int Stack<T>::getSize() const {
    return size;
}

template <typename T>
T Stack<T>::peek() const {
    if (size == 0) {
        throw runtime_error("Stack is empty");
    }
    return data[size - 1];
}

template class Stack<string>;
template class Stack<double>;