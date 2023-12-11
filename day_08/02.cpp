#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {

  std::ifstream infile(argv[1]);
  char direction;
  std::vector<long> steps;
  long step = 0;
  long lcm = 1;
  std::vector<std::string> startingPoints;

  int i = 0;

  std::string instructions;
  getline(infile, instructions);

  std::unordered_map<std::string, std::vector<std::string>> navigator;

  // Build map
  for (std::string line; getline(infile, line);) {

    navigator[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
  }

  // Build starting points vector
  for (auto &pair : navigator) {
    if (pair.first[2] == 'A')
      startingPoints.push_back(pair.first);
  }

  for (auto startingPoint : startingPoints) {
    step = 0;

    while (startingPoint[2] != 'Z') {
      direction = instructions[i];

      step += 1;

      if (direction == 'L')
        startingPoint = navigator[startingPoint][0];
      else
        startingPoint = navigator[startingPoint][1];

      if (i == instructions.size() - 1 && startingPoint[2] != 'Z')
        i = -1;

      i += 1;
    }

    lcm = std::lcm(lcm, step);
  }

  std::cout << "The total number of steps to reach ZZZ is: " << lcm
            << std::endl;

  return 0;
}
