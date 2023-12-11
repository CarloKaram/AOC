#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef std::array<std::vector<std::vector<long>>, 7> arrOfVec;
typedef std::vector<std::vector<long>> vecOfVec;

arrOfVec fileMaps(std::string inFile) {

  int index = 0;
  long num;

  std::vector<long> temp;
  arrOfVec maps;

  std::fstream infile(inFile);

  for (std::string line; getline(infile, line);) {

    if (std::any_of(line.begin(), line.end(), ::isdigit)) {
      std::stringstream range(line);

      while (!range.eof()) {
        range >> num;
        temp.push_back(num);
      }

      maps[index - 1].push_back(temp);
      temp.clear();
    } else if (!line.empty()) {
      index += 1;
    }
  }
  return maps;
}

long findLocation(arrOfVec maps, long seed) {

  long res = seed;

  for (int i = 0; i < 7; i++) {
    vecOfVec map = maps[i];

    for (std::vector<long> &row : map) {
      if (res >= row[1] && res < row[1] + row[2]) {
        res = row[0] + (res - row[1]);
        break;
      }
    }
  }

  return res;
}

int main(int argc, char *argv[]) {

  // Construct array of maps
  arrOfVec maps = fileMaps(argv[1]);

  std::vector<long> seeds = {1482445116, 339187393, 3210489476, 511905836,
                             42566461,   51849137,  256584102,  379575844,
                             3040181568, 139966026, 4018529087, 116808249,
                             2887351536, 89515778,  669731009,  806888490,
                             2369242654, 489923931, 2086168596, 82891253};

  std::vector<long> locations;

  for (auto &seed : seeds) {
    locations.push_back(findLocation(maps, seed));
  }

  std::cout << *std::min_element(locations.begin(), locations.end())
            << std::endl;

  return 0;
}
