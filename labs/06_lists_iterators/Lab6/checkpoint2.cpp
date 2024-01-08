//
// Created by Ryan Ames on 10/4/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>


template <class T>
void print(std::list<T> &data, const std::string &label) {
    std::cout << label << " ";
    typename std::list<T>::iterator i;
    for (i = data.begin(); i != data.end(); i++) {
        std::cout << " " << *i;
    }
    std::cout << std::endl;
}


template <class T>
void reverse(std::list<T> &data) {

    // FILL IN THIS FUNCTION
    T temp;
    int num = data.size();
    int count;
    typename std::list<T>::iterator i = data.end();
    for (count = 0; count < num; count++) {
        temp = data.front();
        data.pop_front();
        i = data.insert(i, temp);
    }
}


//int main() {
//    std::list<int> data;
//    data.push_back(1);
//    data.push_back(2);
//    data.push_back(3);
//    data.push_back(4);
//    data.push_back(5);
//    data.push_back(6);
//    data.push_back(7);
//
//    print(data,"before:");
//    reverse(data);
//    print(data,"after: ");
//
//    std::list <std::string> data2;
//    data2.push_back("apple");
//    data2.push_back("banana");
//    data2.push_back("carrot");
//    data2.push_back("date");
//
//    print(data2,"before:");
//    reverse(data2);
//    print(data2,"after: ");
//}


