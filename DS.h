#ifndef DS_H
#define DS_H

#include<iostream>
#include <functional>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node* next;
    Node() : next(nullptr) {}
};

template <class T>
class Stack {
public:
    Stack();
    ~Stack();
    void push(T p);
    bool pop();
    bool empty();
    T& reTop();

private:
    Node<T>* top;
};

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
    Node<T>* tNew = new Node<T>();
    tNew->next = top;
    tNew->data = p;
    top = tNew;
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
    top = top->next;
    delete oldTop;
    return true;
}

template <class T>
T& Stack<T>::reTop() {
    return top->data;
}

template <class T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    Node<T>* insert(T);
    void print();
    Node<T>* reHead() { return head; };
    void pop() {
        if (head != nullptr) {
            Node<T>* oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }
    Node<T>* searchByTrackingNumber(int trackingNumber) {
        Node<T>* current = head;

        while (current != nullptr) {
            if (current->data->getTrackingNumber() == trackingNumber) {
                return current; // Return the node if found
            }
            current = current->next;
        }

        return nullptr; // Return nullptr if not found
    }
    void deleteNode(T data) {
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

private:
    Node<T>* head;
};

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
    Node<T>* nNode = new Node<T>();
    nNode->data = nl;
    nNode->next = nullptr;

    if (head == nullptr) {
        head = nNode;
    } else {
        Node<T>* tmp = head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
        }
        tmp->next = nNode;
    }
    return nNode;
}

template <class T>
class Queue {
public:
    Queue();
    ~Queue();
    void enqueue(T p);
    bool dequeue();
    bool empty();
    T front();

private:
    Node<T>* head;
    Node<T>* tail;
};

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
    Node<T>* tNew = new Node<T>();
    tNew->data = p;
    tNew->next = nullptr;

    if (empty()) {
        tail = head = tNew;
    } else {
        tail->next = tNew;
        tail = tNew;
    }
}

template <class T>
bool Queue<T>::dequeue() {
    if (empty())
        return false;

    Node<T>* old = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;
    delete old;
    return true;
}

template <class T>
T Queue<T>::front() {
    return head->data;
}

template <class T, class Compare = std::less<T>>
class Vector {
    T* arr;
    int cap;
    int cur;
    Compare comp;  // Comparison function

public:
    Vector();
    Vector(Compare compareFunc);
    ~Vector();
    T* get(int ind);
    int getCap() { return cap; }
    int getSize() { return cur; }
    void push(T nEl);
    void push(T nEl, int ind);
    T pop();
    void heapify(int i);
    void buildHeap();
    T extractRoot();
    bool empty() const { return cur == 0; }
};

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
        T* temp = new T[2 * cap];
        for (int i = 0; i < cap; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        cap *= 2;
    }
    arr[cur] = nEl;
    cur++;
    buildHeap();
}

template <class T, class Compare>
T* Vector<T, Compare>::get(int ind) {
    if (ind >= 0 && ind < cur) {
        return &arr[ind];
    }
    return nullptr;
}

template <class T, class Compare>
T Vector<T, Compare>::pop() {
    if (cur <= 0) {
        throw std::out_of_range("Empty");
    }

    T root = arr[0];
    arr[0] = arr[cur - 1];
    cur--;
    heapify(0);
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
        heapify(ind);
    }
}

template <class T, class Compare>
void Vector<T, Compare>::buildHeap() {
    for (int i = (cur - 1) / 2; i >= 0; i--) {
        heapify(i);
    }
}

template <class T, class Compare>
T Vector<T, Compare>::extractRoot() {
    if (cur <= 0) {
        throw std::out_of_range("Heap is empty");
    }

    T root = arr[0];
    arr[0] = arr[cur - 1];
    cur--;
    heapify(0);
    buildHeap();
    return root;
}

#endif