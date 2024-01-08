#include <iostream>
#include <fstream>
#include <vector>
#include "Room.h"
#include "Department.h"
#include "course.h"
#include "Custom.h"

int main(int argc, char* argv[]) {
    //file input stream set to in_str
    std::ifstream in_str(argv[1]);
    //checks if input file can be opened.
    if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    //saving useful command inputs to variables
    std::string outfile = argv[2];
    std::string output_type = argv[3];
    //if there are 5 arguments then the fifth argument will be saved to a variable
    //otherwise an error will be thrown
    if (argc == 5) {
        std::string room_dept = argv[4];
    }
    //All the pieces of data given in a single line are assigned to a variable
    std::string CRN,dept_code,course_code,title,days,start,end,Classroom;
    std::vector<course> Classes;
    //while loop to iterate through the entire text document
    while (in_str >> CRN) {
        // each data point is read to its respective variable
        in_str >> dept_code;
        in_str >> course_code;
        in_str >> title;
        in_str >> days;
        in_str >> start;
        in_str >> end;
        in_str >> Classroom;
        //control logic for making individual course entries for eac day associated with a single class
        //Iterate through each character that designates the day Ex. T, MTW, TRF
        for(char x : days){
            course Course(CRN, dept_code, course_code, title, x, start, end, Classroom);
            //if the output type is department based, only add courses to the vector that have the same department
            if (output_type == "dept") {
                if (Course.getDept_code() == argv[4]) {
                    Classes.push_back(Course);
                }
            //if the output type is room based we either read all the courses into the vector or only the ones
            //in the room specified by the fifth argument
            } else if (output_type == "room") {
                if (argc == 5) {
                    if (Course.getRoom() == argv[4]) {
                        Classes.push_back(Course);
                    }
                } else {
                    Classes.push_back(Course);
                }
            } else {
                Classes.push_back(Course);
            }
        }
    }
    //if the output type is department, a department object is made, then the Classes vector is checked
    //to make sure it is not empty. if it is empty "No data available is printed"
    if(!Classes.empty()) {
        if (output_type == "dept") {
            Department department(Classes, outfile);
            //the courses are sorted using a custom comparator
            department.sort_function(department.getCourses());
            //the courses are printed out with the proper formatting and spacing
            department.print(department.getCourses());
        } else if (output_type == "room") {
            //First a Room object is created
            Room room (Classes, outfile);
            //Checks if there is a fifth argument or not
            if (argc == 5) {
                //if the room was specified then the classes in the room are sorted
                room.sort_function2(room.getCourses2());
                //the courses are printed out with the proper formatting and spacing
                room.print2(room.getCourses2());
            } else {
                //a temporary vector is made to store courses in the same room, while iterating through
                //the rest of the Classes vector
                std::vector<course> temp_vector;
                //all the classes are sorted with preference to the room name first
                room.sort_function2(room.getCourses2());
                //iterate through all the sorted classes
                for (int i = 0; i < room.getCourses2().size() - 1; i++) {
                    temp_vector.push_back(room.getCourses2()[i]);
                    //if the current course is taking place in a different room than the next course in the
                    //list then a room object is created and the room is printed
                    if (room.getCourses2()[i].getRoom() != room.getCourses2()[i + 1].getRoom()) {
                        Room temp_room(temp_vector, outfile);
                        temp_room.print2(temp_room.getCourses2());
                        //the temporary vector is cleared to be loaded with more courses
                        temp_vector.clear();
                    }
                }
                //last course is pushed bck into the temporary vector
                //if in the last iteration of the loop, the courses were not printed out and the
                //vector was not cleared then the last course must be in the same room as the ones currently
                // in the vector
                temp_vector.push_back(room.getCourses2()[room.getCourses2().size() - 1]);
                Room temp_room(temp_vector, outfile);
                temp_room.print2(temp_room.getCourses2());
            }
        } else if (output_type == "custom"){
            //custom output
            Custom custom (Classes, outfile);
            custom.sort_function_time(custom.getCourses());
            custom.print_time(custom.getCourses());
        } else {
            //nothing happens if none of the previous three conditions were met
        }
    } else {
        //if the Classes vector is empty appropriate statement is printed
        std::ofstream fout(outfile, std::ios::app);
        if (fout.is_open())
        {
            fout << "No data available.";
        }
    }
    return 0;
}