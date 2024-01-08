#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Command.h"
#include "Comment.h"
#include "Tree.h"

using namespace std;
//get data from string
string extract_data_string (const string& line, const string& type){
    unsigned int start = line.find(type)+type.size();
    unsigned int end = line.find('"', start);
    return line.substr(start,end-start);
}
//convert string to bool
bool extract_data_bool (const string& line, const string& type){
    unsigned int start = line.find(type)+type.size()+1;
    unsigned int end = line.find(',', start);
    if (line.substr(start,start-end) == "true"){
        return true;
    } else {
        return false;
    }
}
//convert string to int
int extract_data_int (const string& line, const string& type){
    unsigned int start = line.find(type)+type.size();
    unsigned int end = line.find(',', start);
    return stoi(line.substr(start,end-start));
}
//convert all dates to seconds to order them by comment date
double extract_data_date (const string& line){
    unsigned int start = line.find(' ')+1;
    unsigned int end = line.find(' ', start+1);
    string time_type = line.substr(start,end-start);
    double modifier = stoi(line.substr(0,start));
    if(time_type == "year" || time_type =="years"){
        return modifier*3.154e7;
    } else if (time_type == "months" || time_type == "month") {
        return modifier*2.628e6;
    } else if (time_type == "days" || time_type == "day") {
        return modifier*86410.958906879997812;
    } else if (time_type == "hours" || time_type == "hour") {
        return modifier*3600;
    }else if (time_type == "minutes" || time_type == "minute") {
        return modifier*60;
    }else if (time_type == "weeks" || time_type == "week") {
        return modifier*604876.71234816;
    }else {
        return modifier;
    }
}

int main(int argc, char* argv[]) {
    string input1 = argv[1];
    string input2 = argv[2];
    string output = argv[3];

    ifstream  opsFile(input2);
    if (!opsFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        exit(1);
    }
    vector<Command> commands;
    string input_command;
    string parent_id;
    string id;
    string user;
    string comment;
    set<string> ids;
    // assuming opsFile is an std::ifstream object, which you use to open the second input file.
    // assuming command, parent_id, id, author, comment are all std::string objects.
    // read the command, the parent comment id, the child comment id, the user name.
    while(opsFile >> input_command){
        opsFile >> parent_id;
        if(input_command == "delete_comment" || input_command =="display_comment" || input_command =="like_comment") {
            Command other_command (input_command, parent_id, "", "", "");
            ids.insert(parent_id);
            commands.push_back(other_command);
            //cout<<other_command;
            continue;
        }
        opsFile >> id;
        opsFile >> user;
        // skip any whitespace to get to the next non-whitespace character
        opsFile >> std::ws;
        // now, read the comment
        if (opsFile.peek() == '"') {
            // if the field starts with a double quote, read it as a whole string
            opsFile.get();  // consume the opening double quote
            std::getline(opsFile, comment, '"');  // read until the closing double quote
            // opsFile >> comment;  // read the quoted field
            if (!comment.empty() && comment.back() == '"') {
                comment.pop_back();  // remove the closing double quote
            }
        }
        Command command (input_command, parent_id, id, user, comment);
        commands.push_back(command);
        ids.insert(parent_id);
        ids.insert(id);
        //cout<<command;
    }
    //cout<<commands.size();
    std::ifstream jsonFile(input1);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }

    vector<Comment> parent_comments;
    vector<Comment> comments;
    std::string line;
    string comment_id;
    string comment_id_p;
    string author;
    int like_count;
    int reply_count;
    bool is_reply;
    string publish_date_s;
    double publish_date;
    bool video_owner;
    string c;
    //get each piece of data from a line
    while (std::getline(jsonFile, line)) {
        comment_id = extract_data_string(line, "\"comment_id\": \"");
        comment_id_p = extract_data_string(line, "\"parent_comment_id\": \"");
        author = extract_data_string(line, "\"author\": \"");
        like_count = extract_data_int(line, "\"like_count\": ");
        reply_count = extract_data_int(line, "\"reply_count\": ");
        is_reply = extract_data_bool(line, "\"is_reply\": ");
        publish_date_s = extract_data_string(line, "\"published_date\": \"");
        publish_date = extract_data_date(extract_data_string(line, "\"published_date\": \""));
        video_owner = extract_data_bool(line, "\"is_video_owner\": ");
        c = extract_data_string(line, "\"comment\": \"");
        Comment comment(
        author,
        comment_id,
        like_count,
        reply_count,
        is_reply,
        comment_id_p,
        publish_date_s,
        publish_date,
        video_owner,
        c);
        //find root comments
        if(ids.find(comment_id) != ids.end()){
            ids.insert(comment_id);
            parent_comments.push_back(comment);
        //find other comments
        } else if(ids.find(comment_id_p) != ids.end()) {
            ids.insert(comment_id);
            ids.insert(comment_id_p);
            //cout<<comment;
            comments.push_back(comment);
        }

    }
    // don't need this json file anymore, as the content is read into json_content.
    jsonFile.close();
    //create a vector of tree roots to print
    vector<TreeNode*> roots;
    for(const Comment& parent: parent_comments) {
        TreeNode* root = new TreeNode(parent);
        roots.push_back(root);
    }
    //insert other comment into the tree
    for (TreeNode* root : roots) {
        for(Comment c: comments){
            root->insert(root, c.getParentId(),c);
        }
    }
    //apply commands to comments
    for (TreeNode* root : roots)
        for(Command command: commands)
            command.run(root, output);
    return 0;
}
