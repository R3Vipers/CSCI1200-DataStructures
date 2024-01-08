//
// Created by Ryan Ames on 9/8/2023.
//
#include <iostream>
#ifndef HW2_COURSE_H
#define HW2_COURSE_H



class course {
public:
    //constructor for course class
    course(const std::string& registration_number, const std::string& code, const std::string& course_num,
           const std::string& title, const char& days, const std::string& start, const std::string& end, const std::string& room);
    //getter methods for all variables
    std::string getDept_code() const;
    std::string getCourse_code() const;
    std::string getTitle() const;
    int getDays() const;
    std::string getStart() const;
    std::string getEnd() const;
    std::string getRoom() const;

private:
    //private variable initialization
    std::string CRN;
    std::string dept_code;
    std::string course_code;
    std::string title;
    char days;
    std::string start;
    std::string end;
    std::string room;

    //initialization of days to ints method

    static int days_to_ints(char day);
};

#endif //HW2_COURSE_H
