//
// Created by Ryan Ames on 11/6/2023.
//
#include <iostream>
#include "Comment.h"
#include "Tree.h"
using namespace std;

#ifndef HW8_COMMAND_H
#define HW8_COMMAND_H
class Command {
public:
    //constructor
    Command(const string &c, const string &p_id, const string &ID, const string &u, const string &com) {
       command = c;
       parent_id = p_id;
       id = ID;
       user = u;
       comment = com;
    }
    //run each possible command that can be found
    void run (TreeNode* root, const string& out) {
        if(command == "reply_to_comment") {
            Comment newComment (user, id, 0, 0, true, parent_id, "0 seconds ago", 0, false, comment);
            root->insert(root, parent_id, newComment);
        } else if (command == "like_comment") {
            root->like(root, id);
        } else if (command == "delete_comment") {
            root->erase(root, id);
        } else if (command == "display_comment"){
            root->print(root,0, out);
        }
    }
private:
    string command;
    string parent_id;
    string id;
    string user;
    string comment;
};

#endif //HW8_COMMAND_H
