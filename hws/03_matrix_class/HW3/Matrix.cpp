//
// Created by Ryan Ames on 9/22/2023.
//
#include <iostream>
#include "Matrix.h"

Matrix::Matrix(const unsigned int& a, const unsigned int& b, const double& fill) {
    //check to see if a and b are valid
    if(a!=0 && b!=0){
        rows = a;
        cols = b;
        //fill the matrix with fill value
        data = new double*[a];
        for(int n = 0; n<a; n++){
            data[n] = new double[b];
            for(int i = 0; i<b; i++){
                data[n][i] = fill;
            }
        }
    } else {
        //if matrix is invalid set data to a nullptr
        rows = 0;
        cols = 0;
        data = nullptr;
        std::cerr << "Invalid row or column index" << std::endl;
    }
}

Matrix::Matrix() {
    //set matrix to size of 0x0 and data is set to nullptr
    rows = 0;
    cols = 0;
    data = nullptr;
}

Matrix::Matrix(const Matrix &m) {
    //check to see if row and row are valid
    if(m.num_rows()>0 && m.num_cols()>0) {
        rows = m.rows;
        cols = m.cols;
        //fill the matrix with the corresponding values for the other matrix
        data = new double*[rows];
        for(int n = 0; n<rows; n++){
            data[n] = new double[cols];
            for(int i = 0; i<cols; i++){
                data[n][i] = m.data[n][i];
            }
        }
    } else {
        std::cerr << "Original Matrix has an invalid size" << std::endl;
    }
}

Matrix::~Matrix() {
    //check to see if data is nullptr
    if(data!=nullptr){
        //deallocate memory for rows
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        //deallocate memory for columns
        delete[] data;
        data = nullptr;
        rows = 0;
        cols = 0;
    }
}

void Matrix::clear() {
    //check to see if data is nullptr
    if(data != nullptr) {
        //deallocate memory for rows
        for (unsigned int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        //deallocate memory for columns
        delete[] data;
        data = nullptr;
        rows = 0;
        cols = 0;
    }
}

bool Matrix::get(const unsigned int& row, const unsigned int& col, double &num) const{
    //check to see if data is nullptr
    if(data != nullptr){
        //set num to the value of data[row][column]
        //passing memory address to directly edit value
        num = data[row][col];
        return true;
    } else {
        std::cerr << "Invalid row or column index" << std::endl;
        return false;
    }
}

bool Matrix::set(const unsigned int& row, const unsigned int& col, const double& value) {
    //check to see if the rows and columns are valid
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        //set matrix value to parameter value
        data[row][col] = value;
        return true;
    } else {
        std::cerr << "Invalid row or column index" << std::endl;
        return false;
    }
}

double* Matrix::get_row(const unsigned int& row) {
    //check to see if data is nullptr and row is valid
    if(data != nullptr && row < rows) {
        //allocate memory for row pointer
        double * new_row = new double[cols];
        //set values from target row
        for(int i = 0; i < cols; i++){
            new_row[i] = data[row][i];
        }
        return new_row;
    } else {
        std::cerr << "Invalid row index" << std::endl;
        return nullptr;
    }
}

double* Matrix::get_col(const unsigned int& col) {
    //check to see if data is nullptr and col is valid
    if(data != nullptr && col < cols) {
        //allocate memory for column pointer
        double* new_col = new double[rows];
        //set values from target column
        for(int i = 0; i < rows; i++){
            new_col[i] = data[i][col];
        }
        return new_col;
    } else {
        std::cerr << "Invalid column index" << std::endl;
        return nullptr;
    }
}

unsigned int Matrix::num_rows() const {
    return rows;
}

unsigned int Matrix::num_cols() const {
    return cols;
}

void Matrix::multiply_by_coefficient(const double& num) {
    //check to see if data is nullptr
    if(data != nullptr){
        //iterate through the matrix and multiply values by coefficient
        for(unsigned int x = 0; x < rows-1; x++) {
            for (unsigned int y = 0; y < cols-1; y++) {
                data[x][y] *= num;
            }
        }
    } else {
        std::cerr << "Matrix has invalid size" << std::endl;
    }
}

void Matrix::swap_row(const unsigned int& source, const unsigned int& target) {
    //check to see if data is nullptr and source and target are valid
    if(data != nullptr && source < rows && target < rows) {
        double temp;
        //save source row to a temporary variable then swap values
        for (int i = 0; i < cols - 1; i++) {
            temp = data[source][i];
            data[source][i] = data[target][i];
            data[target][i] = temp;
        }
    } else {
        std::cerr << "Invalid row index" << std::endl;
    }
}

void Matrix::transpose() {
    //check to see if data is nullptr
    if(data != nullptr){
        //allocate memory for temporary storage
        double** temp_arr = new double*[cols];
        unsigned int num_of_rows = rows;
        unsigned int num_of_cols = cols;
        //reverse rows(x) and cols(y) when reading from data
        for(unsigned int x = 0; x < cols; x++) {
            temp_arr[x] = new double[rows];
            for (unsigned int y = 0; y < rows; y++) {
                temp_arr [x][y] = data[y][x];
            }
        }
        //deallocate current memory
        clear();
        //set the pointer value to the temporary pointer
        data = temp_arr;
        cols = num_of_rows;
        rows = num_of_cols;
    }
}

