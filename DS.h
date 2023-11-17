#ifndef DS_H
#define DS_H

#include<iostream>
#include <functional>
using namespace std;

// Node class
template <class T>
class Node {
public:
    T data;          // Data stored in the node
    Node* next;      // Pointer to the next node
    Node() : next(nullptr) {}
};

// Stack class 
template <class T>
class Stack {
public:
    Stack();         // Constructor for Stack class
    ~Stack();        // Destructor for Stack class
    void push(T p);  // Push an element to the stack
    bool pop();      // Pop an element from the stack
    bool empty();    // Check if the stack is empty
    T& reTop();      // Get the top element of the stack

private:
    Node<T>* top;     // Pointer to the top of the stack
};

// Implementation of the Stack class
template <class T>
Stack<T>::Stack() : top(nullptr) {}

template <class T>
Stack<T>::~Stack() {
    while (!empty()) {
        pop();
    }
}

template <class T>
void Stack<T>::push(T p) {
    Node<T>* tNew = new Node<T>();  // Create a new node
    tNew->next = top;               // Link the new node to the current top
    tNew->data = p;                 // Set data for the new node
    top = tNew;                     // Update top to the new node
}

template <class T>
bool Stack<T>::empty() {
    return (top == nullptr);
}

template <class T>
bool Stack<T>::pop() {
    if (empty())
        return false;

    Node<T>* oldTop = top;
    top = top->next;                // Move top to the next node
    delete oldTop;                  // Delete the old top node
    return true;
}

template <class T>
T& Stack<T>::reTop() {
    return top->data;               // Return the data of the top node
}

// implementing linked list
template <class T>
class LinkedList {
public:
    LinkedList();                    // Constructor for LinkedList class
    ~LinkedList();                   // Destructor for LinkedList class
    Node<T>* insert(T);              // Insert a new node at the end of the list
    void print();                    // Print the elements of the list
    Node<T>* reHead() { return head; };  // Get the head of the list
    void pop();                      // Remove the head node
    Node<T>* searchByTrackingNumber(int trackingNumber);  // Search for a node by tracking number
    void deleteNode(T data);         // Delete a node with specific data

private:
    Node<T>* head;                   // Pointer to the head of the list
};

// Implementation of the LinkedList class
template <class T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <class T>
LinkedList<T>::~LinkedList() {
    Node<T>* cur = head;
    Node<T>* nextNode;

    while (cur != nullptr) {
        nextNode = cur->next;
        delete cur;
        cur = nextNode;
    }
}

template <class T>
Node<T>* LinkedList<T>::insert(T nl) {
    Node<T>* nNode = new Node<T>();   // Create a new node
    nNode->data = nl;                 // Set data for the new node
    nNode->next = nullptr;

    if (head == nullptr) {
        head = nNode;                  // If the list is empty set the new node as the head
    } else {
        Node<T>* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;           // Traverse the list to find the last node
        }
        tmp->next = nNode;             // Link the last node to the new node
    }
    return nNode;
}

template <class T>
void LinkedList<T>::print() {
    Node<T>* tmp = head;
    while (tmp != nullptr) {
        cout << tmp->data << " ";     
        tmp = tmp->next;
    }
    cout << endl;
}

template <class T>
void LinkedList<T>::pop() {
    if (head != nullptr) {
        Node<T>* oldHead = head;
        head = head->next;             // Move head to the next node
        delete oldHead;                // Delete the old head node
    }
}

template <class T>
Node<T>* LinkedList<T>::searchByTrackingNumber(int trackingNumber) {
    Node<T>* current = head;

    while (current != nullptr) {
        if (current->data->getTrackingNumber() == trackingNumber) {
            return current;  // Return the node if found
        }
        current = current->next;
    }

    return nullptr;       // Return nullptr if not found
}

template <class T>
void LinkedList<T>::deleteNode(T data) {
    Node<T>* cur = head;
    Node<T>* prev = nullptr;

    while (cur != nullptr && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }

    if (cur != nullptr) {
        if (prev != nullptr) {
            prev->next = cur->next;
        } else {
            head = cur->next;
        }

        delete cur;
    }
}

// Queue class implementing 
template <class T>
class Queue {
public:
    Queue();                          // Constructor for Queue class
    ~Queue();                         // Destructor for Queue class
    void enqueue(T p);               // Enqueue an element into the queue
    bool dequeue();                   // Dequeue an element from the queue
    bool empty();                     // Check if the queue is empty
    T front();                        // Get the front element of the queue

private:
    Node<T>* head;                    // Pointer to the head of the queue
    Node<T>* tail;                    // Pointer to the tail of the queue
};

// Implementation of the Queue class
template <class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

template <class T>
Queue<T>::~Queue() {
    while (!empty()) {
        dequeue();
    }
}

template <class T>
bool Queue<T>::empty() {
    return (tail == nullptr && head == nullptr);
}

