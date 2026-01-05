#include <iostream>
#include <fstream>
using namespace std;

class Student {
private:
    int roll;
    char name[50];
    char course[50];

public:
    void input() {
        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Course: ";
        cin.getline(course, 50);
    }

    void display() {
        cout << "\nRoll Number: " << roll;
        cout << "\nName: " << name;
        cout << "\nCourse: " << course << endl;
    }

    int getRoll() {
        return roll;
    }
};

void addStudent() {
    Student s;
    ofstream out("students.dat", ios::binary | ios::app);

    s.input();
    out.write((char*)&s, sizeof(s));

    out.close();
    cout << "\nStudent Added Successfully!\n";
}

void displayAll() {
    Student s;
    ifstream in("students.dat", ios::binary);

    cout << "\n--- Student List ---\n";
    while (in.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "---------------------";
    }

    in.close();
}

void searchStudent() {
    Student s;
    int r, found = 0;

    cout << "Enter Roll Number to Search: ";
    cin >> r;

    ifstream in("students.dat", ios::binary);

    while (in.read((char*)&s, sizeof(s))) {
        if (s.getRoll() == r) {
            s.display();
            found = 1;
            break;
        }
    }

    in.close();

    if (!found)
        cout << "\nStudent Not Found!\n";
}

void deleteStudent() {
    Student s;
    int r;

    cout << "Enter Roll Number to Delete: ";
    cin >> r;

    ifstream in("students.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    int found = 0;

    while (in.read((char*)&s, sizeof(s))) {
        if (s.getRoll() != r)
            out.write((char*)&s, sizeof(s));
        else
            found = 1;
    }

    in.close();
    out.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nStudent Deleted Successfully!\n";
    else
        cout << "\nStudent Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayAll(); break;
        case 3: searchStudent(); break;
        case 4: deleteStudent(); break;
        case 5: cout << "\nExiting...\n"; break;
        default: cout << "\nInvalid Choice!\n";
        }
    } while (choice != 5);
    return 0;
}
