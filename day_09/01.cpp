#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[]) {

  std::ifstream infile(argv[1]);
  std::vector<long> history;
  std::vector<std::vector<long>> sequences;
  std::vector<long> seq;
  long val;
  int index = 1;
  long ans = 0;

  for (std::string line; getline(infile, line);) {

    std::stringstream values(line);

    while (!values.eof()) {
      values >> val;
      history.push_back(val);
    }

    sequences.push_back(history);

    while (std::any_of(history.begin(), history.end(),
                       [](long num) { return num != 0; })) {

      seq.push_back(history[index] - history[index - 1]);

      if (index == history.size() - 1) {
        sequences.push_back(seq);
        history.clear();
        history = seq;
        seq.clear();
        index = 0;
      }
      index += 1;
    }

    // Append 0 to sequence of zeros
    sequences.back().push_back(0);

    for (int i = sequences.size() - 2; i >= 0; i--) {
      long append = sequences[i].back() + sequences[i + 1].back();
      sequences[i].push_back(append);
    }

    ans += sequences[0].back();

    sequences.clear();
    history.clear();
    values.clear();
  }

  std::cout << ans << std::endl;

  return 0;
}
