#pragma once
#include <iostream>

template <typename T>
class Queue {
public:
    Queue() : front_(nullptr), back_(nullptr) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    bool empty() const {
        return front_ == nullptr;
    }

    void enqueue(const T& value) {
        Node* new_node = new Node(value);
        if (empty()) {
            front_ = new_node;
            back_ = new_node;
        }
        else {
            back_->next = new_node;
            back_ = new_node;
        }
    }
    void push(const T& value) {
        enqueue(value);
    }

    void pop() {
        dequeue();
    }
    void dequeue() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        Node* old_front = front_;
        front_ = front_->next;
        delete old_front;
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return front_->data;
    }

private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* front_;
    Node* back_;
};


