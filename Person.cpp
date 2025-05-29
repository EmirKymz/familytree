#include "Person.hpp"

Person::Person(string n, int by)
    : name(n), birthYear(by), motherName(""), fatherName("") {
    // Başlangıçta anne-baba adı boş, çocuklar boş vektör.
}

string Person::getName() const {
    return name;
}

int Person::getBirthYear() const {
    return birthYear;
}

string Person::getMotherName() const {
    return motherName;
}

string Person::getFatherName() const {
    return fatherName;
}

vector<string> Person::getChildrenNames() const {
    return childrenNames;
}

void Person::setMotherName(const string& mName) {
    motherName = mName;
}

void Person::setFatherName(const string& fName) {
    fatherName = fName;
}

void Person::addChildName(const string& childName) {
    // Aynı çocuk iki kez eklenmesin diye kontrol edebilirsin (isteğe bağlı).
    for (const string& child : childrenNames) {
        if (child == childName) return;
    }
    childrenNames.push_back(childName);
}
