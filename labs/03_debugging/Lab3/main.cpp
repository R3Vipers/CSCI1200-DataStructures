#include <iostream>
#include <valarray>

void compute_squares (double a[], double b[], int size){
    double *Apointer;
    Apointer = a;
    double *Bpointer;
    Bpointer = b;
    for(int i = 0; i<size; i++){
        *(Apointer+i) = sqrt(*(Apointer+i));
        *(Bpointer+i) = *(Apointer+i);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
//    const int n = 10;
//    double a[n];
//    double *p;
//    p = a;
//    int i;
//    for(i = 0; i<10; i++){
//        *(p+i) = sqrt(double(i));
//    }
    int n = 10;
    double a[] {1,2,3,4,5,6,7,8,9,10};
    double b[n];

    srand(time(nullptr));

    compute_squares(a,b,n);

    for(int i=0;i<n;i++)
        std::cout<<b[i]<<" ";
    std::cout<<std::endl;
    return 0;
}
