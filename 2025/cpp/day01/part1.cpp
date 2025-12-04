#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// finish decorating north pole.

void rotate_dial(int & dial_num, const string &line){
    char direction = line[0];
    if (direction == 'R' || direction == 'L'){
        string substr(line.begin() + 1, line.end()); // ignoring first char
        int rotation = std::stoi(substr);
        if (direction == 'R'){
            dial_num = (dial_num + rotation) % 100;
        } else if (direction == 'L'){
            dial_num = (dial_num - rotation) % 100;
            if (dial_num < 0) {
                dial_num += 100;
            }
    }
    } else {
        std::cerr << "Invalid Line. Continue." << std::endl;
        return;
    }

}


int main()
{
    //fstream for opening files 
    // fstream filein(filename, ios::in);
    const std::string filename = "input.txt";
    std::ifstream filein(filename);

    // initial error check
    if (!filein){
        cerr << "Error reading file, please check filename." << std::endl;
    }

    std::string line;
    int dial_num = 50;
    int password = 0;
    while (std::getline(filein, line)){
        if (line.empty()) continue;
        string rotation;
        rotate_dial(dial_num, line);

        if (dial_num == 0){
            password++;
        }
        
        std::cout << "The dial is rotated " << line << " to point at " << dial_num << std::endl;
    }

    std::cout << "Final Password: " << password << std::endl;

    filein.close();
    return 0;
}