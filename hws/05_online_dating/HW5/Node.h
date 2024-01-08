//
// Created by Ryan Ames on 10/11/2023.
//

#ifndef HW5_NODE_H
#define HW5_NODE_H
#include <iostream>
#include "User.h"

//Node class
template <typename T>
class Node {
public:
    //template variable for User class
    T data;
    Node* next;
    //constructor for Node class
    Node(T value) {
        data = value;
        next = nullptr;
    }
};

//Linked list class
template <typename T>
class LinkedList {
private:
    //pointer to list head
    Node<T>* head;
    int size = 0;
    //merge sort adapted
    Node<T>* merge(Node<T>* left, Node<T>* right) {
        Node<T>* result;

        if (left == nullptr) {
            return right;
        }

        if (right == nullptr) {
            return left;
        }

        if (left->data < right->data) {
            result = left;
            result->next = merge(left->next, right);
        } else {
            result = right;
            result->next = merge(left, right->next);
        }

        return result;
    }
    //merge sort adapted from example in class
    Node<T>* mergeSort(Node<T>* head_) {
        if (head_ == nullptr || head_->next == nullptr)
            return head_;

        Node<T>* slow = head_;
        Node<T>* fast = head_;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* nextToMiddle = slow->next;
        slow->next = nullptr;

        Node<T>* left = mergeSort(head_);
        Node<T>* right = mergeSort(nextToMiddle);

        return merge(left, right);
    }

public:
    LinkedList() : head(nullptr) {}
    //calls the clear function to deconstruct the list is destroyed
    ~LinkedList() {
        clear();
    }
    //returns the pointer to the head of the list
    Node<T>* get_head () const {
        return head;
    }
    //calls the sort function for the head of the current list
    void sort() {
        head = mergeSort(head);
    }

    //clear list function that deallocates all memory
    void clear(){
        if(head){
            Node<T>* next = head;
            while (next) {
                head = next->next;
                delete next;
                next = head;
            }
            head = 0;
        }
    }
    //adds an element to the end of the list
    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    //iterates through a list to check if an element exists
    bool exists(T value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

#endif //HW5_NODE_H

//7044931615
//5037402080
