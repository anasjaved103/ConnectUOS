             // BY FARWAH TASLEEM`

#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 40; // This is the max number of students allowed
const int MAX_FRIENDS = 5;    // Each student can have up to 5 friends

struct Student {
    string name;
    int popularity = 0; // Count of how many students consider call this person a friend
};

int main() {
    // Path to the input file where all the data is stored
    string filename = "Friends Dataset.csv";
    ifstream file(filename);
    
    // If the file can't be opened, let the user know and stop the program
    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return 1;
    }
    
    Student students[MAX_STUDENTS]; // Array to store all student info (name and popularity)
    int student_count = 0;          // Keeps count of how many students are actually stored
    string line;

    // Skip the first line of the file since it contains column headers
    getline(file, line);

    // Go through each line in the file, one by one
    while (getline(file, line)) {
        stringstream ss(line);
        string student_name, friend_name;

        // Read the student name (first column)
        getline(ss, student_name, ',');

        // Read up to MAX_FRIENDS friends
        while (getline(ss, friend_name, ',')) {
            if (!friend_name.empty()) {
                // Check if friend_name already exists in our array
                bool found = false;
                for (int i = 0; i < student_count; i++) {
                    if (students[i].name == friend_name) {
                    	// If the friend is already in the array, just update their popularity count
                        students[i].popularity++;
                        found = true;
                        break;
                    }
                }
                // If friend_name is not found, add it to the array
                if (!found && student_count < MAX_STUDENTS) {
                    students[student_count].name = friend_name;
                    students[student_count].popularity = 1;	// They get 1 point for being called a friend
                    student_count++;
                }
            }
        }
    }
    //For testing purposes, output all the student names and their popularity counts
    // for (int i = 0; i < 40; i++){
    //    cout << students[i].name << " " << students[i].popularity << endl;
	// }
	
    // Close the file after we're done reading it
    file.close();

    // Determine which student has the highest popularity
    int max_popularity = 0;
    for (int i = 0; i < student_count; i++) {
        if (students[i].popularity > max_popularity) {
            max_popularity = students[i].popularity;
        }
    }

    // Output the most popular student(s)
    cout << "The most popular student(s) is/are:" << endl;
    for (int i = 0; i < student_count; i++) {
        if (students[i].popularity == max_popularity) {
            cout << students[i].name << " with " << students[i].popularity << " friends." << endl;
        }
    }

    return 0;
}