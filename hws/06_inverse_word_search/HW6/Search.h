//
// Created by Ryan Ames on 10/20/2023.
//

#ifndef HW6_SEARCH_H
#define HW6_SEARCH_H
#include <iostream>
#include <vector>
using namespace std;

class Search {
public:
    // search word[index] at locations (i,j)
    bool search(vector<vector<char>>& board, const string& word, int i, int j, int index, const string& direction){
        // base case
        if(index>=word.length()){
            // when index is equal to word length, it means our search job is done.
            // and in this case, we don't care if i or j is out of bounds of not.
            //cout<<"true"<<endl;
            return true;
        }

        // boundary checking
        if(i<0 || i>=board.size()){
            return false;
        }
        if(j<0 || j>=board[0].size()){
            return false;
        }

        // if not equal, then this is not the path we are looking for.
        if(board[i][j] != word[index]){
            return false;
        }

        char c = board[i][j];
        //cout<<c<< i << j <<endl;
        // if it's found, we change it to '0' so we can guarantee to not reuse it while we are still on this path.

        // general case
        // if search job is still incomplete, then let's continue searching letter i in all four directions, and if we can find the word in any of these four directions, then we are good.
        if(direction == "right" || direction.empty()) {
            if(search(board, word, i, j + 1, index + 1, "right")){
                return true;
            }
        }

        if(direction == "left" || direction.empty()) {
            if(search(board, word, i, j - 1, index + 1, "left")){
                return true;
            }
        }

        if(direction == "down" || direction.empty()) {
            if(search(board, word, i + 1, j, index + 1, "down")){
                return true;
            }
        }
        if(direction == "up" || direction.empty()) {
            if(search(board, word, i - 1, j, index + 1, "up")){
                return true;
            }
        }
        if(direction == "right_down" || direction.empty()) {
            if(search(board, word, i + 1, j + 1, index + 1, "right_down")){
                return true;
            }
        }
        if(direction == "left_down" || direction.empty()) {
            if(search(board, word, i + 1, j - 1, index + 1, "left_down")){
                return true;
            }
        }
        if(direction == "right_up" || direction.empty()) {
            if(search(board, word, i - 1, j + 1, index + 1, "right_up")){
                return true;
            }
        }
        if(direction == "left_up" || direction.empty()) {
            if(search(board, word, i - 1, j - 1, index + 1, "left_up")){
                return true;
            }
        }
        // if we reach here, then the word can't be found.
        //return space to original character
        board[i][j] = c;
        return false;
    }

