#include <iostream>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T data) {
        this->data = data;
        this->next = nullptr;
    }
};

template<typename T>
using NodePtr = Node<T>*;

template<typename T>
class Iterator {
public:
    NodePtr<T> mPtr;
    Iterator(NodePtr<T> ptr) {
        mPtr = ptr;
    }

    void operator++(int) {
        if (mPtr != nullptr) {
            mPtr = mPtr->next;
        }
    }

    bool operator!=(Iterator a) {
        return mPtr != a.mPtr;
    }

    T& operator*() {
        return mPtr->data;
    }
};

template<typename T>
class LinkedList {
public:
    NodePtr<T> head = nullptr;

    bool isEmpty() {
        return head == nullptr;
    }

    Iterator<T> begin() {
        return Iterator<T>(head);
    }

    Iterator<T> end() {
        return Iterator<T>(nullptr);
    }

    void insertAtFirst(T data) {
        if (isEmpty()) {
            head = new Node<T>(data);
        } else {
            NodePtr<T> newNode = new Node<T>(data);
            newNode->next = head;
            head = newNode;
        }
    }

    void insertAtLast(T data) {
        if (isEmpty()) {
            insertAtFirst(data);
        } else {
            NodePtr<T> temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            NodePtr<T> newNode = new Node<T>(data);
            temp->next = newNode;
        }
    }

    void insertAt(int index, T data) {
        if (index == 0) {
            insertAtFirst(data);
            return;
        }
        NodePtr<T> temp = head;
        for (int i = 1; i < index; i++) {
            if (temp->next == nullptr) { break; }
            temp = temp->next;
        }
        NodePtr<T> newNode = new Node<T>(data);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void deleteFirst() {
        if (isEmpty()) { return; }
        NodePtr<T> temp = head;
        head = head->next;
        delete temp;
    }

    void deleteLast() {
        NodePtr<T> temp = head;
        if (isEmpty()) { return; }
        else if (head->next == nullptr) {
            deleteFirst();
            return;
        } else {
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    void size() {
        NodePtr<T> temp = head; // Use NodePtr<T> to traverse the list
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next; // Move to the next node
        }
        std::cout << "Size of the linked list: " << count << std::endl; // Print the size
    }
};