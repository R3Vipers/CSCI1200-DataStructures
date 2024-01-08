//
// Created by Ryan Ames on 9/8/2023.
//
#include "course.h"


//the week days are converted to ints 1-5, monday being 1 and Friday being 5
//easier to sort ints than to sort strings in non-alphanumeric order
int course::days_to_ints (char day){
    int x=0;
    if(day=='M'){
        x = 1;
    } else if(day == 'T') {
        x = 2;
    } else if(day == 'W') {
        x = 3;
    } else if(day == 'R'){
        x = 4;
    } else if(day == 'F') {
        x = 5;
    } else {

    }
    return x;
}

//implementation of course constructor

course::course(const std::string &registration_number, const std::string& code, const std::string& course_num, const std::string &name, const char& day, const std::string& start_time,
               const std::string& end_time, const std::string &classroom) {
    CRN = registration_number;
    dept_code =code;
    course_code = course_num;
    title=name;
    days  = days_to_ints(day);
    start=start_time;
    end=end_time;
    room=classroom;

}

//implementation of all getter methods

std::string course::getDept_code() const {
    return dept_code;
}

std::string course::getCourse_code() const {
    return course_code;
}

std::string course::getTitle() const {
    return title;
}

int course::getDays() const {
    return days;
}

std::string course::getStart() const {
    return start;
}

std::string course::getEnd() const {
    return end;
}

std::string course::getRoom() const {
    return room;
}

