#include <iostream>
#include <string>
#include <vector>
#include "FamilyTree.hpp"
using namespace std;

int main() {
    string peopleFile, relationshipsFile;
    cout << "Enter people file name: ";
    cin >> peopleFile;
    cout << "Enter relationships file name: ";
    cin >> relationshipsFile;

    FamilyTree tree;
    if (!tree.loadFromFile(peopleFile, relationshipsFile)) {
        cout << "Error: Failed to load files." << endl;
        return 1;
    }
    cout << "Family tree loaded successfully!" << endl;

    while (true) {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "1. Display a person's information" << endl;
        cout << "2. Find ancestors of a person" << endl;
        cout << "3. Find descendants of a person" << endl;
        cout << "4. Add a new person" << endl;
        cout << "5. Add a parent-child relationship" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string name;
            cout << "Enter person name: ";
            cin >> name;
            tree.displayPerson(name);
        }
        else if (choice == 2) {
            string name;
            int generations;
            cout << "Enter person name: ";
            cin >> name;
            cout << "Enter number of generations to search: ";
            cin >> generations;
            vector<string> ancestors = tree.findAncestors(name, generations);
            cout << "Ancestors of " << name << " (up to " << generations << " generations):" << endl;
            if (ancestors.empty()) {
                cout << "No known ancestors for " << name << "." << endl;
            } else {
                for (const string& anc : ancestors)
                    cout << anc << endl;
            }
        }
        else if (choice == 3) {
            string name;
            int generations;
            cout << "Enter person name: ";
            cin >> name;
            cout << "Enter number of generations to search: ";
            cin >> generations;
            vector<string> descendants = tree.findDescendants(name, generations);
            cout << "Descendants of " << name << " (up to " << generations << " generations):" << endl;
            if (descendants.empty()) {
                cout << "No known descendants for " << name << "." << endl;
            } else {
                for (const string& desc : descendants)
                    cout << desc << endl;
            }
        }
        else if (choice == 4) {
            string name;
            int birthYear;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter birth year: ";
            cin >> birthYear;
            if (!tree.personExists(name)) {
                tree.addPerson(name, birthYear);
            } else {
                cout << "Person " << name << " already exists." << endl;
            }
        }
        else if (choice == 5) {
            string parent, type, child;
            cout << "Enter parent name: ";
            cin >> parent;
            cout << "Is this parent a mother (m) or father (f)? ";
            cin >> type;
            cout << "Enter child name (or type '-' for no child): ";
            cin >> child;

            if (child == "-") {
                cout << "Failed to add relationship." << endl;
                continue;
            }
            bool isMother = (type == "m" || type == "M");
            bool parentExists = tree.personExists(parent);
            bool childExists = tree.personExists(child);
            bool success = false;

            if (parentExists && childExists) {
                success = tree.setParentChild(parent, child, isMother);
                if (success) {
                    cout << "Relationship added successfully." << endl;
                } else {
                    cout << "Failed to add relationship." << endl;
                }
            } else {
                if (!parentExists)
                    cout << "Person not found: " << parent << endl;
                if (!childExists)
                    cout << "Person not found: " << child << endl;
                cout << "Failed to add relationship." << endl;
            }
        }
        else if (choice == 6) {
            cout << "Goodbye!" << endl;
            break;
        }
        // Geçersiz seçimde menüyü tekrar göster.
    }

    return 0;
}
