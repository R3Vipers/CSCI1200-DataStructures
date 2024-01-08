#include <iostream>
#include <fstream>
#include <cmath>
#include "Node.h"
#include "User.h"

std::string replace(std::string s,
               char c1, char c2)
{
    int l = s.length();

    // loop to traverse in the string
    for (int i = 0; i < l; i++)
    {
        // check for c1 and replace
        if (s[i] == c1)
            s[i] = c2;

            // check for c2 and replace
        else if (s[i] == c2)
            s[i] = c1;
    }
    return s;
}

//simple output to file
void text_output (const std::string& text, const std::string& file_name){

    std::ofstream fout(file_name, std::ios::app);
    if (fout.is_open())
    {
        fout << text;
    }
}

//turns the sting of phone numbers into a list of stings with phone numbers
LinkedList<std::string> string_to_list(Node<User>* &node){
    LinkedList<std::string> phone;
    std::string number = "";
    //returns phone if the string reads null
    if(node->data.get_likes() == "null") {
        return phone;
    //returns just the string if the string contains one phone number
    } else if (node->data.get_likes().size() == 12) {
        phone.pushBack(node->data.get_likes());
        return phone;
    } else {
        //separates the strings
        int count = 0;
        for(long unsigned int i = 0; i < node->data.get_likes().size(); i++) {
            count++;
            number += node->data.get_likes()[i];
            if(number.size() == 12) {
                phone.pushBack(number);
                count = 0;
                number = "";
                i++;
            }
        }
    }
    return phone;
}

//uses the text display function to displays the appropriate text for profiles
template<class T>
void display(Node<T>* &node, const std::string &out_file){
    std::string out;
    out = replace(node->data.get_name(),'_', ' ') + " " + replace(std::to_string(node->data.get_age()), '_', ' ') + "\n";
    text_output(out, out_file);
    if(node->data.get_profession() != "Undisclosed"){
        out = replace(node->data.get_profession(), '_', ' ')+"\n";
        text_output(out, out_file);
    }
    if(node->data.get_school() != "Undisclosed"){
        out = replace(node->data.get_school(), '_', ' ')+"\n";
        text_output(out, out_file);
    }
    out = "\n";
    text_output(out, out_file);
}

//determines if a user has liked the current user
int evaluate_phone_numbers_likes (const std::string &desired_num, const std::string & output, Node<User>* &node) {
    LinkedList<std::string> phone = string_to_list(node);
    if(phone.exists(desired_num)){
        display(node, output);
        return 1;
    }
    return 0;
}
//determines if two users have liked each other
int evaluate_phone_numbers_match (const std::string &desired_num, const std::string & output, Node<User>* &node, Node<User>* &other_node) {

    LinkedList<std::string> phone1 = string_to_list(node);
    LinkedList<std::string> phone2 = string_to_list(other_node);
    if(phone1.exists(other_node->data.get_phone_number()) && phone2.exists(desired_num)){
        display(other_node, output);
        return 1;
    }
    return 0;
}
//takes in a list that has the deleted phone number and determines if the two are matched
int evaluate_phone_numbers_unmatched (const std::string &undesired_num, const std::string & output, Node<User>* &node, Node<User>* &other_node) {

    LinkedList<std::string> phone1 = string_to_list(node);
    LinkedList<std::string> phone2 = string_to_list(other_node);
    if(phone1.exists(other_node->data.get_phone_number()) && phone2.exists(node->data.get_phone_number()) &&
       undesired_num != other_node->data.get_phone_number()){
        display(other_node, output);
        return 1;
    }
    return 0;
}

//given function to calculate distance

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

