#include <iostream>
#include <fstream>
#include <list>
#include "Driver.h"
#include "Rider.h"
#include <cmath>

//calculate distance function - given in README.md
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}
//text output method for ofstream. takes the parameters of the text for output and the file to out put to
void text_output (const std::string& text, const std::string& file_name){

    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout << text;
    }
}
//out puts a truncated version of the double parameter
void truncate (const double& d, const std::string& file_name){
    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout.precision(2);
        fout << floor(d * 100) / 100;
    }
}
//uses two iterators to iterate through two lists, one wor the drivers, and one for the riders, then output to the
//specified files
void update_output(const std::list<Rider>& riders, const std::list<Driver>& drivers, const std::string& r_file_name, const std::string& d_file_name){
    std::_List_const_iterator<Rider> ride_itr = riders.begin();
    std::_List_const_iterator<Driver> drive_itr = drivers.begin();
    std::ofstream fout(r_file_name, std::ios::app);
    while(ride_itr != riders.end()){
        if (fout.is_open()) {
            fout << *ride_itr;
        }
        ++ride_itr;
    }
    std::ofstream fout2(d_file_name, std::ios::app);
    while(drive_itr != drivers.end()){
        if (fout.is_open())
        {
            fout2 << *drive_itr;
        }
        ++drive_itr;
    }
}
//method takes two list and a desired phone number to be found
void find_ride(std::list<Rider>& riders, std::list<Driver>& drivers, const std::string& phone_number, const std::string& output) {
    double distance = 0;
    std::string output_string = "";
    std::list<Driver>::iterator desired_driver;
    std::list<Rider>::iterator ride_itr = riders.begin();
    std::list<Driver>::iterator drive_itr = drivers.begin();
    //iterate through the list of riders until the driver with the matching phone number is found
    while(ride_itr != riders.end()) {
        if(phone_number == ride_itr -> get_phone_number()){
            //check if the rider is in a valid state
            if(ride_itr->get_state() == "Driver_on_the_way"){
                output_string = "You have already requested a ride and your driver is on the way to the pickup location.\n";
                text_output(output_string, output);
                return;
            }
            if(ride_itr->get_state() == "During_the_trip"){
                output_string = "You can not request a ride at this moment as you are already on a trip.\n";
                text_output(output_string, output);
                return;
            }
            //iterate through the list of drivers to find a drive that is available and match the request
            while(drive_itr != drivers.end()) {
                if(ride_itr -> get_vehicle() == drive_itr -> get_vehicle() && drive_itr->get_state() == "Available"){
                    double lat1 = std::stod(ride_itr -> get_lat());
                    double long1 = std::stod(ride_itr -> get_long());
                    double lat2 = std::stod(drive_itr -> get_lat());
                    double long2 = std::stod(drive_itr -> get_long());
                    double dist = calculateDistance(lat1, long1, lat2, long2);
                    if(distance == 0) {
                        distance = dist;
                    } else {
                        if(distance > dist){
                            distance = dist;
                            desired_driver = drive_itr;
                        }
                    }
                }
                drive_itr++;
            }
            //an vs. a text output
            if(ride_itr->get_vehicle() == "Standard" ||  ride_itr->get_vehicle() == "Luxury" || ride_itr->get_vehicle() == "Premium"){
                output_string = "Ride requested for user " + ride_itr->get_first_name() + ", looking for a " +
                                ride_itr->get_vehicle() + " vehicle.\n";
                text_output(output_string, output);
            } else {
                output_string = "Ride requested for user " + ride_itr->get_first_name() + ", looking for an " +
                                ride_itr->get_vehicle() + " vehicle.\n";
                text_output(output_string, output);
            }
            //if distance is zero then no driver was found.
            if(distance == 0){

                output_string = "Pick Up Location: " + ride_itr->get_pickup_location() + ", Drop Off Location: " +
                         ride_itr->get_dropoff_location()  + ".\n";
                text_output(output_string, output);
                output_string = "Sorry we can not find a driver for you at this moment.\n";
                text_output(output_string, output);
                return;
            //if a driver was found output the appropriate text and update the driver and rider classes
            } else {
                output_string = "Pick Up Location: " + ride_itr->get_pickup_location() + ", Drop Off Location: " +
                         ride_itr->get_dropoff_location() + ".\n";
                text_output(output_string, output);
                output_string ="We have found the closest driver " + desired_driver->get_first_name() + "(" +
                         desired_driver->get_rating() + ") for you.\n";
                text_output(output_string, output);
                output_string = desired_driver->get_first_name() + " is now ";
                text_output(output_string, output);
                truncate(distance, output);
                output_string = " miles away from you.\n";
                text_output(output_string, output);

                ride_itr->set_d_first_name(desired_driver->get_first_name());
                ride_itr->set_d_last_name(desired_driver->get_last_name());
                ride_itr->set_d_phone_number(desired_driver->get_phone_number());
                desired_driver->set_r_first_name(ride_itr->get_first_name());
                desired_driver->set_r_last_name(ride_itr->get_last_name());
                desired_driver->set_r_phone_number(ride_itr->get_phone_number());

                return;
            }
        }
        ride_itr++;
    }
    //if no account was found output appropriate text
    output_string = "Account does not exist.\n";
    text_output(output_string, output);
}

