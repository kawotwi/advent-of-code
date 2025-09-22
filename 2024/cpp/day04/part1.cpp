#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

bool searchWord(const std::vector<std::string>& grid, 
                const std::string& word, 
                int startRow, int startCol, 
                int dirRow, int dirCol) {
    
    int rows = grid.size();
    int cols = grid[0].size();
    
    for (int i = 0; i < word.length(); i++) {
        int newRow = startRow + i * dirRow;
        int newCol = startCol + i * dirCol;
        
        // Check bounds
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
            return false;
        }
        
        // Check character match
        if (grid[newRow][newCol] != word[i]) {
            return false;
        }
    }
    return true;
}

int countWordOccurrences(const std::vector<std::string>& grid, 
                        const std::string& word) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    
    std::vector<std::pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    
    // Try every position as a starting point
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // Try every direction from this position
            for (auto& dir : directions) {
                if (searchWord(grid, word, row, col, dir.first, dir.second)) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {

    std::ifstream file("input.txt");

    if (!file.is_open()){
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    // read entire file content into a string 
    std::string line;
    std::vector<std::string> grid;
    
    while (std::getline(file, line)){
        grid.push_back(line);
    }
    file.close();

    // grid dimensions
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::pair<int, int>> directions = {
        {0, 1},   // Right (horizontal)
        {0, -1},  // Left (horizontal backward)
        {1, 0},   // Down (vertical)
        {-1, 0},  // Up (vertical backward)
        {1, 1},   // Down-right (diagonal)
        {1, -1},  // Down-left (diagonal)
        {-1, 1},  // Up-right (diagonal)
        {-1, -1}  // Up-left (diagonal)
    };

    // Search for word (e.g., "XMAS")
    std::string targetWord = "XMAS";
    int totalCount = countWordOccurrences(grid, targetWord);
    
    std::cout << "Found '" << targetWord << "' " << totalCount << " times" << std::endl;
    
    return 0;

}