#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Function prototypes
void displayMenu();
void addTask(const string &filename);
void viewTasks(const string &filename);
void deleteTask(const string &filename);

int main() {
    const string filename = "todolist.txt";
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline left in buffer

        switch (choice) {
            case 1:
                addTask(filename);
                break;
            case 2:
                viewTasks(filename);
                break;
            case 3:
                deleteTask(filename);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    cout << "\nTo-Do List Menu" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View Tasks" << endl;
    cout << "3. Delete Task" << endl;
    cout << "4. Exit" << endl;
}

void addTask(const string &filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string task;
    cout << "Enter task description: ";
    getline(cin, task);
    file << task << endl;
    file.close();
    cout << "Task added successfully!" << endl;
}

void viewTasks(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    cout << "\nTasks:" << endl;
    int index = 1;
    while (getline(file, line)) {
        cout << index++ << ". " << line << endl;
    }
    file.close();
}

void deleteTask(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<string> tasks;
    string line;
    while (getline(file, line)) {
        tasks.push_back(line);
    }
    file.close();

    if (tasks.empty()) {
        cout << "No tasks to delete." << endl;
        return;
    }

    cout << "\nSelect task number to delete:" << endl;
    for (int i = 0; i < tasks.size(); ++i) {
        cout << (i + 1) << ". " << tasks[i] << endl;
    }

    int taskNumber;
    cout << "Enter task number: ";
    cin >> taskNumber;
    cin.ignore();  // Ignore newline left in buffer

    if (taskNumber < 1 || taskNumber > tasks.size()) {
        cout << "Invalid task number." << endl;
        return;
    }

    tasks.erase(tasks.begin() + taskNumber - 1);

    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    for (const auto &task : tasks) {
        outFile << task << endl;
    }
    outFile.close();
    cout << "Task deleted successfully!" << endl;
}