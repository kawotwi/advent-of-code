#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

struct Instruction {
    enum Type { MUL, DO, DONT };
    Type type;
    size_t position;
    int x,y; // for MUL instructions

    Instruction(Type t, size_t pos, int x_val = 0, int y_val = 0)
        : type(t), position(pos), x(x_val), y(y_val) {}
};

int main(){
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

    // sort all patterns of do and dont instructions.
    std::vector<Instruction> instructions;

    // implement a regex expression.
    std::regex mulPattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::sregex_iterator mul_iter(content.begin(), content.end(), mulPattern);
    std::sregex_iterator end;

    // process matches
    while (mul_iter != end) {
        std::smatch match = *mul_iter;

        size_t position = match.position();
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());

        instructions.emplace_back(Instruction::MUL, position, x, y);
        ++mul_iter;
    }

    // do() instructions
    std::regex doPattern(R"(do\(\))");
    std::sregex_iterator do_iter(content.begin(), content.end(), doPattern);

    while (do_iter != end) {
        std::smatch match = *do_iter;
        size_t position = match.position();
        instructions.emplace_back(Instruction::DO, position);
        ++do_iter;
    }

    // dont() instructions
    std::regex dontPattern(R"(don't\(\))");
    std::sregex_iterator dont_iter(content.begin(), content.end(), dontPattern);

    while (dont_iter != end) {
        std::smatch match = *dont_iter;
        size_t position = match.position();
        instructions.emplace_back(Instruction::DONT, position);
        ++dont_iter;
    }

    // sort instructions to process in order
    std::sort(instructions.begin(), instructions.end(),
              [](const Instruction& a, const Instruction& b) {
                return a.position < b.position;
              });
    
    std::cout << "\nFound " << instructions.size() << " total instructions" << std::endl;

    bool mul_enabled = true;
    long long total_sum = 0;
    int processed_muls = 0;
    int skipped_muls = 0;

    for (const auto& instruction : instructions) {
        switch (instruction.type) {
            case Instruction::DO:
                mul_enabled = true;
                std::cout << "Position " << instruction.position << ": do() - ENABLE." << std::endl;
                break;
            
            case Instruction::DONT:
                mul_enabled = false;
                std::cout << "Position " << instruction.position << ": don't() - DISABLED." << std::endl;
                break;
            
            case Instruction::MUL:
                if (mul_enabled) {
                    long long result = static_cast<long long>(instruction.x) * instruction.y;
                    total_sum += result;
                    processed_muls++;
                    std::cout << "Position " << instruction.position << ": mul(" << instruction.x 
                              << "," << instruction.y << ") = " << result << " [ENABLED - ADDED]" << std::endl;
                } else {
                    skipped_muls++;
                    std::cout << "Position " << instruction.position << ": mul(" << instruction.x 
                              << "," << instruction.y << ") = " << (instruction.x * instruction.y) 
                              << " [DISABLED - SKIPPED]" << std::endl;
                }
                break;
        }
    }

    // results
    std::cout << "\n**** RESULTS ****" << std::endl;
    std::cout << "Processed (enabled) multiplications: " << processed_muls << std::endl;
    std::cout << "Skipped (disabled) multiplications: " << skipped_muls << std::endl;
    std::cout << "Total sum of enabled multiplications: " << total_sum << std::endl;

    return 0;
}

