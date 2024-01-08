//
// Created by Ryan Ames on 9/22/2023.
//

#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H
class Matrix {
public:
    //constructors
    Matrix(const unsigned int& a, const unsigned int& b, const double& fill);
    Matrix();
    Matrix(const Matrix& m);
    //Destructor
    ~Matrix();
    //Clear method
    void clear();
    //getter / setter methods
    bool get(const unsigned int& x, const unsigned int& y, double& num) const;
    bool set(const unsigned int& x, const unsigned int&  y, const double& num);
    double* get_row(const unsigned int& row);
    double* get_col(const unsigned int& col);
    unsigned int num_rows() const;
    unsigned int num_cols() const;
    //member functions
    void multiply_by_coefficient(const double &num);
    void swap_row(const unsigned int& source, const unsigned int& target);
    void transpose();
    bool add(const Matrix& b);
    bool subtract(const Matrix& b);
    Matrix* quarter();
    //extra credit resize method
    void resize(const unsigned int& x, const unsigned int& y, const double& num);
    //member operator overload
    Matrix& operator=(const Matrix& m);
private:
    //member variables
    double **data;
    unsigned int rows;
    unsigned int cols;
};
//nonmember operator overloads
std::ostream& operator<<(std::ostream& out, const Matrix& m);
bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);

#endif //HW3_MATRIX_H
