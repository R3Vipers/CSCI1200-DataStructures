// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
using namespace std::chrono;
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}
//map implementation
void identify(const map<int, string> phonebook, int number) {
    if (phonebook.find(number) == phonebook.end())
        cout << "unknown caller!" << endl;
    else
        cout << phonebook.find(number)->second << " is calling!" << endl;
}


int main() {
  // create the phonebook; initially all numbers are unassigned
  auto start = high_resolution_clock::now();

  vector<string> phonebook(10000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  identify(phonebook, 2222);
  identify(phonebook, 4444);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout<<duration.count()<<endl;
// map implementation
  start = high_resolution_clock::now();
  map<int , string> phonebook_m;

  phonebook_m.insert(std::make_pair(1111, "fred"));
  phonebook_m.insert(std::make_pair(2222, "sally"));
  phonebook_m.insert(std::make_pair(3333, "george"));

  // test the phonebook
  identify(phonebook_m, 2222);
  identify(phonebook_m, 4444);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout<<duration.count()<<endl;
}
