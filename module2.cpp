#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int MAX_PEOPLE = 100; 

int main() {
    string names[MAX_PEOPLE];        
    bool friendships[MAX_PEOPLE][MAX_PEOPLE] = {false}; 
    int totalPeople = 0;

   
    ifstream file("Friends Dataset.csv");
    if (!file.is_open()) {
        cout << "Error: Unable to open the file!" << endl;
        return 1;
    }

   
    string line;
    getline(file, line); 
    while (getline(file, line)) {
        stringstream ss(line);
        string person, friendName;
        getline(ss, person, ','); 

        
        int personIndex = -1;
        for (int i = 0; i < totalPeople; i++) {
            if (names[i] == person) {
                personIndex = i;
                break;
            }
        }
        if (personIndex == -1) {
            personIndex = totalPeople;
            names[totalPeople++] = person;
        }

        
        while (getline(ss, friendName, ',')) {
            if (!friendName.empty()) {
                int friendIndex = -1;
                for (int i = 0; i < totalPeople; i++) {
                    if (names[i] == friendName) {
                        friendIndex = i;
                        break;
                    }
                }
                if (friendIndex == -1) {
                    friendIndex = totalPeople;
                    names[totalPeople++] = friendName;
                }

                friendships[personIndex][friendIndex] = true;
            }
        }
    }
    file.close();

                                               // Find asymmetric relationships using Loops
    cout << "Asymmetric Friendships:" << endl;
    for (int i = 0; i < totalPeople; i++) {
        for (int j = 0; j < totalPeople; j++) {
            if (friendships[i][j] && !friendships[j][i]) {
                cout << names[i] << " lists " << names[j] << " as a friend,but HE/SHE didn't" << endl;
            }
        }
    }

    return 0;
}