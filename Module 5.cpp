/* MODULE 5. Create a multiciplity graph to represented weighted strength between two students.
A weighted edge between two students represent the number of common friends. */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 40;  // max number of students
const int MAX_FRIENDS = 5;    // max friends of each student
struct Student{
    string name;
    string friends[MAX_FRIENDS];
}; 
void loadStudents(const string& filename, Student students[], int& total_students){
    ifstream file("Friends Dataset.csv");
    if (!file){
        cout << "Error: Could not open the file!" << endl;
        return;
}
    string line;
    getline(file, line); 
    total_students = 0;
    while (getline(file, line) && total_students < MAX_STUDENTS){
        stringstream ss(line);
        getline(ss, students[total_students].name, ',');
        for (int i = 0; i < MAX_FRIENDS && getline(ss, students[total_students].friends[i], ','); i++);
        total_students++;
    }
    file.close();
}
int countCommonFriends(const Student& s1, const Student& s2){
    int count = 0;
    for (int i = 0; i < MAX_FRIENDS; i++)
        for (int j = 0; j < MAX_FRIENDS; j++)
            if (!s1.friends[i].empty() && s1.friends[i] == s2.friends[j])
                count++;
    return count;
}
void MultiplicityGraph(Student students[], int total_students){
    cout << "\nMultiplicity Graph (Weighted Edges):" << endl;
    for (int i = 0; i < total_students; i++)
        for (int j = i + 1; j < total_students; j++){
            int common = countCommonFriends(students[i], students[j]);
				if (common > 0){
    			cout << "Edge between " << students[i].name << " and " << students[j].name
         		<< " (Weight: " << common << ")" << endl;
		}
    }
}
int main()
{
    Student students[MAX_STUDENTS];
    int total_students = 0;
    loadStudents("Friends Dataset.csv", students, total_students);
    MultiplicityGraph(students, total_students);

    return 0;
}
