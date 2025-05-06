#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int roll;
    char name[20];
    float marks;
};

const char* FILENAME = "students.dat";

void addRecord() {
    ofstream out(FILENAME, ios::binary | ios::app);
    Student s;
    cout << "Enter Roll No, Name, Marks: ";
    cin >> s.roll >> ws;
    cin.getline(s.name, 20);
    cin >> s.marks;
    out.write((char*)&s, sizeof(s));
    out.close();
}

void displayAll() {
    ifstream in(FILENAME, ios::binary);
    Student s;
    cout << "\nAll Student Records:\n";
    while (in.read((char*)&s, sizeof(s))) {
        cout << "Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << endl;
    }
    in.close();
}

void searchRecord(int rollNo) {
    ifstream in(FILENAME, ios::binary);
    Student s;
    bool found = false;

    while (in.read((char*)&s, sizeof(s))) {
        if (s.roll == rollNo) {
            cout << "Found: Roll: " << s.roll << ", Name: " << s.name << ", Marks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    in.close();
}

void modifyRecord(int rollNo) {
    fstream file(FILENAME, ios::binary | ios::in | ios::out);
    Student s;
    bool found = false;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll == rollNo) {
            cout << "Existing: " << s.name << " " << s.marks << endl;
            cout << "Enter new name and marks: ";
            cin.ignore();
            cin.getline(s.name, 20);
            cin >> s.marks;

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));
            file.write((char*)&s, sizeof(s));
            found = true;
            cout << "Record updated.\n";
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";

    file.close();
}

int main() {
    int choice, roll;
    while (true) {
        cout << "\n1. Add\n2. Display\n3. Search\n4. Modify\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayAll(); break;
            case 3:
                cout << "Enter Roll No to search: ";
                cin >> roll;
                searchRecord(roll); break;
            case 4:
                cout << "Enter Roll No to modify: ";
                cin >> roll;
                modifyRecord(roll); break;
            case 5: return 0;
            default: cout << "Invalid.\n";
        }
    }
}
