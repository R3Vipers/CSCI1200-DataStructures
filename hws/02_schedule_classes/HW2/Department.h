//
// Created by Ryan Ames on 9/8/2023.
//

#ifndef HW2_DEPARTMENT_H
#define HW2_DEPARTMENT_H

#include <vector>
#include "course.h"

class Department {
public:
    //Department constructor
    Department(const std::vector<course> &course, const std::string& file);
    //initializing member methods
    void sort_function(std::vector<course> courses);
    void print(const std::vector<course>& courses);
    std::vector<course> getCourses();
    void setCourses(std::vector<course> c);
    void output(const std::string &text);
private:
    //initializing variable names
    std::vector<course> courses;
    std::string file_name;
    //initializing private member functions
    void print_first_lines(const std::vector<int> &lengths, const std::string &department);

    void output_format(const std::string &text, const std::string &LorR, char fill, int size);
};
#endif //HW2_DEPARTMENT_H
;