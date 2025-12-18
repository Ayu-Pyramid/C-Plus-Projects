#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
private:
    string name;
    int id;
    float marks;


public:
   void  setStudent() {
        cout << "Enter the name of the student: ";
       cin.ignore();
       getline(cin,name);

        cout << "Enter their id number: ";
        cin >> id;

        cout << "Enter theri marks: ";
        cin >> marks;


    }
   void  displayStudent() {
        cout << "The student name is " << name <<endl;
        cout << "The student ID is " << id <<endl;
        cout << "The student marks are " << marks <<endl;

    }
   void getId() {
        int num;
        cout << "Enter the ID number of the student: ";
        cin >> num;

        if (num == id) {
            cout << "The student name is " << name << endl;
            cout << "The student marks are " << marks;

        } else {
            cout << "Wrong ID number ";
        }
    }


};



int main9() {

Student student;
    int choice;

    do {
        cout << "\n---- Student Menu ----\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1: student.setStudent();
                break;
            case 2: student.displayStudent();
                break;
            case 3: student.getId();
                break;
            case 4: cout << "Closing the program ";
                break;
            default: cout << "Enter the choice between 1-5";

        }
    } while (choice != 5);


    return 0;
}

