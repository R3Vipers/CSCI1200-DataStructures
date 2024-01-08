//#include <iostream>
//#include <vector>
//#include <unordered_set>
//#include <unordered_map>
//#include "Hashset.h"
//
//using namespace std;
//
//void get_each_digit(vector<int>& digits, int x)
//{
//    if(x >= 10)
//        get_each_digit(digits, x / 10);
//    digits.push_back(x%10);
//}
//
//int get_squares (int n) {
//    vector<int> nums;
//    get_each_digit(nums, n);
//    int square = 0;
//    for(int i : nums){
//        square += i*i;
//    }
//    return square;
//}
//
//bool isHappy(int n) {
//    if(n == 1) return true;
//    unordered_set<int> nums;
//    while(nums.find(get_squares(n))==nums.end()){
//        if(n == 1) return true;
//        n = get_squares(n);
//        nums.insert(n);
//    }
//    if(get_squares(n) == 1)return  true;
//    return false;
//}
//
//bool isHappy2(int n) {
//    if(n == 1) return true;
//    unordered_map<int, int> nums;
//    int temp;
//    while(nums.find(n)==nums.end()){
//        if(n == 1) return true;
//        temp = n;
//        n = get_squares(n);
//        nums[temp] = n;
//    }
//    return false;
//}
//
//bool isHappy3(int n) {
//    if(n==1) return true;
//    HashSet hash;
//    int temp;
//    while(hash.get(n) == -1) {
//        if(n == 1) return true;
//        temp = n;
//        n= get_squares(n);
//        hash.add(temp);
//    }
//    return false;
//}
//
//
//int main() {
//	// Test cases
//	// 2, 4, 5, 6, 17, 18, 20 are not happy numbers.
//	// 1, 7, 10, 13, 19, 23, 28, 68 are happy numbers.
//
//    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};
//
//    for (int n : testCases) {
//        if (isHappy(n)) {
//            std::cout << n << " is a happy number." << std::endl;
//        } else {
//            std::cout << n << " is not a happy number." << std::endl;
//        }
//    }
//    cout<<"-------------------------"<<endl;
//    for (int n : testCases) {
//        if (isHappy2(n)) {
//            std::cout << n << " is a happy number." << std::endl;
//        } else {
//            std::cout << n << " is not a happy number." << std::endl;
//        }
//    }
//    cout<<"-------------------------"<<endl;
//    for (int n : testCases) {
//        if (isHappy3(n)) {
//            std::cout << n << " is a happy number." << std::endl;
//        } else {
//            std::cout << n << " is not a happy number." << std::endl;
//        }
//    }
//
//    return 0;
//}

