//
// Created by Ryan Ames on 12/6/2023.
//
#include <vector>
#include "utilities.h"
#ifndef LAB14_POLYGONS_H
#define LAB14_POLYGONS_H

class Polygon {
public:
    Polygon(const std::string name, const std::vector<Point> points) : points(points){
        if(points.size()<3) throw 1;
    };
    bool is_right_angle (Point a, Point b, Point c) {
        return EqualAngles(Angle(a, b, c), 90.0);
    }
    virtual bool HasAllEqualSides() {
        int len = DistanceBetween(points[0], points[1]);
        for(int i = 0; i< points.size()-2; i++) {
             if(len != DistanceBetween(points[i], points[i+1])) return false;
        }
        return true;
    }
    virtual bool HasAllEqualAngles() {

        return true;
    }
    virtual bool HasARightAngle() {
        return true;
    }
    virtual std::string getName() {return name;}
protected:
    std::string name;
    std::vector<Point> points;
};
class Triangle:public Polygon{
public:
    Triangle(const std::string name, const std::vector<Point> points) : Polygon(name, points){
        if(points.size() != 3) throw 1;
    }
    std::string getName() {return name;}
};
class Quadrilateral: public Polygon{
public:
    Quadrilateral(const std::string name, const std::vector<Point> points) : Polygon(name, points) {
        if (points.size() != 4) throw 1;
    }
    std::string getName() {return name;}
};
class Rectangle: public Quadrilateral {
public:
    Rectangle(const std::string name, const std::vector<Point> points) : Quadrilateral(name, points) {
        if (points.size() != 4) throw 1;
        if (is_right_angle(points[0], points[1], points[2]) && is_right_angle(points[1], points[2], points[3])) throw 1;
    }
    std::string getName() {return name;}
};
class Square: public Quadrilateral {
public:
    Square(const std::string name, const std::vector<Point> points) : Quadrilateral(name, points) {
        if (points.size() != 4) throw 1;
        if (is_right_angle(points[0], points[1], points[2]) && is_right_angle(points[1], points[2], points[3])) throw 1;
        if (EqualSides(DistanceBetween(points[0], points[1]) , DistanceBetween(points[1], points[2])) && EqualSides( DistanceBetween(points[1], points[2]) , DistanceBetween(points[2], points[3]))) throw 1;
    }
    std::string getName() {return name;}
};
class IsoscelesTriangle: public Triangle {
public:
    IsoscelesTriangle(const std::string name, const std::vector<Point> points) : Triangle (name, points) {
        if(points.size() != 3) throw 1;
        if (EqualSides(DistanceBetween(points[0], points[1]) , DistanceBetween(points[1], points[2])) || EqualSides( DistanceBetween(points[0], points[1]) , DistanceBetween(points[2], points[3]))) throw 1;
    }
    std::string getName() {return name;}

};
class EquilateralTriangle: public Triangle {
public:
    EquilateralTriangle(const std::string name, const std::vector<Point> points) : Triangle (name, points) {
        if(points.size() != 3) throw 1;
        if (EqualSides(DistanceBetween(points[0], points[1]) , DistanceBetween(points[1], points[2])) && EqualSides( DistanceBetween(points[0], points[1]) , DistanceBetween(points[2], points[3]))) throw 1;
    }
    std::string getName() {return name;}
};
#endif //LAB14_POLYGONS_H
