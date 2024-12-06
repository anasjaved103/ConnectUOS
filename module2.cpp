
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    const int SIZE = 1000;
    string student1[SIZE], student2[SIZE];
    int count = 0;

    ifstream file("Friends Dataset.csv");
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    string line, s1, s2;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, s1, ',');
        getline(ss, s2, ',');
        student1[count] = s1;
        student2[count] = s2;
        count++;
    }
    file.close();

    cout << "Asymmetric Friendship Ordered Pairs:" << endl;
    for (int i = 0; i < count; i++) {
        bool found = false;
        for (int j = 0; j < count; j++) {
            if (student1[i] == student2[j] && student2[i] == student1[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "(" << student1[i] << ", " << student2[i] << ")" << endl;
        }
    }

    return 0;
}