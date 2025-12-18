#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

class Task {
private:
    string description;
    bool completed;

public:
    Task(string desc = "", bool done = false) {
        description = desc;
        completed = done;
    }

    void displayTask(int index) {
        cout << index << ". ";
        if (completed)
            cout << "[X] ";
        else
            cout << "[ ] ";
        cout << description << endl;
    }

    void markDone() {
        completed = true;
    }

    string toFileString() {
        return description + "|" + (completed ? "1" : "0");
    }

    static Task fromFileString(string line) {
        int pos = line.find('|');
        string desc = line.substr(0, pos);
        bool done = (line.substr(pos + 1) == "1");
        return Task(desc, done);
    }
};

int main10() {
    vector<Task> task;
    int choice;

    do {
        cout << "\n---- TO-DO MENU ----\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Save Tasks\n";
        cout << "5. Load Tasks\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string desc;
            cout << "Enter task description: ";
            getline(cin, desc);
            task.push_back(Task(desc));
            cout << "Task added.\n";
        }
        else if (choice == 2) {
            if (task.empty()) {
                cout << "No tasks available.\n";
            } else {
                for (int i = 0; i < task.size(); i++) {
                    task[i].displayTask(i + 1);
                }
            }
        }
        else if (choice == 3) {
            int num;
            cout << "Enter task number: ";
            cin >> num;

            if (num > 0 && num <= task.size()) {
                task[num - 1].markDone();
                cout << "Task marked completed.\n";
            } else {
                cout << "Invalid task number.\n";
            }
        }
        else if (choice == 4) {
            ofstream file("tasks.txt");
            for (int i = 0; i < task.size(); i++) {
                file << task[i].toFileString() << endl;
            }
            file.close();
            cout << "Tasks saved to file.\n";
        }
        else if (choice == 5) {
            task.clear();
            ifstream file("tasks.txt");
            string line;

            while (getline(file, line)) {
                task.push_back(Task::fromFileString(line));
            }

            file.close();
            cout << "Tasks loaded from file.\n";
        }
        else if (choice == 6) {
            cout << "Exiting program.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
