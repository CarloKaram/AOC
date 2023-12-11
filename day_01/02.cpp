#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::ifstream infile("input");
  std::string numbers;
  std::map<std::string, std::string> dict = {
      {"one", "1"},   {"two", "2"},   {"three", "3"},
      {"four", "4"},  {"five", "5"},  {"six", "6"},
      {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};

  int sum = 0;

  for (std::string line; getline(infile, line);) {
    for (int i = 0; i < line.length(); i++) {
      if (isdigit(line[i])) {
        numbers += line[i];
      }

      for (const auto &[key, value] : dict) {
        if (line.substr(i).rfind(key, 0) == 0) {
          numbers += value;
        }
      }
    }

    numbers.erase(numbers.begin() + 1, numbers.end() - 1);

    sum += stoi(numbers);
    numbers.clear();
  }

  std::cout << "The sum of the calibration values is: " << sum << std::endl;

  return 0;
}
