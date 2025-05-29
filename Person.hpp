#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
using namespace std;

class Person {
private:
    string name;
    int birthYear;
    string motherName;
    string fatherName;
    vector<string> childrenNames;

public:
    Person(string n, int by);

    string getName() const;
    int getBirthYear() const;
    string getMotherName() const;
    string getFatherName() const;
    vector<string> getChildrenNames() const;

    void setMotherName(const string& mName);
    void setFatherName(const string& fName);
    void addChildName(const string& childName);
};

#endif
