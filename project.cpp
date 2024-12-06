#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>


int main() {
    std::ifstream file("Friends Dataset.csv");
    if (file.is_open()) {
        std::string line, word;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            while (std::getline(ss, word, ',')) {
                std::cout << word << " ";
            }
            std::cout << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }
    return 0;
}