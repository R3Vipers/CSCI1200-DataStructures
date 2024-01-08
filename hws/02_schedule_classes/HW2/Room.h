//
// Created by Ryan Ames on 9/8/2023.
//

#ifndef HW2_ROOM_H
#define HW2_ROOM_H

#include "course.h"

class Room {

public:
    //constructor for Room class
    Room(std::vector<course> room, const std::string& file);
    //initializing public member methods
    std::vector<course> getCourses2() const;

    void setCourses2(std::vector<course> course_vector);

    void sort_function2(std::vector<course> courses);

    void print2(const std::vector<course>& courses);

    void output(const std::string &text);

private:
    //initializing private variables
    std::vector<course> courses;
    std::string file_name;
    //initializing private member functions
    void print_first_lines2(const std::vector<int> &lengths, const std::string &room);

    void output_format(const std::string &text, const std::string& LorR, char fill, int size);
};

#endif //HW2_ROOM_H
