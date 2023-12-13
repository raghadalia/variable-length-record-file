#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include "vector"
#pragma warning(disable : 4996) // Disable warning for strcpy

using namespace std;


struct Emp {
    int empno;
    char empname[20];
    float salary;
};

struct Student {
    int stno;
    char stname[30];
    float mark;
    int age;
};


template <typename T>
void insertRecord(const char* fileName, const T& record) {
    ofstream outFile(fileName, ios::app);

    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }

    if constexpr (is_same_v<T, Emp>) {
        outFile << "E " << (record.empno != -1 ? to_string(record.empno) : "null")
            << " " << (strlen(record.empname) > 0 ? record.empname : "null")
            << " " << (record.salary != -1.0 ? to_string(record.salary) : "null") << ' #' << endl;
    }
    else if constexpr (is_same_v<T, Student>) {
        outFile << "S " << (record.stno != -1 ? to_string(record.stno) : "null")
            << " " << (strlen(record.stname) > 0 ? record.stname : "null")
            << " " << (record.mark != -1.0 ? to_string(record.mark) : "null")
            << " " << (record.age != -1 ? to_string(record.age) : "null") << ' #' << endl;
    }

    outFile.close();
}


void searchEmployeeByNumber(const char* fileName, int empNumber) {
    ifstream inFile(fileName, ios::binary);
    int flage = 0;

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    string recordType;

    while (getline(inFile, line)) {
        stringstream l(line);
        l >> recordType;

        if (recordType == "E") {
            Emp empRecord;
            l >> empRecord.empno;

            if (empRecord.empno == empNumber) {
                flage = 1;
                cout << line << endl;  
                break;  
            }
        }
    }

    inFile.close();

    if (!flage) {
        cout << "Employee with number " << empNumber << " not found." << endl;
    }
}

void searchStudentByNumber(const char* fileName, int stNumber) {
    ifstream inFile(fileName, ios::binary);
    int flage = 0;
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    char recordType;

    while (getline(inFile, line)) {
        stringstream l(line);
        l >> recordType;

        if (recordType == 'S') {
            Student stRecord;
            l >> stRecord.stno;

            if (stRecord.stno == stNumber) {
                flage = 1;
                cout << line << endl;  
                break; 
            }
        }
    }

    inFile.close();
    if(flage==0)
    cout << "Student with number " << stNumber << " not found." << endl;
}

void readAndPrintFile(const char* fileName) {
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    char recordType;

    while (getline(inFile, line)) {
        stringstream l(line);
        l >> recordType;
         cout << line << endl;          
    }
    inFile.close();
}

void deleteStudentByNumber(const char* fileName, int stNumber) {
    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    vector<string> lines;  
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();
    ofstream outFile(fileName, ios::trunc);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    bool deleted = false;
    for (const string& record : lines) {
        stringstream ss(record);
        char recordType;
        ss >> recordType;

        if (recordType == 'S') {
            Student stRecord;
            ss >> stRecord.stno;
            if (stRecord.stno == stNumber) {
                deleted = true;
                continue;  
            }
        }
        else
            cout << "the student number not found\n";

        outFile << record << endl;  
    }

    outFile.close();

    if (deleted) {
        cout << "Student with number " << stNumber << " deleted successfully." << endl;
    }
    else {
        cout << "Student with number " << stNumber << " not found." << endl;
    }
}

void deleteEmployeeByNumber(const char* fileName, int empNumber) {
    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    vector<string> lines;  
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    // Open the file again for writing
    ofstream outFile(fileName, ios::trunc);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    bool deleted = false;
    for (const string& record : lines) {
        stringstream ss(record);
        char recordType;
        ss >> recordType;

        if (recordType == 'E') {
            Emp empRecord;
            ss >> empRecord.empno;
            if (empRecord.empno == empNumber) {
                deleted = true;
                continue;  // Skip writing this line (deleting the record)
            }
        }
        else
            cout << "the Employee number not found\n";

        outFile << record << endl;  
    }

    outFile.close();

    if (deleted) {
        cout << "Employee with number " << empNumber << " deleted successfully." << endl;
    }
    else {
        cout << "Employee with number " << empNumber << " not found." << endl;
    }
}

void displayStudentByNumber(const char* fileName, int stNumber) {
    ifstream inFile(fileName, ios::binary);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    char recordType;

    while (getline(inFile, line)) {
        stringstream ss(line);
        ss >> recordType;

        if (recordType == 'S') {
            Student stRecord;
            ss >> stRecord.stno;
            if (stRecord.stno == stNumber) {
                cout << "Student Record: " << line << endl;  
                inFile.close();
                return;  // Once found, no need to continue searching
            }
        }
        else {
            cerr << "Unknown record type: " << recordType << endl;
            break;
        }
    }

    inFile.close();
    cout << "Student with number " << stNumber << " not found." << endl;
}

void updateStudentByNumber(const char* fileName, int stNumber) {
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    vector<string> lines;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    ofstream outFile(fileName);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    bool updated = false;
    for (const string& record : lines) {
        stringstream ss(record);
        char recordType;
        ss >> recordType;

        if (recordType == 'S') {
            Student stRecord;
            ss >> stRecord.stno >> stRecord.stname >> stRecord.mark >> stRecord.age;

            if (stRecord.stno == stNumber) {
                
                int choice;
                cout << "Choose an attribute to update:\n";
                cout << "1. Student Name\n";
                cout << "2. Mark\n";
                cout << "3. Age\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter updated student name: ";
                    cin.ignore();
                    cin.getline(stRecord.stname, sizeof(stRecord.stname));
                    break;
                case 2:
                    cout << "Enter updated mark: ";
                    cin >> stRecord.mark;
                    break;
                case 3:
                    cout << "Enter updated age: ";
                    cin >> stRecord.age;
                    break;
                default:
                    cout << "Invalid choice. No updates will be made.\n";
                    break;
                }

                updated = true;
            }

            
            outFile << fixed << setprecision(6);  
            outFile << "S " << stRecord.stno << " " << stRecord.stname << " " << stRecord.mark << " " << stRecord.age << " #" << endl;
        }
        else {
            // Write non-student records directly
            outFile << record << endl;
        }
    }

    outFile.close();

    if (updated) {
        cout << "Student with number " << stNumber << " updated successfully." << endl;
    }
    else {
        cout << "Student with number " << stNumber << " not found." << endl;
    }
}

