//
// Created by Ryan Ames on 11/29/2023.
//
#include <iostream>
#include <regex>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;


#ifndef HW9_TRENDS_H
#define HW9_TRENDS_H
//class to hold information for each hashtag
class Hashtag {
public:
    //constructor
    Hashtag(const string& t, const long unsigned int &v) : tag(t), views(v), used(1) {}
    //getter and setter methods
    [[nodiscard]] long unsigned int getViews() const {return views;}
    [[nodiscard]] int getUsed() const {return used;}
    [[nodiscard]] string getTag() const {return tag;}
    void increaseViews(long unsigned int &v) {views += v;}
    void increaseUses() {used+=1;}
private:
    string tag;
    long unsigned int views;
    int used;
};
//class to hold information for each sound
class Sound {
public:
    //constructor
    Sound (const string& id, const long unsigned int &v, const string &t, const string &a) :
    ID(id), views(v), title(t), author(a), used(1) {}
    //getter and setter methods
    [[nodiscard]] long unsigned int getViews() const {return views;}
    [[nodiscard]] int getUsed() const {return used;}
    [[nodiscard]] string getTitle() const {return title;}
    [[nodiscard]] string getAuthor() const {return author;}
    [[nodiscard]] string getID() const {return ID;}
    void increaseViews(long unsigned int &v) {views += v;}
    void increaseUses() {used+=1;}
private:
    string ID;
    long unsigned int views;
    string title;
    string author;
    int used;
};

class Trend {
public:
    //constructor
    Trend(const string& id, long unsigned int v, const string& c, const string& w) :
    ID(id), views(v), cover(c), web(w) {}
    //getter and setter methods
    [[nodiscard]] long unsigned int getViews() const {return views;}
    [[nodiscard]] string getID() const {return ID;}
    [[nodiscard]] string getCover() const {return cover;}
    [[nodiscard]] string getWeb() const {return web;}
private:
    string ID;
    long unsigned int views;
    string cover;
    string web;
};

//comparator objects for priority queue
//hashtag comparator
class Comparehash {
public:
    bool operator()(const pair<string, Hashtag> &a, const pair<string, Hashtag> &b)
    {
        if (a.second.getUsed() != b.second.getUsed()) {
            return a.second.getUsed() < b.second.getUsed();
        } else if (a.second.getViews() != b.second.getViews()) {
            return a.second.getViews() < b.second.getViews();
        } else {
            return a.first > b.first;
        }
    }
};
//sound comparator
class Comparesound {
public:
    bool operator()(const pair<string, Sound> &a, const pair<string, Sound> &b)
    {
        if (a.second.getViews() != b.second.getViews()) {
            return a.second.getViews() < b.second.getViews();
        } else if (a.second.getUsed() != b.second.getUsed()) {
            return a.second.getUsed() > b.second.getUsed();
        } else {
            return a.first > b.first;
        }
    }
};
//url comparator
class CompareInfo {
public:
    bool operator()(const Trend &a, const Trend &b)
    {
        return a.getViews() < b.getViews();
    }
};

#endif //HW9_TRENDS_H
