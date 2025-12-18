#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

class Student {
private:
    string name;
    int id;
    float marks;

public:
    void setStudent() {
        cout << "Enter the name of the student: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        cout << "Enter their id number: ";
        cin >> id;

        cout << "Enter their marks: ";
        cin >> marks;
    }

    void displayStudent() {
        cout << "The student name is " << name << endl;
        cout << "The student ID is " << id << endl;
        cout << "The student marks are " << marks << endl;
    }

    int getId() {
        return id;
    }
};

int main10() {
    vector<Student> student;
    int choice;

    do {
        cout << "\n---- Student Menu ----\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            Student students;
            students.setStudent();
            student.push_back(students);
            cout << "Student was added successfully.\n";
        }
        else if (choice == 2) {
            if (student.empty()) {
                cout << "No students are available\n";
            } else {
                for (int i = 0; i < student.size(); i++) {
                    student[i].displayStudent();
                    cout << endl;
                }
            }
        }
        else if (choice == 3) {
            int num;
            cout << "Enter id to search: ";
            cin >> num;

            bool found = false;
            for (int i = 0; i < student.size(); i++) {
                if (student[i].getId() == num) {
                    student[i].displayStudent();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Student not found\n";
            }
        }
        else if (choice == 4) {
            cout << "The program is closing\n";
        }
        else {
            cout << "Please select a correct option between 1-4\n";
        }

    } while (choice != 4);

    return 0;
}
