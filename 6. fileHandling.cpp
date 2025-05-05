#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Employee {
    int id;
    char name[30];
    char designation[30];
    float salary;

    void display() {
        cout << "ID: " << id << ", Name: " << name
             << ", Designation: " << designation
             << ", Salary: " << salary << endl;
    }
    
    
};

struct Index {
    int emp_id;
    long file_position;
    
    void display() const {   
        cout << "employeeId : " << emp_id << endl;
        cout << "FileLocaton: " << file_position << endl;
    }
};

void addEmployee() {
    Employee emp;
    ofstream empFile("employees.dat", ios::binary | ios::app);
    ofstream indexFile("index.dat", ios::binary | ios::app);

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(emp.name, 30);
    cout << "Enter Designation: ";
    cin.getline(emp.designation, 30);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    empFile.seekp(0, ios::end);
    long pos = empFile.tellp();
    empFile.write((char*)&emp, sizeof(Employee));

    Index idx;
    idx.emp_id = emp.id;
    idx.file_position = pos;
    indexFile.write((char*)&idx, sizeof(Index));

    empFile.close();
    indexFile.close();

    cout << "Employee added successfully!\n";
}

void searchEmployee() {
    int search_id;
    cout << "Enter Employee ID to search: ";
    cin >> search_id;

    ifstream indexFile("index.dat", ios::binary);
    ifstream empFile("employees.dat", ios::binary);

    Index idx;
    Employee emp;
    bool found = false;

    while (indexFile.read((char*)&idx, sizeof(Index))) {
        if (idx.emp_id == search_id) {
            empFile.seekg(idx.file_position);
            empFile.read((char*)&emp, sizeof(Employee));
            cout << "Employee Found:\n";
            emp.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!\n";
    }

    indexFile.close();
    empFile.close();
}

void displayAllEmployees() {
    ifstream empFile("employees.dat", ios::binary);
    if (!empFile) {
        cout << "Error opening employees.dat\n";
        return;
    }
    ifstream indexFile("index.dat", ios::binary);
    if (!indexFile) {
        cout << "Error opening index.dat\n";
        return;
    }

    Employee emp;
    cout << "Employee Records:\n";
    while (empFile.read((char*)&emp, sizeof(Employee))) {
        emp.display();
    }
    empFile.close();

    cout << "\nIndex File:\n";
    vector<Index> indexList;
    Index idx;

    while (indexFile.read((char*)&idx, sizeof(Index))) {
        indexList.push_back(idx);
    }


    sort(indexList.begin(), indexList.end(), [](const Index& a, const Index& b) {
        return a.emp_id < b.emp_id;  
    });


    for (const auto& i : indexList) {
        i.display();
    }

    indexFile.close();
}
 

void deleteEmployee() {
    int delete_id;
    cout << "Enter Employee ID to delete: ";
    cin >> delete_id;

    ifstream indexFile("index.dat", ios::binary);
    ifstream empFile("employees.dat", ios::binary);

    vector<Index> indexList;
    Index idx;
    bool found = false;
    while (indexFile.read((char*)&idx, sizeof(Index))) {
        if (idx.emp_id != delete_id) {
            indexList.push_back(idx);
        } else {
            found = true;
        }
    }

    if (!found) {
        cout << "Employee not found!\n";
        indexFile.close();
        empFile.close();
        return;
    }

    ofstream newEmpFile("temp.dat", ios::binary);
    Employee emp;

    while (empFile.read((char*)&emp, sizeof(Employee))) {
        if (emp.id != delete_id) {
            newEmpFile.write((char*)&emp, sizeof(Employee));
        }
    }

    empFile.close();
    newEmpFile.close();
    remove("employees.dat");
    rename("temp.dat", "employees.dat");

    ofstream newIndexFile("index.dat", ios::binary);
    for (const auto& i : indexList) {
        newIndexFile.write((char*)&i, sizeof(Index));
    }

    newIndexFile.close();
    indexFile.close();

    cout << "Employee deleted successfully!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Employee Management System ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Display All Employees\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                searchEmployee();
                break;
            case 3:
                displayAllEmployees();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
        }
    } while (choice != 5);

    return 0;
}