bool Matrix::add(const Matrix& b) {
    //check to see if data is nullptr and if the rows and columns are valid
    if(rows == b.num_rows() && cols == b.num_cols() && data != nullptr && b.num_cols()>0 && b.num_cols()>0) {
        //iterate through the matrix and add the values of matrix b to its values
        for(unsigned int x = 0; x < cols-1; x++) {
            for (unsigned int y = 0; y < rows-1; y++) {
                data[x][y] += b.data[x][y];
            }
        }
        return true;
    } else {
        std::cerr << "Matrices do not have matching sizes or one or both of the Matrices are of an invalid size" << std::endl;
        return false;
    }
}

bool Matrix::subtract(const Matrix& b) {
    //check to see if data is nullptr and if the rows and columns are valid
    if(rows == b.num_rows() && cols == b.num_cols() && data != nullptr) {
        //iterate through the matrix and subtract the values of matrix b to its values
        for(unsigned int x = 0; x < cols-1; x++) {
            for (unsigned int y = 0; y < rows-1; y++) {
                data[x][y] -= b.data[x][y];
            }
        }
        return true;
    } else {
        std::cerr << "Matrices do not have matching sizes or one or both of the Matrices are of an invalid size" << std::endl;
        return false;
    }
}

Matrix* Matrix::quarter() {
    //check to see if data is nullptr
    if(data != nullptr){
        Matrix* quarter = new Matrix[4];
        //create variables to allow to quarter all four at the same time
        unsigned int x = 1 + ((rows - 1) / 2);
        unsigned int y = 1 + ((cols - 1) / 2);
        unsigned int offset_cols = cols - y;
        unsigned int offset_rows = rows - x;
        //assign the quarters to the pointer array
        Matrix QM(x, y, 0);
        quarter[0] = QM;
        quarter[1] = QM;
        quarter[2] = QM;
        quarter[3] = QM;
        //iterate through one quarter of the matrix and assign values to the four quarters
        for(int i = 0; i < x; i++){
            for(int j = 0; j < y; j++){
                quarter[0].set(i, j, data[i][j]);
                quarter[1].set(i, j, data[i][j + offset_cols]);
                quarter[2].set(i, j, data[i + offset_rows][j]);
                quarter[3].set(i, j, data[i + offset_rows][j + offset_cols]);
            }
        }
        return quarter;
    } else {
        std::cerr << "Matrix has invalid size" << std::endl;
        return nullptr;
    }
}

void Matrix::resize(const unsigned int& row, const unsigned int& col, const double& num) {
    //check to see if data is nullptr and x and y are valid
    if(data != nullptr && row > 0 && col> 0 ){
        //allocate memory for temporary storage
        double** temp = new double*[row];
        for(unsigned int i = 0; i < row; i++) {
            temp[i] = new double[col];
            for (unsigned int k = 0; k < col; k++) {
                //if resize goes out of bounds of the original array set temporary data to fill value
                //preserves original data
                if(i >= rows || k >= cols) {
                    temp [i][k] = num;
                } else {
                    temp [i][k] = data[i][k];
                }
            }
        }
        clear();
        data = temp;
        rows = row;
        cols = col;
    } else {
        data = nullptr;
        cols = 0;
        rows = 0;
        std::cerr << "Matrix has invalid size" << std::endl;
    }
}

Matrix& Matrix::operator=(const Matrix &m) {
    // return current matrix if currently equal
    if (this == &m) {
        return *this;
    }
    //deallocate memory for rows
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    //deallocate memory for columns
    delete[] data;
    // set rows and cols from the other matrix
    rows = m.rows;
    cols = m.cols;
    // allocate memory for the new matrix and copy the data from the other matrix
    data = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
    out << m.num_rows() << " x " << m.num_cols() << " Matrix:"<<std::endl;
    //check to see if the rows and columns are valid
    if(m.num_cols()>0 && m.num_cols()>0) {
        out << "[ ";
        //print all values in order
        //print out a new line for every row
        for(unsigned int x = 0; x < m.num_rows(); x++){
            for(unsigned int y = 0; y < m.num_cols(); y++){
                double temp = 0;
                m.get(x,y,temp);
                out<< temp<<' ';
            }
            if(x != m.num_rows()-1) {
                out<< "\n";
            }
        }
        out << "]\n";
    } else {
        out << "[ ]\n";
    }
    out << "Done printing.\n";
    return out;
}

bool operator==(const Matrix &a, const Matrix &b) {
    //check to see if the rows and columns are valid
    if(a.num_rows() == b.num_rows() && a.num_cols() == b.num_cols() && a.num_rows() > 0 && a.num_rows() > 0){
        for(unsigned int x = 0; x < a.num_rows()-1; x++) {
            //iterate through both matrices and until a non-matching value pair is found or if all values are matching
            for (unsigned int y = 0; y < a.num_cols() - 1; y++) {
                double temp_a=0;
                double temp_b=0;
                if(a.get(x,y,temp_a)!=b.get(x,y,temp_b)) {
                    return false;
                }
            }
        }
    } else if (a.num_rows() == 0 && b.num_rows() == 0){
        return true;
    } else {
        return false;
    }
    return true;
}

bool operator!=(const Matrix &a, const Matrix &b) {
    //check to see if the rows and columns are valid
    if(a.num_rows() == b.num_rows() && a.num_cols() == b.num_cols() && a.num_rows() > 0 && a.num_rows() > 0){
        //iterate through both matrices and until a non-matching value pair is found or if all values are matching
        for(unsigned int x = 0; x < a.num_rows()-1; x++) {
            for (unsigned int y = 0; y < a.num_cols() - 1; y++) {
                double temp_a=0;
                double temp_b=0;
                if(a.get(x,y,temp_a)!=b.get(x,y,temp_b)) {
                    return true;
                }
            }
        }
    } else {
        return true;
    }
    return false;
}
