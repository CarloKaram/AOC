#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
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

std::tuple<long, long> findLocation(arrOfVec &maps,
                                    std::tuple<long, long> &seed) {

  std::vector<long> unrolled_ranges;
  std::vector<long> destination_ranges;
  std::vector<std::tuple<long, long>> source_ranges;
  std::tuple<long, long> source;
  std::tuple<long, long> final_dest;
  int dest_size;

  // Initialize source_ranges
  source_ranges.push_back(seed);

  long temp = 0;

  for (int i = 0; i < 7; i++) {
    vecOfVec map = maps[i];

    destination_ranges.clear();

    while (!source_ranges.empty()) {

      // Clear vectors
      // destination_ranges.clear();
      unrolled_ranges.clear();

      // Extract source from vector and pop
      source = source_ranges.back();
      source_ranges.pop_back();

      // Compute start and end
      long start = get<0>(source);
      long end = get<1>(source);

      // Unroll ranges
      for (std::vector<long> &row : map) {
        unrolled_ranges.push_back(row[1]);
        unrolled_ranges.push_back(row[1] + row[2] - 1);
      }

      // Push back original seed range
      unrolled_ranges.push_back(start);
      unrolled_ranges.push_back(end);

      // Sort ranges
      std::sort(unrolled_ranges.begin(), unrolled_ranges.end());

      // Keep relevant ranges
      std::erase_if(unrolled_ranges, [start, end](long x) {
        return (x < start || x > end || x == 0);
      });

      // Find destination for ranges
      for (long source : unrolled_ranges) {
        temp = source;
        for (std::vector<long> &row : map) {
          if (source >= row[1] && source < row[1] + row[2]) {
            temp = row[0] + source - row[1];
            break;
          }
        }
        destination_ranges.push_back(temp);
      }

      std::erase_if(destination_ranges, [](long val) { return (val == 0); });

      // Sort destination ranges
      std::sort(destination_ranges.begin(), destination_ranges.end());

      // std::cout << destination_ranges.size() << std::endl;
    }

    // Construct tuples
    for (int j = 0; j < destination_ranges.size(); j++) {
      source_ranges.push_back(
          std::make_tuple(destination_ranges[j], destination_ranges[j + 1]));
    }
  }

  return source_ranges[0];
}

int main(int argc, char *argv[]) {

  // Construct array of maps
  arrOfVec maps = fileMaps(argv[1]);

  std::vector<long> inputs = {1482445116, 339187393, 3210489476, 511905836,
                              42566461,   51849137,  256584102,  379575844,
                              3040181568, 139966026, 4018529087, 116808249,
                              2887351536, 89515778,  669731009,  806888490,
                              2369242654, 489923931, 2086168596, 82891253};

  // std::vector<long> inputs = {79, 14}; // 55, 13};
  std::vector<std::tuple<long, long>> seed_ranges;
  std::vector<std::tuple<long, long>> location_ranges;

  // Build start-end seed ranges
  for (int i = 0; i < inputs.size(); i += 2) {
    seed_ranges.push_back(
        std::make_tuple(inputs[i], inputs[i] + inputs[i + 1] - 1));
  }

  for (int i = 0; i < seed_ranges.size(); i++) {
    location_ranges.push_back(findLocation(maps, seed_ranges[i]));
  }

  std::sort(location_ranges.begin(), location_ranges.end());

  // for (auto &location : location_ranges) {
  //   std::cout << get<0>(location) << ", " << get<1>(location) << std::endl;
  // }

  std::cout << "The minimum location is: " << get<0>(location_ranges[0])
            << std::endl;

  return 0;
}
