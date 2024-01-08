//
// Created by Ryan Ames on 10/3/2023.
//

#ifndef HW4_DRIVER_H
#define HW4_DRIVER_H

#include <string>

class Driver {
public:
    //constructor with all 13 parameters
    Driver(const std::string& f_name, const std::string& l_name, const std::string& gen, const std::string& year, const std::string& phone,
           const std::string& rate, const std::string& c_lat, const std::string& c_long, const std::string& vehicle,
           const std::string& current_state, const std::string& rider_name, const std::string& rider_lastname,
           const std::string& rider_phone_number);
    //<< operator overload
    friend std::ostream& operator<<(std::ostream& out, const Driver& m);
    //setter methods
    void set_r_first_name(const std::string& first_name);
    void set_r_last_name(const std::string& last_name);
    void set_r_phone_number(const std::string& phone_number);
    void set_state(const std::string& state);
    //getter methods
    std::string get_phone_number();
    std::string get_rating();
    std::string get_first_name();
    std::string get_last_name();
    std::string get_lat();
    std::string get_long();
    std::string get_vehicle();
    std::string get_state();
    std::string get_r_phone_number();
private:
    std::string first_name, last_name, gender, age, phone_number, rating, current_lat, current_long,
    vehicle, state, r_first_name, r_last_name, r_phone_number;
};
#endif //HW4_DRIVER_H