//returns a boolean that checks if the phone number input is correctly formatted
bool is_phone_number_valid(const std::string& number){
    if(number.size()==12){
        if(number[3] == '-' && number [7] == '-'){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    //assign all arguments to variables
    std::string rider_input = argv[2];
    std::string driver_input = argv[1];
    std::string output = argv[3];
    std::string rider_output = argv[5];
    std::string driver_output = argv[4];
    std::string desired_phone_number = argv[6];
    std::string request_type = argv[7];

    std::string output_string;
    //check if the desired phone number is valid.
    //if not output the appropriate text and terminate the program
    if(!is_phone_number_valid(desired_phone_number)){
        output_string = "Phone number is invalid.\n";
        text_output(output_string, output);
        return 0;
    }


    std::ifstream in_rider(rider_input);
    //checks if input file can be opened.
    if (!in_rider.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }

    std::list<Driver> drivers;
    std::list<Rider> riders;

    std::string first_name,last_name, gender, age, phone_number, rating, pickup_location, current_lat, current_long,
    dropoff_location, dropoff_lat,dropoff_long, vehicle, state, d_first_name, d_last_name, d_phone_number;
    //while loop to iterate through the entire text document
    while (in_rider >> first_name) {
        // each data point is read to its respective variable
        in_rider >> last_name;
        in_rider >> gender;
        in_rider >> age;
        in_rider >> phone_number;
        in_rider >> rating;
        in_rider >> pickup_location;
        in_rider >> current_lat;
        in_rider >> current_long;
        in_rider >> dropoff_location;
        in_rider >> dropoff_lat;
        in_rider >> dropoff_long;
        in_rider >> vehicle;
        in_rider >> state;
        in_rider >> d_first_name;
        in_rider >> d_last_name;
        in_rider >> d_phone_number;
        Rider rider (first_name, last_name, gender, age, phone_number, rating,
                     pickup_location, current_lat, current_long,
                     dropoff_location, dropoff_lat, dropoff_long, vehicle,
                     state, d_first_name, d_last_name, d_phone_number);
        riders.push_back(rider);
    }

    in_rider.close();

    std::ifstream in_driver(driver_input);
    //checks if input file can be opened.
    if (!in_driver.good()) {
        std::cerr << "Can't open " << argv[2] << " to read.\n";
        exit(1);
    }

    //while loop to iterate through the entire text document
    while (in_driver >> first_name) {
        // each data point is read to its respective variable
        in_driver >> last_name;
        in_driver >> gender;
        in_driver >> age;
        in_driver >> phone_number;
        in_driver >> rating;
        in_driver >> current_lat;
        in_driver >> current_long;
        in_driver >> vehicle;
        in_driver >> state;
        in_driver >> d_first_name;
        in_driver >> d_last_name;
        in_driver >> d_phone_number;
        Driver driver (first_name, last_name, gender, age, phone_number, rating,
                       current_lat, current_long, vehicle, state, d_first_name, d_last_name, d_phone_number);
        drivers.push_back(driver);
    }
    in_driver.close();

    //if there is a request, attempt to find a ride then out put the updated driver and rider files
    if(request_type == "request") {
        find_ride(riders, drivers, desired_phone_number, output);
        update_output(riders, drivers, rider_output,driver_output);
    } else if (request_type == "cancel") {
        std::list<Rider>::iterator ride_itr = riders.begin();
        std::list<Driver>::iterator drive_itr = drivers.begin();
        while(ride_itr != riders.end()){
            if(desired_phone_number == ride_itr -> get_phone_number()) {
                //make sure rider is in a valid state
                if(ride_itr->get_state() != "Driver_on_the_way"){
                    output_string = "You can only cancel a ride request if your driver is currently on the way to the pickup location.\n";
                    text_output(output_string, output);
                    return 0;
                }
                output_string = "Ride request for user " + ride_itr->get_first_name() + " is now canceled by the user.\n";
                text_output(output_string, output);
                //find rider and set state to ready to available and set rider parameters to null
                while(drive_itr != drivers.end()) {
                    if(desired_phone_number == drive_itr->get_r_phone_number()){
                        drive_itr->set_state("Available");
                        drive_itr->set_r_first_name("null");
                        drive_itr->set_r_last_name("null");
                        drive_itr->set_r_phone_number("null");
                    }
                    drive_itr++;
                }
                //delete rider
                riders.erase(ride_itr);
                update_output(riders, drivers, rider_output,driver_output);
                return 0;
            }
            ++ride_itr;
        }
        drive_itr = drivers.begin();
        ride_itr = riders.begin();
        while(drive_itr != drivers.end()){
            if(desired_phone_number == drive_itr -> get_phone_number()){
                //make sure driver is in a valid state
                if(drive_itr->get_state() != "On_the_way_to_pickup"){
                    output_string = "You can only cancel a ride request if you are currently on the way to the pickup location.\n";
                    text_output(output_string, output);
                    return 0;
                }
                output_string = "Your driver " + drive_itr->get_first_name() + " has cancelled the ride request. We will now find a new driver for you.\n";
                text_output(output_string, output);
                //find rider and set state to ready to request
                while(ride_itr != riders.end()) {
                    if(ride_itr->get_phone_number() == drive_itr->get_r_phone_number()){
                        ride_itr->set_state("Ready_to_request");
                    }
                    ride_itr++;
                }
                //attempt to find a new driver
                find_ride(riders, drivers, drive_itr->get_r_phone_number(), output);
                drive_itr->set_state("Available");
                drive_itr->set_r_first_name("null");
                drive_itr->set_r_last_name("null");
                drive_itr->set_r_phone_number("null");
                update_output(riders, drivers, rider_output,driver_output);
                return 0;
            }
            ++drive_itr;
        }
        //if no account is found output appropriate text
        output_string = "Account does not exist.\n";
        text_output(output_string, output);
    }
    return 0;
}
