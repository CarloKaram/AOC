#include <algorithm>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <tuple>
#include <vector>

bool isAsterisk(char c) { return (c == '*'); }

int main(int argc, char *argv[]) {

  std::ifstream infile(argv[1]);
  int line_num = 0;
  int sum = 0;
  int rows, cols;

  if (strcmp(argv[1], "sample") == 0) {
    rows = 12;
    cols = 12;
  } else {
    rows = 142;
    cols = 142;
  }

  std::vector<std::tuple<int, int>> gears;
  std::vector<int> ratios;

  char arr[rows][cols];

  // Build array from engine schematic
  for (std::string line; getline(infile, line);) {

    for (int i = 0; i < line.length(); i++) {
      arr[line_num + 1][i + 1] = line[i];
    }

    line_num += 1;
  }

  // Add top and bottom row margin
  for (int j = 0; j < cols; j++) {
    arr[0][j] = '.';
    arr[rows - 1][j] = '.';
  }

  // Add first and last column margin
  for (int i = 0; i < rows; i++) {
    arr[i][0] = '.';
    arr[i][cols - 1] = '.';
  }

  // Detect number
  for (int i = 1; i <= rows - 2; i++) {
    int j = 1;
    while (j <= cols - 2) {
      int start = j;
      std::string num = "";

      while (j <= cols - 2 && isdigit(arr[i][j])) {
        num += arr[i][j];
        j += 1;
      }

      if (num == "") {
        j += 1;
        continue;
      }

      for (int k = i - 1; k <= i + 1; k++) {
        for (int l = start - 1; l <= j; l++) {
          if (arr[k][l] == '*' && !(std::count(gears.begin(), gears.end(),
                                               std::make_tuple(k, l)))) {
            gears.push_back(std::make_tuple(k, l));
            ratios.push_back(stoi(num));
          } else if (arr[k][l] == '*') {
            int idx =
                std::find(gears.begin(), gears.end(), std::make_tuple(k, l)) -
                gears.begin();
            sum += stoi(num) * ratios[idx];
          }
        }
      }
    }
  }

  std::cout << "The sum of the gear ratios is: " << sum << std::endl;
}
