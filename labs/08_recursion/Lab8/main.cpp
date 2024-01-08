#include <iostream>

class Point {
public:
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x_, int y_){
        x = x_;
        y = y_;
    }
    [[nodiscard]] int getX() const{
       return x;
    }
    [[nodiscard]] int getY() const{
        return y;
    }
    void setX(int x_){
        x = x_;
    }
    void setY(int y_){
        y = y_;
    }

    Point& operator= (Point b) {
        x = b.x;
        y = b.y;
        return *this;
    }
private:
    int x,y;
};

int distance_to_origin (Point &point) {
    return abs(point.getX()) + abs(point.getY());
}

bool is_valid_move(int dist, Point &move){
    int new_dist = abs(move.getX()) + abs(move.getY());
    if(dist >= new_dist) {
        return true;
    }
    return false;
}


int find_num_of_paths (Point &start, int dist) {
    if(distance_to_origin(start)==0){
        return 1;
    }
    if((start.getX()<0 ||start.getY() <0 || dist <0) && is_valid_move(dist, start)){
        return 0;
    }
    Point new_point = start;
    new_point = start;
    new_point.setX(start.getX()-1);
    int paths1 = find_num_of_paths(new_point, dist);
    new_point = start;
    new_point.setY(start.getY()-1);
    int paths2 = find_num_of_paths(new_point, dist);
    return paths1 + paths2;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Point start_point(5,5);
    int distance = distance_to_origin(start_point);
    int num_of_paths = find_num_of_paths(start_point, distance);
    std::cout<<num_of_paths<<std::endl;
    return 0;
}
