#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int main() {
    /*
    Read in file.
    Split line by spaces.
    Check if list is monotonic.
    Check if nth element is +/- 1 or 3 from n+1 element.
    */
    
    int total_levels = 0;
    std::ifstream file("input.txt");
    std::string line;
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // Split line by spaces
        std::vector<int> levels;
        std::istringstream iss(line);
        std::string token;
        
        while (iss >> token) {
            levels.push_back(std::stoi(token));
        }
        
        if (levels.size() <= 1) continue;
        
        // Determine monotonic direction from first two elements
        int monotonic = sign(levels[1] - levels[0]);
        bool add_count = true;
        
        // Check each adjacent pair
        for (size_t i = 0; i < levels.size() - 1; i++) {
            int curr_lvl = levels[i];
            int next_lvl = levels[i + 1];
            
            // Check if monotonic
            if (sign(next_lvl - curr_lvl) != monotonic) {
                add_count = false;
                break;
            }
            
            // Check if difference is between 1 and 3 (inclusive)
            int diff = std::abs(next_lvl - curr_lvl);
            if (diff < 1 || diff > 3) {
                add_count = false;
                break;
            }
        }
        
        if (add_count) {
            total_levels++;
        }
    }
    
    file.close();
    std::cout << "Total valid levels: " << total_levels << std::endl;
    
    return 0;
}