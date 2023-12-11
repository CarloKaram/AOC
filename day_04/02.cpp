#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string.h>
#include <unordered_set>
#include <vector>

int main(int argc, char *argv[]) {

  std::unordered_set<int> hands;
  int number;
  int value = 0;
  int line_number = 0;
  int total_cards, scratchcards, matches;

  std::fstream infile(argv[1]);

  if (strcmp(argv[1], "sample") == 0) {
    total_cards = 13;
    scratchcards = 6;
  } else {
    total_cards = 35;
    scratchcards = 220;
  }

  std::vector<int> multipliers(scratchcards, 1);

  for (std::string line; getline(infile, line);) {

    line = line.substr(line.find(':') + 1);

    line.erase(remove(line.begin(), line.end(), '|'), line.end());

    std::stringstream card(line);

    while (!card.eof()) {
      card >> number;
      hands.insert(number);
    }

    matches = total_cards - hands.size();

    for (int i = line_number + 1; i <= line_number + matches; i++) {
      multipliers[i] += multipliers[line_number];
    }

    hands.clear();
    line_number += 1;
  }

  value = std::accumulate(multipliers.begin(), multipliers.end(), 0);
  std::cout << "The value of the scratchcards is: " << value << std::endl;

  return 0;
}
