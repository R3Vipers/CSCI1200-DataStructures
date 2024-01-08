#include <iostream>
#include <vector>
#include <map>

//bool exits (const std::vector<int>& nums, int num) {
//    for(int n : nums)
//        if(n == num)
//            return true;
//    return false;
//}
//
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    std::vector<int> nums {19, 83, -12, 83, 65, 19, 45, -12, 45, 19, 45};
//    std::map<int,int> map1;
//    for(int i=0;i<nums.size();i++){
//        // if already exists
//        ++map1[nums[i]];
//    }
//    std::vector<int> modes;
//    int count = 0;
//    for(int i=0;i<nums.size();i++){
//        // if already exists
//        if(map1[nums[i]] > count) {
//            modes.clear();
//            modes.push_back(nums[i]);
//            count = map1[nums[i]];
//        } else if (map1[nums[i]] == count) {
//            if(!exits(modes, nums[i]))
//                modes.push_back(nums[i]);
//        }
//    }
//    std::cout<<"Mode(s): "<<std::endl;
//    for(int mode :modes) {
//        std::cout<<mode<<" "<<std::endl;
//    }
////--------------------------------------
//    std::map<int,int> map2;
//    for(int i=0;i<nums.size();i++){
//        // if already exists
//        if(map2.find(nums[i]) == map2.end()) {
//            map2.insert(std::make_pair(nums[i], 1));
//        } else {
//            map2.insert(std::make_pair(nums[i], map2.find(nums[i])->second+=1));
//        }
//    }
//    std::vector<int> modes2;
//    int count2 = 0;
//    for(int i=0;i<nums.size();i++){
//        // if already exists
//        if(map2.find(nums[i])->second > count2) {
//            modes2.clear();
//            modes2.push_back(nums[i]);
//            count2 = map2.find(nums[i])->second;
//        } else if (map2.find(nums[i])->second== count2) {
//            if(!exits(modes2, nums[i]))
//                modes2.push_back(nums[i]);
//        }
//    }
//    std::cout<<"Mode(s): "<<std::endl;
//    for(int mode :modes2) {
//        std::cout<<mode<<" "<<std::endl;
//    }
//    return 0;
//}
