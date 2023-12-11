#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

std::string reRank(std::string &hand) {

  std::unordered_map<char, char> letterMap{
      {'T', 'A'}, {'J', 'B'}, {'Q', 'C'}, {'K', 'D'}, {'A', 'E'}};
  std::string remapped;

  for (char &c : hand) {
    if (letterMap[c] == '\0')
      remapped += c;
    else
      remapped += letterMap[c];
  }

  return remapped;
}

int assignRank(std::string &hand) {

  int rep = 0;
  int card = 0;

  std::unordered_map<char, int> charCount;

  for (char &ch : hand) {
    if (charCount.find(ch) != charCount.end()) {
      charCount[ch]++;
    } else {
      charCount[ch] = 1;
    }
  }

  for (const auto &pair : charCount) {
    if (pair.second > 1) {
      card += 1;
      rep += pair.second;
    }
  }

  if (rep == 5) {
    if (card == 1)
      return 6;
    else
      return 4;
  }
  if (rep == 4) {
    if (card == 1)
      return 5;
    else
      return 2;
  }
  if (rep == 3) {
    return 3;
  }
  if (rep == 2) {
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {

  std::ifstream infile(argv[1]);

  std::vector<std::tuple<std::string, int>> hand_bid_pair;
  std::vector<int> ranks;

  std::string hand;
  int bid;
  int ans = 0;

  while (infile >> hand >> bid) {

    hand_bid_pair.push_back(std::make_tuple(hand, bid));
  }

  for (auto &pair : hand_bid_pair) {
    ranks.push_back(assignRank(std::get<0>(pair)));
  }

  std::sort(hand_bid_pair.begin(), hand_bid_pair.end(),
            [](std::tuple<std::string, int> a, std::tuple<std::string, int> b) {
              return std::make_tuple(assignRank(std::get<0>(a)),
                                     reRank(std::get<0>(a))) >
                     std::make_tuple(assignRank(std::get<0>(b)),
                                     reRank(std::get<0>(b)));
            });

  std::reverse(hand_bid_pair.begin(), hand_bid_pair.end());

  int rank = 1;

  for (auto &pair : hand_bid_pair) {
    ans += rank * std::get<1>(pair);
    rank++;
  }

  std::cout << "The answer is: " << ans << std::endl;

  return 0;
}
