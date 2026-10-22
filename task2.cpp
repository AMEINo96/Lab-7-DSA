#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;
    
    Student(int id, string n, float gpa) {
        studentID = id;
        name = n;
        GPA = gpa;
        left = nullptr;
        right = nullptr;
    }
};

class StudentBST {
private:
    Student* root;

    Student* findMin(Student* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Student* insert(Student* node, int id, string name, float gpa) {
        if (node == nullptr) {
            return new Student(id, name, gpa);
        }
        if (id < node->studentID) {
            node->left = insert(node->left, id, name, gpa);
        } else if (id > node->studentID) {
            node->right = insert(node->right, id, name, gpa);
        } else {
            cout << "Student with ID " << id << " already exists!\n";
        }
        return node;
    }


    Student* search(Student* node, int id) {
        if (node == nullptr || node->studentID == id) {
            return node;
        }
        if (id < node->studentID) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    Student* remove(Student* node, int id) {
        if (node == nullptr) return node;

        if (id < node->studentID) {
            node->left = remove(node->left, id);
        } else if (id > node->studentID) {
            node->right = remove(node->right, id);
        } else {
           
            if (node->left == nullptr) {
                Student* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Student* temp = node->left;
                delete node;
                return temp;
            }
            Student* temp = findMin(node->right);
            node->studentID = temp->studentID;
            node->name = temp->name;
            node->GPA = temp->GPA;
            node->right = remove(node->right, temp->studentID);
        }
        return node;
    }

    void inorder(Student* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << "ID: " << node->studentID << " | Name: " << setw(10) << left << node->name 
                 << " | GPA: " << fixed << setprecision(2) << node->GPA << "\n";
            inorder(node->right);
        }
    }


    int countStudents(Student* node) {
        if (node == nullptr) return 0;
        return 1 + countStudents(node->left) + countStudents(node->right);
    }

    void findHighestGPA(Student* node, Student*& highestNode) {
        if (node != nullptr) {
            if (highestNode == nullptr || node->GPA > highestNode->GPA) {
                highestNode = node;
            }
            findHighestGPA(node->left, highestNode);
            findHighestGPA(node->right, highestNode);
        }
    }

    void findLowestGPA(Student* node, Student*& lowestNode) {
        if (node != nullptr) {
            if (lowestNode == nullptr || node->GPA < lowestNode->GPA) {
                lowestNode = node;
            }
            findLowestGPA(node->left, lowestNode);
            findLowestGPA(node->right, lowestNode);
        }
    }

    void displayAboveThreshold(Student* node, float threshold) {
        if (node != nullptr) {
            displayAboveThreshold(node->left, threshold);
            if (node->GPA > threshold) {
                cout << "ID: " << node->studentID << " | Name: " << setw(10) << left << node->name 
                     << " | GPA: " << fixed << setprecision(2) << node->GPA << "\n";
            }
            displayAboveThreshold(node->right, threshold);
        }
    }

public:
    StudentBST() : root(nullptr) {}

    void insertRecord(int id, string name, float gpa) {
        root = insert(root, id, name, gpa);
    }

    void searchRecord(int id) {
        Student* result = search(root, id);
        if (result != nullptr) {
            cout << "Student Found! ID: " << result->studentID << " | Name: " << result->name << " | GPA: " << result->GPA << "\n";
        } else {
            cout << "Student with ID " << id << " not found.\n";
        }
    }

    void deleteRecord(int id) {
        root = remove(root, id);
        cout << "Record deletion attempted for ID " << id << ".\n";
    }

    void displayInorder() {
        cout << "\n--- Student Records (Sorted by ID) ---\n";
        inorder(root);
        cout << "--------------------------------------\n";
    }

    void printTotalStudents() {
        cout << "Total number of students: " << countStudents(root) << "\n";
    }

    void printHighestLowestGPA() {
        if (root == nullptr) {
            cout << "No students in the system.\n";
            return;
        }
        Student* highest = nullptr;
        Student* lowest = nullptr;
        
        findHighestGPA(root, highest);
        findLowestGPA(root, lowest);

        cout << "Highest GPA: " << highest->name << " (" << highest->GPA << ")\n";
        cout << "Lowest GPA:  " << lowest->name << " (" << lowest->GPA << ")\n";
    }

    void printAboveThreshold(float threshold) {
        cout << "\n--- Students with GPA above " << threshold << " ---\n";
        displayAboveThreshold(root, threshold);
        cout << "--------------------------------------\n";
    }
};

int main() {
    StudentBST system;

    system.insertRecord(105, "Alice", 3.8);
    system.insertRecord(102, "Bob", 2.9);
    system.insertRecord(108, "Charlie", 3.5);
    system.insertRecord(101, "Diana", 3.9);
    system.insertRecord(104, "Evan", 3.1);
    system.insertRecord(107, "Fiona", 2.5);
    system.insertRecord(109, "George", 4.0);

    system.displayInorder();

    cout << "\nSearching for ID 104:\n";
    system.searchRecord(104);
    
    cout << "\nSearching for ID 999:\n";
    system.searchRecord(999);

    cout << "\nDeleting student with ID 102 (Bob):\n";
    system.deleteRecord(102);
    system.displayInorder();

    cout << "\n--- Analytics ---\n";
    system.printTotalStudents();
    system.printHighestLowestGPA();
    system.printAboveThreshold(3.0);

    return 0;
}