//
// Created by Ryan Ames on 9/12/2023.
//

#include <vector>
#include "course.h"

#ifndef HW2_CUSTOM_H
#define HW2_CUSTOM_H
class Custom {
public:
    //constructor for Custom class
    Custom(const std::vector<course> &course, const std::string& file);

    //initiations for all member functions

    void sort_function_time(std::vector<course> courses);
    void print_time(const std::vector<course>& courses);
    std::vector<course> getCourses();
    void setCourses(std::vector<course> c);

    void output(const std::string &text);

private:
    //initializing variables
    std::vector<course> courses;
    std::string file_name;
    //initializing comparator method
    static bool compareTwoTimes(const course &a, const course &b);

};
#endif //HW2_CUSTOM_H
