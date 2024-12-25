#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
    ifstream file("Friends Dataset.csv");
    if (!file) return cout << "Error opening file!", 1;

    unordered_map<string, unordered_set<string>> friends;
    string line, student, friendName;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, student, ',');
        while (getline(ss, friendName, ',')) friends[student].insert(friendName);
    }

    int threshold;
    cout << "Enter minimum threshold: ";
    cin >> threshold;

    vector<string> students;
    for (auto& entry : friends) students.push_back(entry.first);

    cout << "Potential friendships:\n";
    for (size_t i = 0; i < students.size(); ++i) {
        for (size_t j = i + 1; j < students.size(); ++j) {
            const string& s1 = students[i], &s2 = students[j];
            int common = 0;
            for (auto& f : friends[s1]) if (friends[s2].count(f)) ++common;
            if (common >= threshold) cout << s1 << " and " << s2 << " have " << common << " common friends.\n";
        }
    }

    return 0;
}
