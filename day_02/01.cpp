#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string &s, char delim) {

  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

int main() {

  std::ifstream infile("input");
  bool valid = true;
  int game_id = 0;
  int sum = 0;

  for (std::string game; getline(infile, game);) {

    game_id += 1;

    game = game.substr(game.find(":") + 1);

    std::vector<std::string> sets = split(game, ';');

    for (auto set : sets) {
      std::vector<std::string> balls = split(set, ',');

      for (auto ball : balls) {
        std::string color = ball.substr(ball.find(" ") + 1);
        color = color.substr(color.find(" ") + 1);
        if ((color == "red" && stoi(ball) > 12) ||
            (color == "green" && stoi(ball) > 13) ||
            (color == "blue" && stoi(ball) > 14)) {
          valid = false;
          break;
        }
      }
      balls.clear();
    }

    if (valid == true)
      sum += game_id;

    valid = true;
    sets.clear();
  }

  std::cout << "The sum of the valid games' IDs is: " << sum << std::endl;
  return 0;
}
