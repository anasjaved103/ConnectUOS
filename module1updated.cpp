                       // By Muhammad Anas bin Javed.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    const int SIZE = 2000;
    string names[SIZE];
    int counts[SIZE] = {0};
    int maxCount = 0;
    string mostPopularName;
    int numNames = 0;

    ifstream file("Friends Dataset.csv");
    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return 1;
    }

    string line, name;
    while (getline(file, line)) {
        stringstream ss(line);
        while (getline(ss, name, ',')) {
            names[numNames] = name;
            numNames++;
        }
    }
    file.close();

    for (int i = 0; i < numNames; i++) {
        for (int j = 0; j < numNames; j++) {
            if (names[i] == names[j]) {
                counts[i]++;
            }
        }
    }

    for (int i = 0; i < numNames; i++) {
        if (counts[i] > maxCount) {
            maxCount = counts[i];
            mostPopularName = names[i];
        }
    }

    cout << "Most Popular Student: " << mostPopularName << endl;
    cout << mostPopularName << " has " << maxCount - 1 << " friends." << endl;

    return 0;
}
