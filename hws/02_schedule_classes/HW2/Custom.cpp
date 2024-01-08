//
// Created by Ryan Ames on 9/12/2023.
//
#include "Custom.h"
#include <algorithm>
#include <utility>
#include <fstream>
//defining Custom class constructor
Custom::Custom(const std::vector<course> &course, const std::string& file) {
    courses = course;
    file_name = file;
}
//ofstream function to make output simple and clean
void Custom::output (const std::string& text){

    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout << text;
    }
}
//sorting method that orders classes based on start time.
bool Custom::compareTwoTimes(const course &a, const course &b) {

    if (a.getStart()[5] != b.getStart()[5])
        return a.getStart()[5] < b.getStart()[5];

    if (a.getStart()[0] != b.getStart()[0])
        return a.getStart()[0] > b.getStart()[0];

    if (a.getStart()[1] != b.getStart()[1])
        return a.getStart()[1] < b.getStart()[1];

    return (a.getStart()[3] > b.getStart()[3]);

}
//sort function is called and then courses are set based on newly sorted vector
void Custom::sort_function_time(std::vector<course> c) {
    sort(c.begin(), c.end(), compareTwoTimes);
    setCourses(c);
}

void Custom::print_time(const std::vector<course> &c) {
    int temp = 0;
    int num = 0;
    std::string time;
    std::vector<course> temp_vector;
    //all the courses are iterated through to find the start time or times with the most entries
    for(int i = 0; i < c.size()-1; i++){
        temp_vector.push_back(c[i]);
        if(c[i].getStart()!=c[i+1].getStart()) {
            if(temp_vector.size()>temp) {
               temp =  temp_vector.size();
               num = temp_vector.size();
               time = c[i].getStart() + ", ";
            } else if(temp_vector.size()==temp) {
                time += c[i].getStart() + ", ";
            } else {

            }
            temp_vector.clear();
        }
    }
    //last element case logic
    temp_vector.push_back(c[c.size()-1]);
    if(temp_vector.size()>temp) {
        temp =  temp_vector.size();
        time = c[c.size()-1].getStart() + " ";
    }
    if(temp_vector.size()==temp) {
        time += c[c.size()-1].getStart() + " ";
    }
    //output
    std::string line = "The busiest time(s) is(are): " + time + std::to_string(num) + " classes start at that time\n";
    output(line);
}

//definitions for getter and setter methods
std::vector<course> Custom::getCourses() {
    return courses;
}

void Custom::setCourses(std::vector<course> c) {
    courses = std::move(c);
}


