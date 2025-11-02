#pragma once

template <typename T>
class StackNode {
public:
    T data;
    StackNode* next;
    
    StackNode(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class Stack {
private:
    StackNode<T>* top;

public:
    Stack() : top(nullptr) {}
    
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
    
    void push(const T& value) {
        StackNode<T>* newNode = new StackNode<T>(value);
        newNode->next = top;
        top = newNode;
    }
    
    void pop() {
        if (empty()) return;
        
        StackNode<T>* temp = top;
        top = top->next;
        delete temp;
    }
    
    T& peek() {
        return top->data;
    }
    
    const T& peek() const {
        return top->data;
    }
    
    bool empty() const {
        return top == nullptr;
    }
};