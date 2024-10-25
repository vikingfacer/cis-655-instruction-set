#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "parser.h"

int main(int argc, char* argv[]) {
    Parser parser;

    std::cout << std::endl;
    if (argc != 2) {
        std::cout << "usage: parser <instruction_file>" << std::endl;
        std::exit(0);
    }

    std::string inputFileName = argv[1];
    std::ifstream inputStream(inputFileName);
    if (!inputStream.is_open()) {
        std::cout << "Faiced to open file." << std::endl << std::endl;
        std::exit(1);
    }

    std::vector<std::string> output = parser.parse(inputStream);
    inputStream.close();
    
    std::cout << std::endl << "Commands passed successfully." << std::endl;

    for(const std::string line : output) 
        std::cout << line << std::endl;
}