int main(int argc, char* argv[]) {
    //assign all arguments to variables
    std::string user_input = argv[1];
    std::string output_file = argv[2];
    std::string desired_phone_number = argv[3];
    std::string output_type = argv[4];
    std::string other_phone_number;
    if(argc == 6){
        other_phone_number = argv[5];
    }

    std::string output_string;

    //linked list for user information
    LinkedList<User> user_list;

    std::ifstream in_user(user_input);
    //checks if input file can be opened.
    if (!in_user.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }



    //strings to input parameters
    std::string name, gender, age, phone_number, profession, school, current_lat, current_long,
            premium, min_age, max_age, max_dist, preference, likes;
    //while loop to iterate through the entire text document
    while (in_user >> name) {
        // each data point is read to its respective variable
        in_user >> age;
        in_user >> gender;
        in_user >> phone_number;
        in_user >> profession;
        in_user >> school;
        in_user >> current_lat;
        in_user >> current_long;
        in_user >> premium;
        in_user >> min_age;
        in_user >> max_age;
        in_user >> max_dist;
        in_user >> preference;
        in_user >> likes;
        User user (name, age, gender, phone_number, profession, school, current_lat, current_long,
                     premium, min_age, max_age, max_dist, preference, likes);
        user_list.pushBack(user);
    }

    in_user.close(); //close the ifstream file reader

    int count = 0;
    if(output_type == "like"){
        //create iterator nodes for comparing users
        Node<User>* current_user = user_list.get_head();
        Node<User>* check = user_list.get_head();
        //iterate until the desired user is found
        while (current_user != NULL){
            if(current_user->data.get_phone_number() == desired_phone_number) {
                if (current_user->data.get_premium() == "false") {
                    output_string = "Only premium users can view who liked you.\n\n";
                    text_output(output_string, output_file);
                    return 0;
                }
                break;
            }
            current_user = current_user->next;
        }
        //iterate until all liked users are found
        while(check != NULL){
            count += evaluate_phone_numbers_likes(desired_phone_number, output_file, check);
            check = check->next;
        }
        //if none are found out put desired text
        if(count == 0) {
            output_string = "You have not received any likes so far.\n\n";
            text_output(output_string, output_file);
        }
    } else if (output_type == "match") {
        //sort the list of users first so that when matches are outputted they will come out in order
        user_list.sort();
        //create iterator nodes for comparing users
        Node<User>* current = user_list.get_head();
        Node<User>* match = user_list.get_head();
        //iterate until the desired user is found
        while(match != NULL){
            if(match->data.get_phone_number() == desired_phone_number){
                break;
            }
            match = match->next;
        }
        //iterate until all matched users are found
        while(current != NULL){
            count += evaluate_phone_numbers_match(desired_phone_number, output_file, match, current);
            current = current->next;
        }
        //if none are found out put desired text
        if(count == 0) {
            output_string = "You do not have any matches at this moment.\n\n";
            text_output(output_string, output_file);
        }
    } else if (output_type == "profile") {
        //create iterator nodes for comparing users
        Node<User>* current = user_list.get_head();
        Node<User>* match = user_list.get_head();
        //iterate until the desired user is found
        while(match != NULL){
            if(match->data.get_phone_number() == desired_phone_number){
                break;
            }
            match = match->next;
        }
        //iterate until all profiles that meet user criteria are found
        while(current != NULL){
            double lat1 = match->data.get_lat();
            double long1 = match->data.get_long();
            double lat2 = current->data.get_lat();
            double long2 = current->data.get_long();
            double dist = calculateDistance(lat1, long1, lat2, long2);
            if(match->data.get_min_age() <= current->data.get_age() &&
               current->data.get_age() <= match->data.get_max_age() &&
               match->data.get_max_dist() >= dist && dist != 0)
            {
                //check for cases of both gender preference
                if(match->data.get_preferred_gender() == "Both") {
                    display(current, output_file);
                    count++;
                //else compare the preferred gender and the given gender
                } else if (match->data.get_preferred_gender() == current->data.get_gender()){
                    display(current, output_file);
                    count++;
                }

            }
            current = current->next;
        }
        //if none are found out put desired text
        if(count == 0) {
            output_string = "There are no users matching with your preference at this moment.\n\n";
            text_output(output_string, output_file);
        }
    } else if (output_type == "unmatch") {
        //sort the list of users first so that when matches are outputted they will come out in order
        user_list.sort();
        //create iterator nodes for comparing users
        Node<User>* current = user_list.get_head();
        Node<User>* other = user_list.get_head();
        Node<User>* match = user_list.get_head();
        //iterate until the desired user is found
        while(current != NULL){
            if(current->data.get_phone_number() == desired_phone_number){
                output_string = current->data.get_name()+"'s match list:\n\n";
                text_output(output_string, output_file);
                break;
            }
            current = current->next;
        }
        //iterate until all mathced users are found
        while(match != NULL){
            count += evaluate_phone_numbers_unmatched(other_phone_number, output_file, current, match);
            match = match->next;
        }
        //if none are found out put desired text
        if(count == 0) {
            output_string = "You do not have any matches at this moment.\n\n";
            text_output(output_string, output_file);
        }
        count = 0;
        match = user_list.get_head();
        output_string = "======\n";
        text_output(output_string, output_file);
        //iterate until the desired user is found
        while(other != NULL){
            if(other->data.get_phone_number() == other_phone_number){
                output_string = "\n" + other->data.get_name()+"'s match list:\n\n";
                text_output(output_string, output_file);
                break;
            }
            other = other->next;
        }
        //iterate until all matched users are found
        while(match != NULL){
            count += evaluate_phone_numbers_unmatched(desired_phone_number, output_file, other, match);
            match = match->next;
        }
        //if none are found out put desired text
        if(count == 0) {
            output_string = "You do not have any matches at this moment.\n\n";
            text_output(output_string, output_file);
        }
    }
    return 0;
}