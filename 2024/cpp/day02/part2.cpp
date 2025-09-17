#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Fast inline sign function
inline int sign(int x) {
    return (x > 0) - (x < 0);
}

// Check if a sequence is valid (monotonic with differences of 1-3)
bool isValidSequence(const std::vector<int>& levels) {
    const size_t size = levels.size();
    if (size <= 1) return true;
    
    const int startDirection = sign(levels[1] - levels[0]);
    if (startDirection == 0) return false; // No change between first elements
    
    for (size_t i = 0; i < size - 1; ++i) {
        const int diff = levels[i + 1] - levels[i];
        const int currentDirection = sign(diff);
        const int absDiff = (diff < 0) ? -diff : diff;
        
        if (currentDirection != startDirection || absDiff < 1 || absDiff > 3) {
            return false;
        }
    }
    return true;
}

// Helper function to check validity after removing element at index
bool isValidAfterRemoval(const std::vector<int>& levels, size_t removeIndex) {
    const size_t size = levels.size();
    if (size <= 2) return true; // After removal, size would be <= 1
    
    // Build new sequence without the removed element
    std::vector<int> temp;
    temp.reserve(size - 1);
    for (size_t i = 0; i < size; ++i) {
        if (i != removeIndex) {
            temp.push_back(levels[i]);
        }
    }
    
    return isValidSequence(temp);
}

// Check if sequence can be made valid by removing exactly one element
bool canBeValidReport(const std::vector<int>& levels) {
    const size_t size = levels.size();
    if (size <= 1) return true;
    
    // First check if already valid without removal
    if (isValidSequence(levels)) return true;
    
    // Try removing each element one by one
    // This is the most reliable approach for correctness
    for (size_t i = 0; i < size; ++i) {
        if (isValidAfterRemoval(levels, i)) {
            return true;
        }
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    // Handle command line arguments
    const char* filename = (argc >= 2) ? argv[1] : "input.txt";
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        }
        return 1;
    }
    
    int totalValid = 0;
    std::string line;
    std::vector<int> levels;
    levels.reserve(16); // Reserve reasonable space
    
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Parse integers from line
        levels.clear();
        std::istringstream iss(line);
        int num;
        
        while (iss >> num) {
            levels.push_back(num);
        }
        
        // Skip lines with insufficient data
        if (levels.size() <= 1) continue;
        
        // Check if this report can be made valid
        if (canBeValidReport(levels)) {
            ++totalValid;
        }
    }
    
    std::cout << "Total valid reports: " << totalValid << std::endl;
    return 0;
}
