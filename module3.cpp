#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const int SIZE = 1000;

struct Graph {
    int adjMatrix[SIZE][SIZE];
    int numVertices;
};

void createGraph(Graph& graph, string names[], int numNames) {
    graph.numVertices = numNames;
    for (int i = 0; i < numNames; i++) {
        for (int j = 0; j < numNames; j++) {
            if (i != j) {
                graph.adjMatrix[i][j] = 1; // assume all students are friends
            } else {
                graph.adjMatrix[i][j] = 0;
            }
        }
    }
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            cout << graph.adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
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

    Graph graph;
    createGraph(graph, names, numNames);
    printGraph(graph);

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
