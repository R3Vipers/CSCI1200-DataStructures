//
// Created by Ryan Ames on 9/8/2023.
//
#include "Department.h"
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "course.h"
//Department constructor
Department::Department(const std::vector<course> &course, const std::string& file) {
    courses = course;
    file_name = file;
}
//Output method for easy and clean file output
void Department::output(const std::string& text){

    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout << text;
    }
}
//Output method for formatted output
//saves many lines of code
void Department::output_format (const std::string& text, const std::string& LorR, char fill, int size){

    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        if(LorR == "left"){
            fout << std::left << std::setfill(fill) << std::setw(size);
            fout << text;
        } else {
            fout << std::right << std::setfill(fill) << std::setw(size);
            fout << text;
        }

    }
}
//setter method for courses
void Department::setCourses(std::vector<course> c) {
    courses=c;
};
//comparator function that take course code as priority first, then the day,
//then by AM or PM, lastly by the start time
bool compareTwoCourses(const course &a, const course &b) {
    if (a.getCourse_code() != b.getCourse_code())
        return a.getCourse_code() < b.getCourse_code();

    if (a.getDays() != b.getDays())
        return a.getDays() < b.getDays();

    if (a.getStart()[5] != b.getStart()[5])
        return a.getStart()[5] < b.getStart()[5];

    if (a.getStart()[0] != b.getStart()[0]) {
        if (a.getStart()[5] == 'P') {
            return a.getStart()[0] < b.getStart()[0];
        } else if (a.getStart()[5] == 'A'){
            return a.getStart()[0] > b.getStart()[0];
        } else {
            return a.getStart()[0] > b.getStart()[0];
        }
    }

    if (a.getStart()[1] != b.getStart()[1])
        return a.getStart()[1] > b.getStart()[1];

    return (a.getStart()[3] > b.getStart()[3]);

}
//method is used for printing the ints that correspond with the day of the week
//and converting them back into strings
std::string ints_to_days (int d){
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
std::vector<int> longest (const std::vector<course>& courses) {
    std::vector<int> longest;
    int tempT = 0;
    int tempD=0;
    for(course x: courses){
        if(tempT < x.getTitle().size()){
            tempT = x.getTitle().size();
        }
        if(tempD < ints_to_days(x.getDays()).size()){
            tempD = ints_to_days(x.getDays()).size();
        }
    }
    longest.push_back(9);
    longest.push_back(tempT);
    longest.push_back(tempD);
    longest.push_back(10);
    longest.push_back(8);
    return longest;
}
//sorting method uses the comparator compareTwoCourses to sort vector
void Department::sort_function(std::vector<course> c) {
    sort(c.begin(), c.end(), compareTwoCourses);
    setCourses(c);
}
//Prints the first lines for the Department
//Lines are pre-determined and use the longest method to determine spacing with fill characters
void Department::print_first_lines (const std::vector<int>& lengths, const std::string& department) {
    std::string line = "Dept " + department + "\n";

    output(line);

    std::string str="Coursenum";
    output_format(str,"left",' ',lengths[0]+2);

    str="Class Title";
    output_format(str,"left",' ',lengths[1]+2);

    str="Day";
    output_format(str,"left",' ',lengths[2]+2);

    str="Start Time";
    output_format(str,"left",' ',lengths[3]+2);

    str="End Time\n";
    output_format(str,"left",' ',lengths[4]-1);

    str="  ";
    output_format(str,"right",'-',lengths[0]+2);

    str="  ";
    output_format(str,"right",'-',lengths[1]+2);

    str="  ";
    output_format(str,"right",'-',lengths[2]+2);

    str="  ";
    output_format(str,"right",'-',lengths[3]+2);

    str="\n";
    output_format(str,"right",'-',lengths[4]+1);
}
//the print function iterates through the sorted vector and prints the formatted data
void Department::print(const std::vector<course>& c) {
    std::vector<int> lengths = longest(c);
    print_first_lines(lengths, c[0].getDept_code());
    for(const course& x : c) {

        std::string str=x.getCourse_code();
        output_format(str,"left",' ',lengths[0]+2);

        str=x.getTitle();
        output_format(str,"left",' ',lengths[1]+2);

        str=ints_to_days(x.getDays());
        output_format(str,"left",' ',lengths[2]+2);

        str=x.getStart();
        output_format(str,"left",' ',lengths[3]+2);

        str=x.getEnd();
        output_format(str,"left",' ',lengths[4]);
        str = "\n";
        output(str);

    }
    //number of entries output logic
    std::string line = std::to_string(c.size()) + " entries\n";
    output(line);
    line = "\n";
    output(line);
}
//getter method for courses
std::vector<course> Department::getCourses() {
    return courses;
}





