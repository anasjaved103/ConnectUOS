//Module 3: Given a student A, find the students that are 1-hop, 2-hop, and 3-hop away from a given student.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

 const int MAX_STUDENTS = 40;
 const int MAX_FRIENDS = 5;   
 const int MAX_HOPS = 40;     

struct Student {
    string name;
    string friends[MAX_FRIENDS];
};


void split(string &line, char delimiter, string tokens[], int &token_count) {
    stringstream ss(line);
    string token;
    token_count = 0;
    while (getline(ss, token, delimiter)) {
        tokens[token_count++] = token;
    }
}


int findStudentIndex(string &student_name, Student students[], int total_students) {
    for (int i = 0; i < total_students; i++) {
        if (students[i].name == student_name) {
            return i;
        }
    }
    return -1;
}

bool existsInArray(string &value, string arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

void findHops(string &student_name, Student students[], int total_students) {
    int studentIndex = findStudentIndex(student_name, students, total_students);
    if (studentIndex == -1) {
        cout << "Student not found in the dataset.\n";
        return;
    }

    
    string hop1[MAX_HOPS], hop2[MAX_HOPS], hop3[MAX_HOPS];
    int hop1_count = 0, hop2_count = 0, hop3_count = 0;

   
    for (int i = 0; i < MAX_FRIENDS; i++) {
        if (!students[studentIndex].friends[i].empty()) {
            hop1[hop1_count++] = students[studentIndex].friends[i];
        }
    }

   
    for (int i = 0; i < hop1_count; i++) {
        int friendIndex = findStudentIndex(hop1[i], students, total_students);
        if (friendIndex != -1) {
            for (int j = 0; j < MAX_FRIENDS; j++) {
                string friend_of_friend = students[friendIndex].friends[j];
                if (!friend_of_friend.empty() && friend_of_friend != student_name &&
                    !existsInArray(friend_of_friend, hop1, hop1_count) &&
                    !existsInArray(friend_of_friend, hop2, hop2_count)) {
                    hop2[hop2_count++] = friend_of_friend;
                }
            }
        }
    }

    
    for (int i = 0; i < hop2_count; i++) {
        int friendIndex = findStudentIndex(hop2[i], students, total_students);
        if (friendIndex != -1) {
            for (int j = 0; j < MAX_FRIENDS; j++) {
                string friend_of_friend_of_friend = students[friendIndex].friends[j];
                if (!friend_of_friend_of_friend.empty() && friend_of_friend_of_friend != student_name &&
                    !existsInArray(friend_of_friend_of_friend, hop1, hop1_count) &&
                    !existsInArray(friend_of_friend_of_friend, hop2, hop2_count) &&
                    !existsInArray(friend_of_friend_of_friend, hop3, hop3_count)) {
                    hop3[hop3_count++] = friend_of_friend_of_friend;
                }
            }
        }
    }

  
    cout << "\n1-hop Friends: ";
    for (int i = 0; i < hop1_count; i++) {
        cout << hop1[i] << ", ";
    }
    cout << endl;

    cout << "\n2-hop Friends: ";
    for (int i = 0; i < hop2_count; i++) {
        cout << hop2[i] << ", ";
    }
    cout << endl;

    cout << "\n3-hop Friends: ";
    for (int i = 0; i < hop3_count; i++) {
        cout << hop3[i] << ", ";
    }
    cout << endl;
}

int main() {
    ifstream file("Friends Dataset.csv");
    if (!file.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return 1;
    }

    Student students[MAX_STUDENTS];
    int total_students = 0;

    string line;
   
    getline(file, line);

    
    while (getline(file, line) && total_students < MAX_STUDENTS) {
        string tokens[MAX_FRIENDS + 1];
        int token_count = 0;
        split(line, ',', tokens, token_count);

        if (token_count > 0) {
            students[total_students].name = tokens[0];
            for (int i = 1; i < token_count && i <= MAX_FRIENDS; i++) {
                students[total_students].friends[i - 1] = tokens[i];
            }
            total_students++;
        }
    }

    file.close();

    // get input (student name) from user
    string student_name;
    cout << "Enter the name of the student: ";
    getline(cin, student_name);

    // function to find hops for the student input by user
    findHops(student_name, students, total_students);

    return 0;
}
