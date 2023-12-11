#include <fstream>
#include <iostream>
#include <string>

int main() {

  std::ifstream infile("input");
  std::string numbers;

  int sum = 0;

  for (std::string line; getline(infile, line);) {
    for (char &c : line) {
      if (isdigit(c)) 
      {
        numbers += c;
      }
    }

    numbers.erase(numbers.begin() + 1, numbers.end() - 1);

    sum += stoi(numbers);
    numbers.clear();
  }

  std::cout << "The sum of the calibration values is: " << sum << std::endl;

  return 0;
}
