#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "parser.h"

std::string delimiter = ",";

std::vector<std::string> Parser::parse(std::ifstream &in) {
  std::vector<std::string> tokens;
  while (!in.eof()) {
    std::string token;
    while (!std::getline(in, token, ',').eof()) {
      tokens.push_back(token);
    }

    if (tokens.size() == 0)
      continue;

    // pass tokens to decoder
  }
  return tokens;
}
