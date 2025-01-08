/*8. Find the broadcast points of the class. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100; 
const int MAX_FRIENDS = 50;   

struct Student{
    string name;
    string friends[MAX_FRIENDS];
};

// Function to load student data from the file
int loadStudents(const string &filename, Student students[]){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Error: Could not open the file!" << endl;
        return 0;
    }

    string line;
    getline(file, line); // Skip the header 
    int total_students = 0;

    while (getline(file, line) && total_students < MAX_STUDENTS){
        stringstream ss(line);
        string token;
        int tokenCount = 0;

        while (getline(ss, token, ',')){
            if (tokenCount == 0) {
                students[total_students].name = token;  // First token is the student's name
            } else if (tokenCount - 1 < MAX_FRIENDS){
                students[total_students].friends[tokenCount - 1] = token;  // Friends list
            }
            tokenCount++;
        }
        total_students++;
    }
    file.close();
    return total_students;
}

// Function to check if all students can be reached from a starting student
bool canReachAll(Student students[], int total_students, const string &start){
    bool visited[MAX_STUDENTS] = {false};
    string stack[MAX_STUDENTS];
    int stackCount = 0;

    stack[stackCount++] = start;

    while (stackCount > 0){
        string current = stack[--stackCount];

        for (int i = 0; i < total_students; i++){
            if (students[i].name == current && !visited[i]){
                visited[i] = true;

                for (int j = 0; j < MAX_FRIENDS; j++){
                    if (!students[i].friends[j].empty()){
                        bool alreadyVisited = false;

                        for (int k = 0; k < total_students; k++){
                            if (students[k].name == students[i].friends[j] && visited[k]){
                                alreadyVisited = true;
                                break;
                            }
                        }

                        if (!alreadyVisited && stackCount < MAX_STUDENTS){
                            stack[stackCount++] = students[i].friends[j];
                        }
                    }
                }
                break;
            }
        }
    }

    // Check if all students are visited
    for (int i = 0; i < total_students; i++){
        if (!visited[i]) return false;
    }

    return true;
}

// Function to find broadcast points in the student network
void findBroadcastPoints(Student students[], int total_students){
    bool found = false;
    for (int i = 0; i < total_students; i++){
        if (canReachAll(students, total_students, students[i].name)){
            cout << students[i].name << " is a broadcast point.\n";
            found = true;
        }
    }
    if (!found){
        cout << "No broadcast points found.\n";
    }
}
int main(){
    Student students[MAX_STUDENTS];
    int total_students = 0;
    string filename = "Friends Dataset.csv";  
    total_students = loadStudents(filename, students);

    if (total_students > 0){
        findBroadcastPoints(students, total_students);
    } else{
        cout << "No data to process.\n";
    }
    return 0;
}