template <class T>
void Queue<T>::enqueue(T p) {
    Node<T>* tNew = new Node<T>();   // Create a new node
    tNew->data = p;                  // Set data for the new node
    tNew->next = nullptr;

    if (empty()) {
        tail = head = tNew;           
    } else {
        tail->next = tNew;            // Link the current tail to the new node
        tail = tNew;                  // Update tail to the new node
    }
}

template <class T>
bool Queue<T>::dequeue() {
    if (empty())
        return false;

    Node<T>* old = head;
    head = head->next;                // Move head to the next node
    if (head == nullptr)
        tail = nullptr;               // If the queue becomes empty update tail to nullptr
    delete old;                       // Delete the old head node
    return true;
}

template <class T>
T Queue<T>::front() {
    return head->data;                 // Return the data of the head node
}

// implementing heap operation using concept of vector and dynamic array
template <class T, class Compare = std::less<T>>
class Vector {
    T* arr;                            // Dynamic array
    int cap;                           // Capacity of the array
    int cur;                           // Current number of elements in the array
    Compare comp;                      // Comparison function for heap operations

public:
    Vector();                         // Constructor for Vector class
    Vector(Compare compareFunc);      // Constructor with custom comparison function
    ~Vector();                        // Destructor for Vector class
    T* get(int ind);                  // Get an element at a specific index
    int getCap() { return cap; }      // Get the capacity of the array
    int getSize() { return cur; }     // Get the current size of the array
    void push(T nEl);                 // Add an element to the array
    void push(T nEl, int ind);        // Add an element at a specific index
    T pop();                          // Remove and return the last element
    void heapify(int i);              // Heapify the array at a specific index
    void buildHeap();                 // Build a heap from the array
    T extractRoot();                  // Extract the root element from the heap
    bool empty() const { return cur == 0; }  // Check if the array is empty
};

// Implementation of the Vector class
template <class T, class Compare>
Vector<T, Compare>::Vector() : arr(new T[1]), cur(0), cap(1), comp(Compare()) {}

template <class T, class Compare>
Vector<T, Compare>::Vector(Compare compareFunc) : arr(new T[1]), cur(0), cap(1), comp(compareFunc) {}

template <class T, class Compare>
Vector<T, Compare>::~Vector() {
    delete[] arr;
}

template <class T, class Compare>
void Vector<T, Compare>::push(T nEl) {
    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < cur; i++) {
            temp[i] = arr[i];         // Copy elements to the new array
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    }
    arr[cur] = nEl;                    // Add the new element to the array
    cur++;
    buildHeap();                       // Rebuild the heap
}

template <class T, class Compare>
void Vector<T, Compare>::push(T nEl, int ind) {
    if (ind < 0 || ind > cur) {
        throw std::out_of_range("Index out of bounds");
    }

    if (cap == cur) {
        T* temp = new T[2 * cap];     // Create a new array with double the capacity
        for (int i = 0; i < ind; i++) {
            temp[i] = arr[i];         // Copy elements before the insertion point
        }
        temp[ind] = nEl;               // Insert the new element
        for (int i = ind + 1; i <= cur; i++) {
            temp[i] = arr[i - 1];      // Copy elements after the insertion point
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    } else {
        for (int i = cur; i > ind; i--) {
            arr[i] = arr[i - 1];        // Shift elements to make space for the new element
        }
        arr[ind] = nEl;                 // Insert the new element
    }

    cur++;
    buildHeap();                        // Rebuild the heap
}

template <class T, class Compare>
T* Vector<T, Compare>::get(int ind) {
    if (ind >= 0 && ind < cur) {
        return &arr[ind];                // Return a pointer to the element at the specified index
    }
    return nullptr;
}

template <class T, class Compare>
T Vector<T, Compare>::pop() {
    if (cur <= 0) {
        throw std::out_of_range("Empty");
    }

    T root = arr[cur - 1];               // Get the last element
    cur--;
    buildHeap();                         // Rebuild the heap
    return root;
}

template <class T, class Compare>
void Vector<T, Compare>::heapify(int i) {
    int ind = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < cur && comp(arr[ind], arr[left])) {
        ind = left;
    }

    if (right < cur && comp(arr[ind], arr[right])) {
        ind = right;
    }

    if (ind != i) {
        std::swap(arr[i], arr[ind]);
        heapify(ind);                    // Recursive heapify at the modified index
    }
}

template <class T, class Compare>
void Vector<T, Compare>::buildHeap() {
    for (int i = (cur - 1) / 2; i >= 0; i--) {
        heapify(i);                      // Heapify each non-leaf node from bottom to top
    }
}

template <class T, class Compare>
T Vector<T, Compare>::extractRoot() {
    if (cur <= 0) {
        throw std::out_of_range("Heap is empty");
    }

    T root = arr[0];                    // Get the root element
    arr[0] = arr[cur - 1];              // Replace root with the last element
    cur--;
    heapify(0);                         // Heapify from the root
    buildHeap();                        // Rebuild the heap
    return root;
}

#endif  // DS_H
