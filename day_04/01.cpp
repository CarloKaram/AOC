#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_set>

int main(int argc, char *argv[]) {

  std::unordered_set<int> hands;
  int number;
  int value = 0;
  int total_cards;

  std::fstream infile(argv[1]);

  if (strcmp(argv[1], "sample") == 0)
    total_cards = 13;
  else
    total_cards = 35;

  for (std::string line; getline(infile, line);) {

    line = line.substr(line.find(':') + 1);

    line.erase(remove(line.begin(), line.end(), '|'), line.end());

    std::stringstream card(line);

    while (!card.eof()) {
      card >> number;
      hands.insert(number);
    }

    if (hands.size() != total_cards)
      value += std::pow(2, total_cards - hands.size() - 1);

    hands.clear();
  }

  std::cout << "The value of the scratchcards is: " << value << std::endl;

  return 0;
}
