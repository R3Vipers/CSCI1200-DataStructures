//
// Created by Ryan Ames on 10/10/2023.
//

#ifndef HW5_USER_H
#define HW5_USER_H

#include <string>
#include "Node.h"

class User {
public:
    //constructors for User class
    User(const std::string &first_name, const std::string &user_age, const std::string &user_gender,
         const std::string &number, const std::string &user_profession, const std::string &institution,
         const std::string &current_lat, const std::string &current_long, const std::string &premium_user,
         const std::string &min_a, const std::string &max_a, const std::string &max_dist,
         const std::string &preference, const std::string &likes);
    //default constructor for User class
    User();
    //getter methods for private variables
    std::string get_name();
    int get_age() const;
    std::string get_profession();
    std::string get_school();
    std::string get_phone_number();
    int get_max_age() const;
    int get_min_age() const;
    double get_lat() const;
    double get_long() const;
    std::string get_preferred_gender();
    std::string get_gender();
    int get_max_dist() const;
    std::string get_premium();
    std::string get_likes();
    bool operator < (const User& user2){
        return phone_number < user2.phone_number;
    }
private:
    //strings for user data
    std::string name, gender, phone_number, profession, school, premium,
    preferred_gender, liked_profiles;
    //integers for User age, preferred age, max distance
    int age, max_age, min_age, max_distance;
    //doubles for User latitude and longitude
    double latitude, longitude;

};
#endif //HW5_USER_H
