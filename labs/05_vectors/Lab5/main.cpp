#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;

int foobar (const std::vector<std::string> &a, int b) {
    int answer = 0;
    for (int i = 0; i < a.size(); i+=b) {
        answer++;
    }
    return answer;
}

//O(a) a = size of vector a

void foo2 (const std::vector<int> &a, std::string &b) {
    b.clear();
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] > 0)
            b.push_back('+');
        else
            b.push_back('-');
    }
}

//O(a) a = size of vector a

std::vector<int> foo3 (const std::vector<int> &a, const std::string &b) {
    return std::vector<int>(b.size(),a.size());
}

//O(1)

int foo3 (const std::vector<std::string> &a, const std::string& b) {
    int ret = 0;
    for (int i=0; i<a.size(); i++){
        ret += (a[i] == b);
    }
    return ret;
}

//O(a) a = size of vector a

std::vector<int> foo4 (const std::vector<int> &a) {
    std::vector<int> answer = a;
    for (int i = 0; i < a.size(); i++) {
        if(a[i] < (a[a.size()-1]*a[a.size()-1])){
            answer.erase(answer.end()-1);
        }
    }
    return answer;
}
//O(a) a = size of vector a


std::vector<int> foo5 (const std::vector<int> &a, int b) {
    std::vector<int> ret;
    for(int i=0; i<a.size(); i++){
        if(a[i] < b){
            ret.insert(ret.end(),a[i]);
        }
    }
    return ret;
}
//O(a) a = size of vector a

//int main() {
//    std::cout << "Hello, World!" << std::endl;
//
//    std::vector<int> myVector;
//    srand((unsigned)time(NULL));
//    int a = 100000; //1 to 20
//    for (int i =0; i < a; i++){
//        int b = rand() % 20 + 1;
//        myVector.push_back(b);
//    }
//
//    int b = 5;
//    std::string bs = "hello";
//
//    auto start = high_resolution_clock::now();
//    foo2(myVector,bs);
//    auto stop = high_resolution_clock::now();
//
//    auto duration = duration_cast<microseconds>(stop - start);
//
//    std::cout << duration.count() << std::endl;
//    return 0;
//}
