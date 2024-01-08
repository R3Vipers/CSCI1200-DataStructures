//
// Created by Ryan Ames on 10/10/2023.
//
#include "User.h"
#include "Node.h"


// Constructor for user class
User::User(const std::string &first_name, const std::string &user_age, const std::string &user_gender,
           const std::string &number, const std::string &user_profession, const std::string &institution,
           const std::string &current_lat, const std::string &current_long, const std::string &premium_user,
           const std::string &min_a, const std::string &max_a, const std::string &max_dist,
           const std::string &preference, const std::string &likes) {
    name = first_name;
    int a = std::stoi(user_age);
    age = a;
    gender = user_gender;
    phone_number = number;
    profession = user_profession;
    school = institution;
    double lat = std::stod(current_lat);
    latitude = lat;
    double long_ = std::stod(current_long);
    longitude = long_;
    premium = premium_user;
    int m_a = std::stoi(max_a);
    max_age = m_a;
    int mn_a = std::stoi(min_a);
    min_age = mn_a;
    int m_d = std::stoi(max_dist);
    max_distance = m_d;
    preferred_gender = preference;
    liked_profiles = likes;
}

//default constructor for user class

User::User() {

}

//getter methods for all

std::string User::get_name() {
    return name;
}

int User::get_age() const{
    return age;
}

std::string User::get_profession() {
    return profession;
}

std::string User::get_school() {
    return school;
}

std::string User::get_phone_number() {
    return phone_number;
}

int User::get_max_age() const{
    return max_age;
}

int User::get_min_age() const{
    return min_age;
}

double User::get_lat() const{
    return latitude;
}

double User::get_long() const{
    return longitude;
}

std::string User::get_preferred_gender() {
    return preferred_gender;
}

std::string User::get_gender() {
    return gender;
}

int User::get_max_dist() const{
    return max_distance;
}

std::string User::get_premium() {
    return premium;
}

std::string User::get_likes() {
    return liked_profiles;
}


