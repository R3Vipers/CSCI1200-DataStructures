//
// Created by Ryan Ames on 9/6/2023.
//
#include <iostream>
#include "time.h"


Time::Time() {
    second = 0;
    minute = 0;
    hour = 0;
}

Time::Time(int ahour, int aminute, int asecond) {
    second = asecond;
    minute = aminute;
    hour = ahour;
}

int Time::getSecond() const {
    return second;
}

int Time::getMinute() const {
    return minute;
}

int Time::getHour() const {
    return hour;
}

void Time::setHour(int ahour) {
    hour = ahour;
}

void Time::setMinute(int aminute) {
    minute = aminute;
}

void Time::setSecond(int asecond) {
    second = asecond;
}

void Time::PrintAMPM() {
    if(hour!=12){
        std::cout<<hour%12;
    } else {
        std::cout<<hour;
    }
    if(minute<10){
        std::cout<<":0"<<minute;
    } else {
        std::cout<<":"<<minute;
    }
    if(second<10){
        std::cout<<":0"<<second;
    } else {
        std::cout<<":"<<second;
    }
    if(hour>=12 && hour != 24) {
       std::cout<<" pm\n" ;
    } else if (hour<12){
        std::cout<<" am\n" ;
    } else {
        std::cout<<" am\n" ;
    }
}
