#include <stdio.h>

#include <algorithm>  // sorting algo
#include <cmath>      // using abs()
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
    // Open input file for reading
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    ifstream filein(argv[1]);
    if (!filein) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    // initialize variables for left and right list, and line for file.
    string line;
    vector<int> left_list;
    vector<int> right_list;

    left_list.reserve(1000);
    right_list.reserve(1000);

    while (getline(filein, line)) {
        istringstream iss(line);  // stringstream treats like input source
        int left, right;

        if (iss >> left >> right) {
            left_list.push_back(left);
            right_list.push_back(right);
        }
    }

    // sort both lists
    std::sort(left_list.begin(), left_list.end());
    std::sort(right_list.begin(), right_list.end());

    // calculate pairs and distances
    int total_distance = 0;
    for (int i = 0; i < left_list.size(); i++) {
        total_distance += abs(left_list[i] - right_list[i]);
    }
    cout << "Total Distance: " << total_distance << endl;
    filein.close();  // close the file
    return 0;
}
