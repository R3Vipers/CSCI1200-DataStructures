//
// Created by Ryan Ames on 9/6/2023.
//

#include <string>

#ifndef LAB2_ANIMAL_H
#define LAB2_ANIMAL_H

#endif //LAB2_ANIMAL_H

class Time {
public:
    Time();
    Time(int asecond, int aminute, int ahour);

    int getSecond() const;
    int getMinute() const;
    int getHour() const;

    void setSecond(int asecond);
    void setMinute(int aminute);
    void setHour(int ahour);

    void PrintAMPM();

private:
    int second;
    int minute;
    int hour;

};
