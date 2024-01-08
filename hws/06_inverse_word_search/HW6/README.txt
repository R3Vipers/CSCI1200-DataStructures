HOMEWORK 6: INVERSE WORD SEARCH


NAME:  < Ryan Ames >


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Stack overflow, geek for geeks, w3schools >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 30 >


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?

The big O of my algorithm is 8^N where N is equal to ((8^l)*2(r*w*h + f*w*h)) + w*h*3l.
I determined 8^N from the generateBoards function which has 8 recursion branches.
2(8^l)(r*w*h + f*w*h) was determined from calling the validate_list function 2 times,
but each time there is only one populated list with just the required or forbidden words.
The validate_list function calls the exist function which has a running time based on the number
of rows and columns. The exist function calls the search function which has 8 recursion branches.
the generateBoards function also has a portion that has a running time based on the rows and columns and
also calls the place function twice and canPlaceWord function once which both have a running time of the
length of the word.


TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

Puzzle1 | time: 1.077s    | solutions: 8
Puzzle2 | time: 1.071s    | solutions: 4
Puzzle3 | time: 1.285s    | solutions: 8
Puzzle4 | time: 1.272s    | solutions: 4
Puzzle5 | time: 1.643s    | solutions: 100
Puzzle6 | time: 1.940s    | solutions: 208
Puzzle7 | time: 2.066s    | solutions: 1
Puzzle8 | time: 3m28.606s | solutions: 4

All puzzles ran around on to two seconds except for Puzzle8 which ran over three minutes.
I believe this is because of the size of the board and the length of the words number of possible permutations.
There is definitely a exponential running time based on the sharp increase of time
from two extra columns.

I created three new test cases. Custom three runs fine and tests the ability of the algorithm for simple
palindromes. Custom 2 runs fin and tests the algorithm for a one word edge case, which works fine. Custom 1
checks for two words that are spelled the same backwards i.e. cat and tac. The algorithm cannot handel this
case because of the validate list function.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!


