//
// Created by Ryan Ames on 11/1/2023.
//
#include <iostream>
#include <fstream>
#include <regex>
#include <list>

class Document {
public:
    //constructor for document
    Document(const std::string &u, const std::string &t, const std::string &d, const std::string &s, const std::list<std::string> &otherLinks, unsigned int key, unsigned int sz) {
        URL = u;
        title = t;
        description = d;
        snippet = s;
        outGoingLinks = otherLinks;
        keywordDensity = key;
        size = sz;
    }
    //getter and setter methods
    std::string get_URL() const {return URL;}
    std::string get_Title() const {return title;}
    std::string get_Description() const {return description;}
    std::string get_Snippet() const {return snippet;}
    unsigned int getSize() const {return size;}
    double getBackScore() const {return 1.0/(1.0+outGoingLinks.size());}
    std::list<std::string> get_outGoingLinks() const {return outGoingLinks;};
    unsigned int getDensity() const {return keywordDensity;}
    void setRank(double rank) {ranking = rank;}
    double getRank() const {return ranking;}
private:
    //Data analytics for a given document
    unsigned int keywordDensity;
    unsigned int size;
    double ranking;
    std::string URL;
    std::string title;
    std::string description;
    std::string snippet;
    std::list<std::string> outGoingLinks;
};

//operator overload
std::ostream& operator<<(std::ostream& out, const Document& d) {
    out<<"Title: "<<d.get_Title()<<std::endl;
    out<<"URL: "<<d.get_URL()<<std::endl;
    out<<"Description: "<<d.get_Description()<<std::endl;
    out<<"Snippet: "<<d.get_Snippet()<<std::endl;
    return out;
}

//> and < are reverse to give descending order when sorted by rank
bool operator>(const Document& a, const Document& b) {
    return a.getRank()< b.getRank();
};

bool operator<(const Document& a, const Document& b) {
    return a.getRank() > b.getRank();
};


#ifndef HW7_DOCUMENT_H
#define HW7_DOCUMENT_H

#endif //HW7_DOCUMENT_H
