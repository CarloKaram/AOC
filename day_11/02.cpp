#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct ind_pair {
  int x;
  int y;
};

std::vector<std::vector<char>> buildMap(std::string filename) {

  std::vector<std::vector<char>> observation;
  std::ifstream infile(filename);
  char body;

  for (std::string line; getline(infile, line);) {

    std::vector<char> temp;

    std::stringstream sequence(line);

    while (sequence >> body) {
      temp.push_back(body);
    }

    observation.push_back(temp);
  }

  return observation;
}

int main(int argc, char *argv[]) {

  std::vector<std::vector<char>> image = buildMap(argv[1]);
  std::vector<ind_pair> coords;
  ind_pair index;

  long exp_x = 0;
  long exp_y = 0;

  // Find coordinates of galaxies
  for (int i = 0; i < image.size(); i++) {

    if (std::none_of(image[i].begin(), image[i].end(),
                     [](char c) { return c == '#'; })) {
      exp_y += 1000000 - 1;
    }

    for (int j = 0; j < image[0].size(); j++) {

      std::vector<char> temp;

      for (auto &seq : image) {
        temp.push_back(seq[j]);
      }

      if (std::none_of(temp.begin(), temp.end(),
                       [](char c) { return c == '#'; })) {
        exp_x += 1000000 - 1;
      }

      if (image[i][j] == '#') {
        index.x = j + exp_x;
        index.y = i + exp_y;
        coords.push_back(index);
      }
    }
    exp_x = 0;
  }

  long sum = 0;

  while (coords.size() > 0) {

    index = coords.back();
    coords.pop_back();

    for (auto &coord : coords) {
      sum += abs(index.x - coord.x) + abs(index.y - coord.y);
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
