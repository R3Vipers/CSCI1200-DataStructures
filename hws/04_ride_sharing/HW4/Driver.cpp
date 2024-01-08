//
// Created by Ryan Ames on 10/3/2023.
//
#include <iostream>
#include "Driver.h"

Driver::Driver(const std::string& f_name, const std::string& l_name, const std::string& gen, const std::string& year,
               const std::string& phone, const std::string& rate, const std::string& c_lat, const std::string& c_long,
               const std::string& v, const std::string& current_state, const std::string& rider_name, const std::string& rider_lastname,
               const std::string& rider_phone_number) {
    first_name = f_name;
    last_name = l_name;
    gender = gen;
    age = year;
    phone_number = phone;
    rating = rate;
    current_lat = c_lat;
    current_long = c_long;
    vehicle = v;
    state = current_state;
    r_first_name = rider_name;
    r_last_name = rider_lastname;
    r_phone_number = rider_phone_number;
}

std::ostream &operator<<(std::ostream &out, const Driver &d) {
    //out put single line of all the parameters associated with a driver
    out << d.first_name + " " << d.last_name + " " << d.gender + " " << d.age + " " << d.phone_number + " "
        << d.rating + " " << d.current_lat + " " << d.current_long + " " << d.vehicle + " " << d.state + " "
        << d.r_first_name + " " << d.r_last_name + " " << d.r_phone_number << std::endl;
    return out;
}

//setter methods

void Driver::set_r_first_name(const std::string& f_name) {
    r_first_name = f_name;
}

void Driver::set_r_last_name(const std::string& l_name) {
    r_last_name = l_name;
}

void Driver::set_r_phone_number(const std::string& p_number) {
    r_phone_number = p_number;
}

void Driver::set_state(const std::string &d_state) {
    state = d_state;
}

//getter methods

std::string Driver::get_phone_number() {
    return phone_number;
}

std::string Driver::get_lat() {
    return current_lat;
}

std::string Driver::get_long() {
    return current_long;
}

std::string Driver::get_vehicle() {
    return vehicle;
}

std::string Driver::get_state() {
    return state;
}

std::string Driver::get_first_name() {
    return first_name;
}

std::string Driver::get_rating() {
    return rating;
}

std::string Driver::get_r_phone_number() {
    return r_phone_number;
}

std::string Driver::get_last_name() {
    return last_name;
}


