//
// Created by Ryan Ames on 10/3/2023.
//

#ifndef HW4_RIDER_H
#define HW4_RIDER_H

#include <string>

class Rider {
public:
    //constructor with all 17 parameters
    Rider(const std::string& f_name, const std::string& l_name, const std::string& gen, const std::string& year, const std::string& phone,
           const std::string& rate, const std::string& pickup_location, const std::string& pickup_lat, const std::string& pickup_long,
           const std::string& dropoff_location, const std::string& dropoff_lat, const std::string& dropoff_long, const std::string& vehicle,
           const std::string& current_state, const std::string& driver_name, const std::string& driver_lastname,
          const std::string& driver_phone_number);
    //<< operator overload
    friend std::ostream& operator<<(std::ostream& out, const Rider& m);
    //setter methods
    void set_d_first_name(const std::string& first_name);
    void set_d_last_name(const std::string& last_name);
    void set_d_phone_number(const std::string& phone_number);
    void set_state(const std::string& state);
    //getter methods
    std::string get_first_name();
    std::string get_last_name();
    std::string get_phone_number();
    std::string get_dropoff_location();
    std::string get_pickup_location();
    std::string get_lat();
    std::string get_long();
    std::string get_vehicle();
    std::string get_state();
private:
    std::string first_name, last_name, gender, age, phone_number, rating, dropoff_location, dropoff_lat, dropoff_long, pickup_location, pickup_lat, pickup_long,
            vehicle, state, d_first_name, d_last_name, d_phone_number;
};
#endif //HW4_RIDER_H
;