#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct ind_pair {
  int row;
  int col;
};

ind_pair findStart(std::vector<std::vector<char>> network) {

  ind_pair location;

  for (int i = 0; i < network.size(); i++) {
    auto start_index = std::find(network[i].begin(), network[i].end(), 'S');
    if (start_index != network[i].end()) {
      location.row = i;
      location.col = start_index - network[i].begin();
      break;
    }
  }

  std::cout << "Found start location at: (" << location.row << ", "
            << location.col << ")" << std::endl;

  return location;
}

std::vector<std::vector<char>> buildMap(std::string filename) {

  std::vector<std::vector<char>> network;
  std::ifstream infile(filename);
  std::vector<char> temp;
  char pipe;

  for (std::string line; getline(infile, line);) {

    std::stringstream sequence(line);

    while (!sequence.eof()) {
      sequence >> pipe;
      temp.push_back(pipe);
    }

    network.push_back(temp);

    temp.clear();
    sequence.clear();
  }

  // Append dots to avoid checking for limits
  for (int i = 0; i < network.size(); i++) {
    network[i].push_back('.');
    network[i].insert(network[i].begin(), '.');
  }

  for (int i = 0; i < network[i].size(); i++) {
    temp.push_back('.');
  }

  network.push_back(temp);
  network.insert(network.begin(), temp);

  std::cout << "Built map successfully!" << std::endl;

  return network;
}

int main(int argc, char *argv[]) {

  std::vector<ind_pair> indices;
  int loop_length = 0;

  // Build vector map of pipes
  std::vector<std::vector<char>> pipe_network = buildMap(argv[1]);

  // Find start location
  ind_pair start_location = findStart(pipe_network);
  ind_pair new_start = start_location;

  pipe_network[start_location.row][start_location.col] = '7';

  // Navigate
  while (true) {
    int i = new_start.row;
    int j = new_start.col;

    if (pipe_network[i][j] == '|' || pipe_network[i][j] == 'L' ||
        pipe_network[i][j] == 'J') {
      if (i - 1 < start_location.row) {
        new_start.row = i - 1;
      } else if (pipe_network[i][j] == '|') {
        new_start.row = i + 1;
      } else if (pipe_network[i][j] == 'L') {
        new_start.col = j + 1;
      } else {
        new_start.col = j - 1;
      }
    } else if (pipe_network[i][j] == '7' || pipe_network[i][j] == 'F') {
      if (i + 1 > start_location.row) {
        new_start.row = i + 1;
      } else if (pipe_network[i][j] == '7') {
        new_start.col = j - 1;
      } else {
        new_start.col = j + 1;
      }
    } else if (pipe_network[i][j] == '-') {
      if (j + 1 > start_location.col) {
        new_start.col = j + 1;
      } else {
        new_start.col = j - 1;
      }
    } else if (pipe_network[i][j] == 'S') {
      break;
    }

    loop_length += 1;

    if (loop_length == 1) {
      pipe_network[start_location.row][start_location.col] = 'S';
    }

    start_location.row = i;
    start_location.col = j;
  }

  std::cout << loop_length / 2 << std::endl;

  return 0;
}
