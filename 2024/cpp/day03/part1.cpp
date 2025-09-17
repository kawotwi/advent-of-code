#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


int main(){
    std::cout << "Hello world!" << std::endl;
    std::ifstream file("input.txt");

    if (!file.is_open()){
        std::cerr << "Error: Could not open input.txt" << std::endl;
        return 1;
    }

    // read entire file content into a string
    std::string content;
    std::string line;
    while (std::getline(file, line)){
        content += line;
    }
    file.close();

    // implement a regex expression.
    std::regex mulPattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    long long totalSum = 0;
    std::sregex_iterator iter(content.begin(), content.end(), mulPattern);
    std::sregex_iterator end;

    // process matches
    while (iter != end) {
        std::smatch match = *iter;

        // extract the two numbers
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());

        // calculate the product and add for sum
        totalSum += static_cast<long long>(x) * y;

        ++iter;
    }

    std::cout << "\nTotal sum of all multiplications: " << totalSum << std::endl;
    
    return 0;
}
