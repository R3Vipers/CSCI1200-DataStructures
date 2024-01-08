#include <iostream>
#include <set>
#include <fstream>
#include "Search.h"

using namespace std;

int main(int argc, char* argv[]) {

    //take in arguments
    std::string user_input = argv[1];
    std::string output_file = argv[2];
    std::string output_type = argv[3];
    //create necessary variables
    vector<vector<char>> board {};
    vector<string> words {};
    Search search;
    vector<string> bad_words {};

    std::ifstream in_user(user_input);
    //checks if input file can be opened.
    if (!in_user.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    //open output stream to output file
    std::ofstream fout(output_file, std::ios::app);

    //create input files variables
    int rows;
    int cols;
    string g_or_b;
    string word;

    //read input file
    in_user >> cols;
    in_user >> rows;
    while(in_user >> g_or_b){
        in_user >> word;
        if(g_or_b == "+"){
            words.push_back(word);
        } else {
            bad_words.push_back(word);
        }
    }

    //if there are no word, then there ar no solutions
    if(words.empty()){
        if (fout.is_open())fout << "No solutions found"<<endl;
        return 0;
    }

    //generate boards nto a set to remove duplicates
    set<vector<vector<char>>> boards = search.generateWordSearchBoards(rows, cols, words, bad_words);
    //vector of alphabet
    vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    //iterate through each board if an & is found make 26 iterations of said board and ad them to the end
    //if there is more than one it continues to make more iterations
    std::set<vector<vector<char>>>::iterator itr = boards.begin();
    std::set<vector<vector<char>>>::iterator itr2;
    for (vector<vector<char>> b : boards) {
        for (int x = 0; x < b.size(); x++) {
            for(int y = 0; y < b[0].size(); y++) {
                if(b[x][y] == '&'){
                    for(char letter : letters){
                        b[x][y] = letter;
                        if(search.validate_list(b,words, bad_words)) boards.insert(b);
                    }
                }
            }
        }
    }
    //clear the forbidden word list and just add &s to get rid of any straggling boards
    bad_words.clear();
    bad_words.emplace_back("&");
    int count = 0;
    //delete boards that still contain &s
    while (itr != boards.end()) {
        if (search.validate_list(const_cast<vector<vector<char>> &>(*itr), words, bad_words)) {
            count++;
            itr++;
        }
        else {
            itr2 = itr;
            itr++;
            boards.erase(itr2);
        }
    }
    //if there are no boards left, then there are no solutions
    if(boards.empty()){
        if (fout.is_open())fout << "No solutions found"<<endl;
        return 0;
    }
    //print out all solutions
    if(output_type == "all_solutions") {
        if (fout.is_open())fout << count << " solution(s)" << endl;
        for (const vector<vector<char>> &b: boards) {
            if (fout.is_open())fout << "Board: " << endl << "  ";
            int x = 1;
            for (const vector<char> &row: b) {
                for (const char &letter: row) if (fout.is_open())fout << letter;
                if (fout.is_open()) {
                    fout << endl;
                    if (x < rows) {
                        fout << "  ";
                    }
                }
                x++;
            }
        }
        if (fout.is_open())fout << endl;
    //else print out just the first solution
    } else if (output_type == "one_solution"){
        if (fout.is_open())fout << "Board: " << endl << "  ";
        int x = 1;
        for (const vector<char> &row: *boards.begin()) {
            for (const char &letter: row) if (fout.is_open())fout << letter;
            if (fout.is_open()) {
                fout << endl;
                if (x < rows) {
                    fout << "  ";
                }
            }
            x++;
        }
        if (fout.is_open())fout << endl;
    }

    return 0;
}
