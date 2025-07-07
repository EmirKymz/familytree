#include "FamilyTree.hpp"
#include <fstream>
#include <iostream>

FamilyTree::FamilyTree() {
}

int FamilyTree::findPersonIndex(const string& name) const {
    for (size_t i = 0; i < people.size(); ++i) {
        if (people[i].getName() == name)
            return i;
    }
    return -1;
}

bool FamilyTree::loadFromFile(const string& peopleFile, const string& relationshipsFile) {
    ifstream pfile(peopleFile);
    ifstream rfile(relationshipsFile);

    if (!pfile.is_open() || !rfile.is_open()) {
        return false;
    }

    string name;
    int birthYear;
    while (pfile >> name >> birthYear) {
        addPerson(name, birthYear);
    }
    pfile.close();

    string father, mother, child;
    while (rfile >> father >> mother >> child) {
        if (child != "null") {
            setParentChild(mother, child, true);
            setParentChild(father, child, false);
        }
    }
    rfile.close();
    return true;
}

void FamilyTree::addPerson(string name, int birthYear) {
    if (findPersonIndex(name) == -1) {
        people.push_back(Person(name, birthYear));
    }
}

bool FamilyTree::setParentChild(string parentName, string childName, bool isMother) {
    int parentIdx = findPersonIndex(parentName);
    int childIdx = findPersonIndex(childName);
    if (parentIdx == -1 || childIdx == -1) {
        return false;
    }

    if (isMother) {
        people[childIdx].setMotherName(parentName);
    } else {
        people[childIdx].setFatherName(parentName);
    }
    people[parentIdx].addChildName(childName);
    return true;
}

void FamilyTree::displayPerson(const string& name) const {
    int idx = findPersonIndex(name);
    if (idx == -1) {
        cout << "Person not found: " << name << endl;
        return;
    }
    const Person& p = people[idx];
    cout << "Name: " << p.getName() << endl;
    cout << "Birth Year: " << p.getBirthYear() << endl;

    string mother = p.getMotherName();
    string father = p.getFatherName();

    cout << "Parents: ";
    if (mother == "" && father == "") {
        cout << "None" << endl;
    } else {
        bool first = true;
        if (father != "") {
            cout << father << " (father)";
            first = false;
        }
        if (mother != "") {
            if (!first) cout << ", ";
            cout << mother << " (mother)";
        }
        cout << endl;
    }

    const vector<string>& children = p.getChildrenNames();
    cout << "Children: ";
    if (children.empty()) {
        cout << "None" << endl;
    } else {
        for (size_t i = 0; i < children.size(); ++i) {
            cout << children[i];
            if (i < children.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

vector<string> FamilyTree::findAncestors(const string& name, int generations) const {
    vector<string> result;
    int idx = findPersonIndex(name);
    if (idx == -1 || generations <= 0) return result;

    const Person& p = people[idx];
    string mother = p.getMotherName();
    string father = p.getFatherName();

    if (mother != "") {
        result.push_back("Generation 1: " + mother);
    }
    if (father != "") {
        result.push_back("Generation 1: " + father);
    }

    if (generations > 1) {
        if (mother != "") {
            vector<string> m_anc = findAncestors(mother, generations - 1);
            for (const string& anc : m_anc) {
                int genNum = stoi(anc.substr(11, anc.find(':') - 11));
                string newAnc = "Generation " + to_string(genNum + 1) + anc.substr(anc.find(':'));
                result.push_back(newAnc);
            }
        }
        if (father != "") {
            vector<string> f_anc = findAncestors(father, generations - 1);
            for (const string& anc : f_anc) {
                int genNum = stoi(anc.substr(11, anc.find(':') - 11));
                string newAnc = "Generation " + to_string(genNum + 1) + anc.substr(anc.find(':'));
                result.push_back(newAnc);
            }
        }
    }
    return result;
}

vector<string> FamilyTree::findDescendants(const string& name, int generations) const {
    vector<string> result;
    int idx = findPersonIndex(name);
    if (idx == -1 || generations <= 0) return result;

    const Person& p = people[idx];
    const vector<string>& children = p.getChildrenNames();

    if (!children.empty()) {
        string genStr = "Generation 1: ";
        for (size_t i = 0; i < children.size(); ++i) {
            genStr += children[i];
            if (i < children.size() - 1) genStr += ", ";
        }
        result.push_back(genStr);

        if (generations > 1) {
            for (const string& child : children) {
                vector<string> childDesc = findDescendants(child, generations - 1);
                for (const string& desc : childDesc) {
                    int genNum = stoi(desc.substr(11, desc.find(':') - 11));
                    string newDesc = "Generation " + to_string(genNum + 1) + desc.substr(desc.find(':'));
                    result.push_back(newDesc);
                }
            }
        }
    }
    return result;
}

void FamilyTree::displayAllPeople() const {
    for (const Person& p : people) {
        cout << p.getName() << " (" << p.getBirthYear() << ")" << endl;
    }
}

bool FamilyTree::personExists(const string& name) const {
    return findPersonIndex(name) != -1;
}
