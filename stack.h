#pragma once
#include <initializer_list>
#include <stdexcept>

template<typename T>
class StackOnList {
private:
    class Node {
    public:
        T value;
        Node* prev;
        Node() = default;
        Node(const T&);
    };

    Node* last_ = nullptr;
    int size_ = 0;

public:
    StackOnList();
    ~StackOnList();
    StackOnList(const StackOnList&);
    StackOnList& operator=(const StackOnList&);
    StackOnList(StackOnList&&);
    StackOnList& operator=(StackOnList&&);
    StackOnList(std::initializer_list<T>);
    void push(const T&);
    int size() const;
    bool isEmpty() const;
    T& top();
    const T& top() const;
    T pop();
};

template<typename T>
StackOnList<T>::StackOnList() { }

template<typename T>
StackOnList<T>::~StackOnList() {
    while (last_ != nullptr) {
        pop();
    }
}

template<typename T>
StackOnList<T>::StackOnList(const StackOnList& other) {
    Node* pnt = other.last_;
    Node* first = nullptr;

    while (pnt != nullptr) {
        auto ptr = new Node(pnt->value);
        if (first == nullptr) {
            last_ = ptr;
            first = ptr;
        } else {
            first->prev = ptr;
            first = ptr;
        }
        pnt = pnt->prev;
    }
    size_ = other.size_;
}

template<typename T>
StackOnList<T>::StackOnList(StackOnList&& other) {
    last_ = other.last_;
    size_ = other.size_;
    other.last_ = nullptr;
}

template<typename T>
StackOnList<T>& StackOnList<T>::operator=(const StackOnList& other) {
    if (this == &other) {
        return *this;
    }

    while (last_ != nullptr) {
        pop();
    }

    auto pnt = other.last_;
    Node* first = nullptr;

    while (pnt != nullptr) {
        auto ptr = new Node(pnt->value);
        if (first == nullptr) {
            last_ = ptr;
            first = ptr;
        } else {
            first->prev = ptr;
            first = ptr;
        }
        pnt = pnt->prev;
    }
    size_ = other.size_;

    return *this;
}

template<typename T>
StackOnList<T>& StackOnList<T>::operator=(StackOnList&& other) {
    if (this == &other) {
        return *this;
    }

    while (last_ != nullptr) {
        pop();
    }

    last_ = other.last_;
    size_ = other.size_;
    other.last_ = nullptr;

    return *this;
}

template<typename T>
StackOnList<T>::StackOnList(std::initializer_list<T> list) {
    for (const auto& elem : list) {
        push(elem);
    }
}

template<typename T>
int StackOnList<T>::size() const {
    return size_;
}

template<typename T>
bool StackOnList<T>::isEmpty() const {
    return (last_ == nullptr);
}

template<typename T>
T& StackOnList<T>::top() {
    if (last_ == nullptr) {
        throw std::runtime_error("Stack is empty.");
    }
    return last_->value;
}

template<typename T>
const T& StackOnList<T>::top() const {
    if (last_ == nullptr) {
        throw std::runtime_error("Stack is empty.");
    }
    return last_->value;
}

template<typename T>
void StackOnList<T>::push(const T& val) {
    Node* ptr = new Node(val);

    if (last_ != nullptr) {
        ptr->prev = last_;
    }
    last_ = ptr;
    size_++;
}

template<typename T>
T StackOnList<T>::pop() {
    if (last_ == nullptr) {
        throw std::runtime_error("Stack is empty.");
    }

    T res = last_->value;
    auto ptr = last_;
    last_ = last_->prev;
    delete ptr;
    size_--;
    return res;
}

template<typename T>
StackOnList<T>::Node::Node(const T& val) : value(val), prev(nullptr) { }
