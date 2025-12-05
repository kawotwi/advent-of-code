#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// finish decorating north pole.

int countZeroCrossings(int start, int distance, char direction) {
    int count = 0;
    int pos = start;
    
    for (int i = 0; i < distance; i++) {
        if (direction == 'L') {
            pos--;
            if (pos < 0) pos = 99;
        } else {
            pos++;
            if (pos > 99) pos = 0;
        }
        
        if (pos == 0) {
            count++;
        }
    }
    
    return count;
}


int main() {
    std::ifstream input("input.txt");
    if (!input.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    
    int position = 50;  // Starting position
    int password = 0;   // Count of times dial points to 0
    
    std::string line;
    int lineNum = 0;
    while (std::getline(input, line)) {
        if (line.empty()) continue;
        lineNum++;
        
        char direction = line[0];  // 'L' or 'R'
        int distance = std::stoi(line.substr(1));  // Number after L/R
        
        // Count zero crossings during this rotation
        int crossings = countZeroCrossings(position, distance, direction);
        password += crossings;
        
        // Update position
        if (direction == 'L') {
            position = (position - distance) % 100;
            if (position < 0) position += 100;
        } else {
            position = (position + distance) % 100;
        }
        
        // Debug output for first few lines
        if (lineNum <= 10) {
            std::cout << line << ": " << position << " (zeros: " << crossings << ", total: " << password << ")" << std::endl;
        }
    }
    
    input.close();
    
    std::cout << "\nThe password is: " << password << std::endl;
    
    return 0;
}