    bool exist(vector<vector<char>>& board, const string& word) {
        int m=board.size();
        int n=board[0].size();
        // find the first letter of this word
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                // if it's true, return true; if not, continue search at next (i,j)
                if(board[i][j] == word[0]) {
                    if (search(board, word, i, j, 0, "")) {
                        return true;
                    }
                }
            }
        }
        // if we reach here, then the word can't be found.
        return false;
    }
    bool validate_list (vector<vector<char>>& board, const vector<string>& good_words, const vector<string>& bad_words){
        //check board for required words
        for (const string& word: good_words){

            if(!exist(board, word)) return false;
        }
        //check board for forbidden words
        for (const string& word: bad_words){

            if(exist(board, word)) return false;
        }
        return true;
    }


    bool canPlaceWord(vector<vector<char>>& grid, const int& row, const int& col, const string& word, const int& direction) {
        int numRows = grid.size();
        int numCols = grid[0].size();
        int len = word.length();

        // Check if the word fits horizontally
        if (direction == 0 && col + len <= numCols) {
            for (int i = 0; i < len; i++) {
                if (grid[row][col + i] != '&' && grid[row][col + i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        // Check if the word fits vertically
        if (direction == 1 && row + len <= numRows) {
            for (int i = 0; i < len; i++) {
                if (grid[row + i][col] != '&' && grid[row + i][col] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        if (direction == 2 && -1 <= col - len) {
            for (int i = 0; i < len; i++) {
                if (grid[row][col - i] != '&' && grid[row][col - i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        if (direction == 3 && -1 <= row - len) {
            for (int i = 0; i < len; i++) {
                if (grid[row - i][col] != '&' && grid[row - i][col] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        //diagonals

        if (direction == 4 && -1 <= row - len && -1 <= col - len) {
            for (int i = 0; i < len; i++) {
                if (grid[row - i][col - i] != '&' && grid[row - i][col - i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        if (direction == 5 && row + len <= numRows && -1 <= col - len) {
            for (int i = 0; i < len; i++) {
                if (grid[row + i][col - i] != '&' && grid[row + i][col - i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        if (direction == 6 && -1 <= row - len && col + len <= numCols) {
            for (int i = 0; i < len; i++) {
                if (grid[row - i][col + i] != '&' && grid[row - i][col + i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        if (direction == 7 && row + len <= numRows && col + len <= numCols) {
            for (int i = 0; i < len; i++) {
                if (grid[row + i][col + i] != '&' && grid[row + i][col + i] != word[i]) {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    string placeWord(vector<vector<char>>& grid, const int& row, const int& col, const string& word, const int& direction) {
        int len = word.length();
        string old = "";
        //place words in the desired orientation
        if (direction == 0) {
            for (int i = 0; i < len; i++) {
                old += grid[row][col + i];
                grid[row][col + i] = word[i];
            }
        } else if (direction == 1) {
            for (int i = 0; i < len; i++) {
                old += grid[row + i][col];
                grid[row + i][col] = word[i];
            }
        } else if (direction == 2) {
            for (int i = 0; i < len; i++) {
                old += grid[row][col - i];
                grid[row][col - i] = word[i];
            }
        } else if (direction == 3) {
            for (int i = 0; i < len; i++) {
                old += grid[row - i][col];
                grid[row - i][col] = word[i];
            }
        // diagonals
        } else if (direction == 4) {
            for (int i = 0; i < len; i++) {
                old += grid[row - i][col - i];
                grid[row - i][col - i] = word[i];
            }
        } else if (direction == 5) {
            for (int i = 0; i < len; i++) {
                old += grid[row + i][col - i];
                grid[row + i][col - i] = word[i];
            }
        } else if (direction == 6) {
            for (int i = 0; i < len; i++) {
                old += grid[row - i][col + i];
                grid[row - i][col + i] = word[i];
            }
        } else if (direction == 7) {
            for (int i = 0; i < len; i++) {
                old += grid[row + i][col + i];
                grid[row + i][col + i] = word[i];
            }
        }
        return old;
    }



    void generateBoards(set<vector<vector<char>>>& result, vector<vector<char>>& board, vector<string>& good_words, vector<string>& bad_words, vector<string>& old_words, int count) {
        int numRows = board.size();
        int numCols = board[0].size();
        //return if forbidden words are in the board
        if(!validate_list(board, {}, bad_words)){
            return;
        }
        //return and insert board if every required word is present
        if(validate_list(board, good_words, {})){
            result.insert(board);
            return;
        }

        string word = good_words[count];
        //iterate through each index
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                for (int direction = 0; direction < 8; direction++) {
                    //check if a word can be placed at current index
                    if (canPlaceWord(board, row, col, word, direction)) {
                        //save old letters on board
                        old_words.push_back(placeWord(board, row, col, word, direction));
                        generateBoards(result, board, good_words, bad_words, old_words, count+1);
                        //replace old letters after recursion
                        placeWord(board, row, col, old_words.back(), direction);
                        old_words.pop_back();
                    }
                }
            }
        }
    }
    //driver function for generateBoards
    set<vector<vector<char>>> generateWordSearchBoards(int& rows, int& cols, vector<string>& good_words, vector<string>& bad_words) {
        set<vector<vector<char>>> result;
        vector<vector<char>> board(rows, vector<char> (cols, '&'));
        vector<string> old;
        int count = 0;
        generateBoards(result, board, good_words, bad_words, old, count);

        return result;
    }
};
#endif //HW6_SEARCH_H
