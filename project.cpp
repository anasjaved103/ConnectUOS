#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>


int main() {
    ifstream file("Friends Dataset.csv");
    if (file.is_open()) {
        string line, word;
        while (getline(file, line)) {
            :stringstream ss(line);
            while (getline(ss, word, ',')) {
              cout << word << " ";
            }
            cout << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
    return 0;
}