void updateEmployeeByNumber(const char* fileName, int empNumber) {
    ifstream inFile(fileName);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    vector<string> lines;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    ofstream outFile(fileName);

    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    bool updated = false;
    for (const string& record : lines) {
        stringstream ss(record);
        char recordType;
        ss >> recordType;

        if (recordType == 'E') {
            Emp empRecord;
            ss >> empRecord.empno >> empRecord.empname >> empRecord.salary;

            if (empRecord.empno == empNumber) {
                int choice;
                cout << "Choose an attribute to update:\n";
                cout << "1. Employee Name\n";
                cout << "2. Salary\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    cout << "Enter updated Employee name: ";
                    cin.ignore();
                    cin.getline(empRecord.empname, sizeof(empRecord.empname));
                    break;
                case 2:
                    cout << "Enter updated salary: ";
                    cin >> empRecord.salary;
                    break;
                default:
                    cout << "Invalid choice. No updates will be made.\n";
                    break;
                }

                updated = true;
            }

            outFile << fixed << setprecision(6);  // Set precision for floating-point numbers
            outFile << "E " << empRecord.empno << " " << empRecord.empname << " " << empRecord.salary << " #" << endl;
        }
        else {
            // Write non-Emp records directly
            outFile << record << endl;
        }
    }

    outFile.close();

    if (updated) {
        cout << "Employee with number " << empNumber << " updated successfully." << endl;
    }
    else {
        cout << "Employee with number " << empNumber << " not found." << endl;
    }
}


int main() {
    char choice;
    do {
        cout << "Menu:\n";
        cout << "1- Insert Employee/Student Record\n";
        cout << "2- Delete Student Record by Number\n";
        cout << "3- Delete Employee Record by Number\n";
        cout << "4- Update Student Record\n";
        cout << "5- Update Employee Record\n";
        cout << "6- Display All Records\n";
        cout << "7- Search for a Student by Number\n";
        cout << "8- Search for an Employee by Number\n";
        cout << "9- Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case '1':
            char recordType;
            char choice;
            do {
                cout << "Enter record type (E for Employee, S for Student): ";
                cin >> recordType;
                if ((recordType != 'E' && recordType != 'e') && (recordType != 'S' && recordType != 's')) {
                    cerr << "Invalid record type. Exiting...\n";
                    return 1;
                }

                if (recordType == 'E' || recordType == 'e') {
                    Emp empRecord;
                    cout << "Enter Employee number (enter -1 for null): ";
                    cin >> empRecord.empno;

                    cout << "Enter Employee name (enter N for null): ";
                    cin.ignore();
                    cin.getline(empRecord.empname, sizeof(empRecord.empname));

                    cout << "Enter Employee salary (enter -1 for null): ";
                    cin >> empRecord.salary;

                    insertRecord("records.txt", empRecord);
                }
                else if (recordType == 'S' || recordType == 's') {
                    Student stRecord;
                    cout << "Enter student number (enter -1 for null): ";
                    cin >> stRecord.stno;

                    cout << "Enter student name (enter N for null): ";
                    cin.ignore();
                    cin.getline(stRecord.stname, sizeof(stRecord.stname));

                    cout << "Enter student mark (enter -1 for null): ";
                    cin >> stRecord.mark;

                    cout << "Enter student age (enter -1 for null): ";
                    cin >> stRecord.age;

                    insertRecord("records.txt", stRecord);
                }
                cout << "Do you want to add another record? (Y/N): ";
                cin >> choice;

            } while (choice == 'Y' || choice == 'y');
            break;
        case '2':
        
            int deleteStNumber;
            cout << "Enter student number to delete: ";
            cin >> deleteStNumber;
            deleteStudentByNumber("records.txt", deleteStNumber);
            break;

        case '3':
            int empNumberToDelete;
            cout << "Enter Emp number to delete: ";
            cin >> empNumberToDelete;
            deleteEmployeeByNumber("records.txt", empNumberToDelete);
            break;
        case '4':
            int stNumber;
            char updatedName[30];
            cout << "Enter student number to update name: ";
            cin >> stNumber;
            updateStudentByNumber("records.txt", stNumber);
            break;
        case '5':
           
            int empNumber;

            cout << "Enter Employee number to update: ";
            cin >> empNumber;

            updateEmployeeByNumber("records.txt", empNumber);

            break;
        case '6':
           
            readAndPrintFile("records.txt");
           
            break;
        case '7':
            int searchStNumber;
            cout << "Enter student number to search: ";
            cin >> searchStNumber;
            searchStudentByNumber("records.txt", searchStNumber);

            break;
        case '8':
          
            int searchEmpNumber;
            cout << "Enter Employee number to search: ";
            cin >> searchEmpNumber;
            searchEmployeeByNumber("records.txt", searchEmpNumber);

            break;
        case '9':
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (choice != '9');

    return 0;
}
