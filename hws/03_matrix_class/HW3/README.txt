HOMEWORK 3: MATRIX CLASS


NAME:  < Ryan Ames >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<
Online resources:
https://cplusplus.com/doc/tutorial/pointers/
https://www.w3schools.com/cpp/cpp_pointers.asp
https://www.geeksforgeeks.org/copy-constructor-in-cpp/

mentors: Braeden

office hours
>
Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get --> O(1)

set --> O(1)

num_rows --> O(1)

get_column --> O(n)

operator<< --> O(mn)

quarter --> O((mn)^3)

operator== --> O((mn)^2)

operator!= --> O((mn)^2)

swap_rows --> O(n)

rref (provided in matrix_main.cpp) --> O((mn)^3)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

