//
// Created by Ryan Ames on 10/3/2023.
//
#include <iostream>
#include "Rider.h"

Rider::Rider(const std::string &f_name, const std::string &l_name, const std::string &gen, const std::string &year,
             const std::string &phone, const std::string &rate, const std::string &pick_location,
             const std::string &pick_lat, const std::string &pick_long, const std::string &drop_location,
             const std::string &drop_lat, const std::string &drop_long, const std::string &v,
             const std::string &current_state, const std::string& driver_name, const std::string& driver_lastname,
             const std::string& driver_phone_number) {

    first_name = f_name;
    last_name = l_name;
    gender = gen;
    age = year;
    phone_number = phone;
    rating = rate;
    dropoff_location = drop_location;
    dropoff_lat = drop_lat;
    dropoff_long = drop_long;
    pickup_location = pick_location;
    pickup_lat = pick_lat;
    pickup_long = pick_long;
    vehicle = v;
    state = current_state;
    d_first_name = driver_name;
    d_last_name = driver_lastname;
    d_phone_number = driver_phone_number;
}

std::ostream &operator<<(std::ostream &out, const Rider &r) {
    //out put single line of all the parameters associated with a driver
    out << r.first_name + " " << r.last_name + " " << r.gender + " " << r.age + " " << r.phone_number + " "
        << r.rating + " " << r.pickup_location + " " << r.pickup_lat + " " << r.pickup_long + " " << r.dropoff_location + " "
        << r.dropoff_lat + " " << r.dropoff_long + " " << r.vehicle + " " << r.state + " " << r.d_first_name + " "
        << r.d_last_name + " " << r.d_phone_number  << std::endl;
    return out;
}

//setter methods

void Rider::set_d_first_name(const std::string &f_name) {
    d_first_name = f_name;
}

void Rider::set_d_last_name(const std::string &l_name) {
    d_last_name = l_name;
}

void Rider::set_d_phone_number(const std::string &p_number) {
    d_phone_number = p_number;
}

void Rider::set_state(const std::string &r_state) {
    state = r_state;
}

//getter methods

std::string Rider::get_phone_number() {
    return phone_number;
}

std::string Rider::get_lat() {
    return pickup_lat;
}

std::string Rider::get_long() {
    return pickup_long;
}

std::string Rider::get_vehicle() {
    return vehicle;
}

std::string Rider::get_state() {
    return state;
}

std::string Rider::get_dropoff_location() {
    return dropoff_location;
}

std::string Rider::get_pickup_location() {
    return pickup_location;
}

std::string Rider::get_first_name() {
    return first_name;
}

std::string Rider::get_last_name() {
    return last_name;
}



