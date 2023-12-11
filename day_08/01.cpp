#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {

  std::ifstream infile(argv[1]);
  char direction;
  std::string startingPoint = "AAA";
  int steps = 0;
  int i = 0;

  std::string instructions;
  getline(infile, instructions);

  std::unordered_map<std::string, std::vector<std::string>> navigator;

  // Build map
  for (std::string line; getline(infile, line);) {

    navigator[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
  }

  while (startingPoint != "ZZZ") {
    direction = instructions[i];
    steps += 1;

    if (direction == 'L')
      startingPoint = navigator[startingPoint][0];
    else
      startingPoint = navigator[startingPoint][1];

    if (i == instructions.size() - 1 && startingPoint != "ZZZ") {
      i = -1;
    }

    i += 1;
  }

  std::cout << "The total number of steps to reach ZZZ is: " << steps
            << std::endl;

  return 0;
}
