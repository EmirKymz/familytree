#ifndef FAMILYTREE_HPP
#define FAMILYTREE_HPP

#include "Person.hpp"
#include <string>
#include <vector>
using namespace std;

class FamilyTree {
private:
    vector<Person> people;
    int findPersonIndex(const string& name) const;

public:
    FamilyTree();

    bool loadFromFile(const string& peopleFile, const string& relationshipsFile);
    void addPerson(string name, int birthYear);
    bool setParentChild(string parentName, string childName, bool isMother);

    vector<string> findAncestors(const string& name, int generations) const;
    vector<string> findDescendants(const string& name, int generations) const;

    void displayPerson(const string& name) const;
    void displayAllPeople() const;

    bool personExists(const string& name) const;
};

#endif
