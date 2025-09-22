#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

bool isXMAS(const std::vector<std::string> & grid, int r, int c, int max_rows, int max_cols) {
    // check that chunk is within bounds
    if (r - 1 < 0 || r + 1 >= max_rows || c - 1 < 0 || c + 1 >= max_cols) return false;
    
    // check if MAS is within diagonal
    if (grid[r-1][c-1] == 'M' && grid[r][c] == 'A' && grid[r+1][c+1] == 'S'){
        if (grid[r-1][c+1] == 'M' && grid[r][c] == 'A' && grid[r+1][c-1] == 'S'){
            return true;
        } else if (grid[r+1][c-1] == 'M' && grid[r][c] == 'A' && grid[r-1][c+1] == 'S'){
            return true;
        }
    } 
    // check SAM mirrored diagnoal
    if (grid[r-1][c-1] == 'S' && grid[r][c] == 'A' && grid[r+1][c+1] == 'M'){
        if (grid[r-1][c+1] == 'S' && grid[r][c] == 'A' && grid[r+1][c-1] == 'M'){
            return true;
        }else if (grid[r+1][c-1] == 'S' && grid[r][c] == 'A' && grid[r-1][c+1] == 'M'){
            return true;
        }
    }
    // if neither if statement works select false
    return false;
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
    size_t max_cols = 0;
    
    while (std::getline(file, line)){
        grid.push_back(line);
        if (line.size() > max_cols) {max_cols = line.size();}
    }
    file.close();

    // Pad all rows to max_cols
    for (auto& row : grid) {
        if (row.size() < max_cols) {
            row.append(max_cols - row.size(), ' ');
        }
    }

    // grid dimensions
    int rows = grid.size();
    int cols = grid[0].size();

    // Search for word (e.g., "XMAS")
    std::string targetWord = "XMAS";
    int totalCount = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (isXMAS(grid, row, col, rows, cols)){
                ++totalCount;
            }
        }
    }
    
    std::cout << "Found '" << targetWord << "' " << totalCount << " times" << std::endl;
    
    return 0;

}