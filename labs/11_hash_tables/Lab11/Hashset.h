//
// Created by Ryan Ames on 11/8/2023.
//
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

#define TABLE_SIZE 1024

#ifndef LAB11_HASHSET_H
#define LAB11_HASHSET_H


class Node {
public:
    int number;
    int index;
    Node* next;
};

class HashSet {
public:
    HashSet();
    ~HashSet() {
        Node* temp;
        for(Node * & i : Table){
            temp = i;
            while (i) {
                i = temp->next;
                delete temp;
                temp = i;
            }
        }
    }
    void add(int num){
        int key;
        key = hash_function(num);   // key will be something in between 0 and (TABLE_SIZE-1); num can be negative
        if(Table[key]== nullptr){
            // create the first node for this linked list
            Node* node;
            node = new Node;
            node->number = num;
            node->next = nullptr;
            Table[key] = node;
        }else{
            // insert a node to the beginning of this linked list
            Node* node;
            node = new Node;
            node->number = num;
            node->next = Table[key];
            Table[key] = node;
        }
    }

// give me the number, return the index
    int get(int num){
        int key = hash_function(num);   // key will be something in between 0 and (TABLE_SIZE-1); num can be negative
        Node* node;
        node = Table[key];
        while(node){
            if(node->number == num){
                return node->index;
            }
            node = node->next;
        }
        // not found
        return -1;
    }

    int hash_function(int num) const{
        abs((num*seed)%TABLE_SIZE);
        return num;
    }
private:
    Node* Table[TABLE_SIZE]{};
    int seed = rand();
};

HashSet::HashSet() {
    for(Node* & i : Table){
        i= nullptr;
    }
}

// add this num-index mapping into the table
// this has to be Node** table, because it's not just one pointer, it's an array of pointers.

#endif //LAB11_HASHSET_H
