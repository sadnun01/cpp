#include <iostream>
#include <string>
using namespace std;

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

// Iterator Class
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
        NodePtr<T> temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        std::cout << "Size of the linked list: " << count << std::endl;
    }
};

// Stack
template<typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    void push(T data) {
        list.insertAtFirst(data); //at beginning
    }

    void pop() {
        if (!list.isEmpty()) {
            list.deleteFirst(); // Pop removeing the top element
        } else {
            cout << "Stack is empty, nothing to pop!" << endl;
        }
    }

    T top() {
        if (!list.isEmpty()) {
            return list.head->data; // Top returns the first element
        }
        throw runtime_error("Stack is empty, no top element!");
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    void display() {
        for (Iterator<T> it = list.begin(); it != list.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

// Queue
template<typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    void enqueue(T data) {
        list.insertAtLast(data); //inserting at the end
    }

    void dequeue() {
        if (!list.isEmpty()) {
            list.deleteFirst(); // Dequeue removes the first element
        } else {
            cout << "Queue is empty, nothing to dequeue!" << endl;
        }
    }

    T front() {
        if (!list.isEmpty()) {
            return list.head->data; // Front returns the first element
        }
        throw runtime_error("Queue is empty, no front element!");
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    void display() {
        for (Iterator<T> it = list.begin(); it != list.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

// Movie Class
class Movie {
public:
    string name;
    float rating;

    Movie(string name, float rating) {
        this->name = name;
        this->rating = rating;
    }

    void show() {
        cout << "Movie Name: " << name << ", " << "Rating: " << rating << endl;
    }
};

// Main Function
int main() {

    LinkedList<int> myList;
    myList.insertAtLast(10);
    myList.insertAtLast(11);
    myList.insertAtLast(12);
    myList.insertAtLast(13);
    myList.insertAt(2, 23);

    myList.deleteLast();

    for (Iterator<int> it = myList.begin(); it != myList.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    for (Iterator<int> it = myList.begin(); it != myList.end(); it++) {
        *it = *it * *it;
    }

    for (Iterator<int> it = myList.begin(); it != myList.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    // Linked List of string
    LinkedList<string> words;
    words.insertAtLast("One");
    words.insertAtLast("Two");
    words.insertAtLast("Three");
    words.insertAtLast("Four");

    for (Iterator<string> it = words.begin(); it != words.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    LinkedList<Movie*> movies;
    movies.insertAtLast(new Movie("M1", 5.5f));
    movies.insertAtFirst(new Movie("M2", 7.5f));

    for (Iterator<Movie*> it = movies.begin(); it != movies.end(); it++) {
        (*it)->show();
    }
    cout << endl;

    // Stack of integers
    Stack<int> stack;
    stack.push(5);
    stack.push(10);
    stack.push(15);

    cout << "Stack after pushes: ";
    stack.display();

    cout << "Top of the stack: " << stack.top() << endl;

    stack.pop();
    cout << "Stack after pop: ";
    stack.display();

    // Queue of integers
    Queue<int> queue;
    queue.enqueue(5);
    queue.enqueue(10);
    queue.enqueue(15);

    cout << "Queue after enqueues: ";
    queue.display();

    cout << "Front of the queue: " << queue.front() << endl;

    queue.dequeue();
    cout << "Queue after dequeue: ";
    queue.display();

    return 0;
}