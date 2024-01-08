//
// Created by Ryan Ames on 9/8/2023.
//
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "Room.h"

//Constructor for Room class
Room::Room(std::vector<course> room, const std::string& file) {
    courses = std::move(room);
    file_name = file;
}
//output method for clean and simple text file output
void Room::output (const std::string& text){
    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout << text;
    }
}
//method outputs formatted text to text file
void Room::output_format (const std::string& text, const std::string& LorR, char fill, int size){
    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        if(LorR == "left"){
            fout << std::left << std::setfill(fill) << std::setw(size);
            fout << text;
        } else {
            fout << std::right << std::setfill(fill) << std::setw(size);
            fout <<text;
        }
    }
}
//comparator the prioritizes rooms, then course day, then start time
bool compareTwoCourses2(const course &a, const course &b) {
    if (a.getRoom() != b.getRoom())
        return a.getRoom() < b.getRoom();

    if (a.getDays() != b.getDays())
        return a.getDays() < b.getDays();

    if (a.getStart()[5] != b.getStart()[5])
        return a.getStart()[5] < b.getStart()[5];

    if (a.getStart()[0] != b.getStart()[0]) {
        if (a.getStart()[5] == 'P') {
            return a.getStart()[0] > b.getStart()[0];
        } else if (a.getStart()[5] == 'A'){
            return a.getStart()[0] < b.getStart()[0];
        } else {
            return a.getStart()[0] > b.getStart()[0];
        }
    }
    if (a.getStart()[1] != b.getStart()[1])
        return a.getStart()[1] < b.getStart()[1];

    return (a.getStart()[3] > b.getStart()[3]);
}
//Prints the first lines for the Department
//Lines are pre-determined and use the longest method to determine spacing with fill characters
void Room::print_first_lines2 (const std::vector<int>& lengths, const std::string& room) {
    std::string line = "Room " + room + "\n";
    output(line);

    std::string str="Dept";
    output_format(str,"left",' ',lengths[0]+2);

    str="Coursenum";
    output_format(str,"left",' ',lengths[1]+2);

    str="Class Title";
    output_format(str,"left",' ',lengths[2]+2);

    str="Day";
    output_format(str,"left",' ',lengths[3]+2);

    str="Start Time";
    output_format(str,"left",' ',lengths[4]+2);

    str="End Time\n";
    output_format(str,"left",' ',lengths[5]);

    str="  ";
    output_format(str,"right",'-',lengths[0]+2);

    str="  ";
    output_format(str,"right",'-',lengths[1]+2);

    str="  ";
    output_format(str,"right",'-',lengths[2]+2);

    str="  ";
    output_format(str,"right",'-',lengths[3]+2);

    str="  ";
    output_format(str,"right",'-',lengths[4]+2);

    str="\n";
    output_format(str,"right",'-',lengths[5]+1);
}
//method is used for printing the ints that correspond with the day of the week
//and converting them back into strings
std::string ints_to_days2 (int d){
    std::string x;
    if(d==1){
        x = "Monday";
    } else if(d == 2) {
        x = "Tuesday";
    } else if(d == 3) {
        x = "Wednesday";
    } else if(d == 4){
        x = "Thursday";
    } else if(d == 5) {
        x = "Friday";
    } else {
        x = "Monday";
    }
    return x;
}
//the method longest integrates through the vector of courses and finds the longest
//string sizes from some of the parameters of a course. Some will not vary in size therefore
//they are set directly.
std::vector<int> longest2 (const std::vector<course>& courses) {
    std::vector<int> longest;
    int tempT = 11;
    int tempD=0;
    int tempC=4;
    for(course x: courses){
        if(tempT < x.getTitle().size()){
            tempT = x.getTitle().size();
        }
        if(tempD < ints_to_days2(x.getDays()).size()){
            tempD = ints_to_days2(x.getDays()).size();
        }
        if(tempC < x.getDept_code().size()) {
            tempC = x.getDept_code().size();
        }
    }
    longest.push_back(tempC);
    longest.push_back(9);
    longest.push_back(tempT);
    longest.push_back(tempD);
    longest.push_back(10);
    longest.push_back(8);
    return longest;
}
//getter method for courses
std::vector<course> Room::getCourses2() const {
    return courses;
}
//setter method for courses
void Room::setCourses2(std::vector<course> course_vector) {
    courses = course_vector;
}
//sorting and setting method for courses
void Room::sort_function2(std::vector<course> c) {
    sort(c.begin(), c.end(), compareTwoCourses2);
    setCourses2(c);
}
//the print function iterates through the sorted vector and prints the formatted data
void Room::print2(const std::vector<course> &c) {
    std::vector<int> lengths = longest2(c);
    print_first_lines2(lengths, c[0].getRoom());
    for(const course& x : c) {

        std::string str=x.getDept_code();
        output_format(str,"left",' ',lengths[0]+2);

        str=x.getCourse_code();
        output_format(str,"left",' ',lengths[1]+2);

        str=x.getTitle();
        output_format(str,"left",' ',lengths[2]+2);

        str=ints_to_days2(x.getDays());
        output_format(str,"left",' ',lengths[3]+2);

        str=x.getStart();
        output_format(str,"left",' ',lengths[4]+2);

        str=x.getEnd();
        output_format(str,"left",' ',lengths[5]);
        str = "\n";
        output(str);
    }
    //number of entries output logic
    std::string line = std::to_string(c.size()) + " entries\n";
    output(line);
    line = "\n";
    output(line);
}




