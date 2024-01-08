//
// Created by Ryan Ames on 11/7/2023.
//

#include <iostream>
using namespace std;

#ifndef HW8_COMMENT_H
#define HW8_COMMENT_H
class Comment {
public:
    //constructors
    Comment();
    Comment(const string& a, const string& c_id, int l_count, int r_count, bool reply, const string& p_id, const string &p_date_s, double p_date, bool v_owner, const string& c) {
        author = a;
        comment_id = c_id;
        like_count = l_count;
        reply_count = r_count;
        is_reply = reply;
        parent_id = p_id;
        publish_date_s = p_date_s;
        publish_date = p_date;
        video_owner = v_owner;
        comment = c;
    }
    //getter and setter methods
    double getDate() const {return publish_date;}
    string getAuthor() {return author;}
    string getCommentId() {return comment_id;}
    int getLikes() const {return like_count;}
    int getReplys() const {return reply_count;}
    string getComment() {return comment;}
    string getDate_s () {return publish_date_s;}
    string getParentId() {return parent_id;}
    void setDepth (int d) {depth = d;}
    int getDepth() const {return depth;}
    void addlike() {like_count+=1;}
private:
    //private variables
    string author;
    string comment_id;
    int like_count;
    int reply_count;
    bool is_reply;
    string parent_id;
    string publish_date_s;
    double publish_date;
    bool video_owner;
    string comment;
    int depth;
};
//print out each line with spacing that corresponds with depth
std::ostream& operator << (std::ostream& out, Comment &comment) {
    for (int i=0; i<comment.getDepth(); i++) out << "    ";
    out << comment.getAuthor() << " " << comment.getDate_s() << endl;
    for (int i=0; i<comment.getDepth(); i++) out << "    ";
    out << comment.getComment()<<endl;
    for (int i=0; i<comment.getDepth(); i++) out << "    ";
    out << "\U0001F44D " << comment.getLikes() <<std::endl;
    if (comment.getReplys() != 0) {
        for (int i=0; i<comment.getDepth(); i++) out << "    ";
        out << comment.getReplys() << " replies"<<endl;
    }
    return out;
}
//operator overloads
bool operator < (Comment& a, Comment& b){
    return a.getDate() < b.getDate();
}

bool operator > (Comment& a, Comment& b) {
    return a.getDate() > b.getDate();
}
#endif //HW8_COMMENT_H
