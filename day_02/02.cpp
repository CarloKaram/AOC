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
  int sum = 0;
  int min_red = 1;
  int min_green = 1;
  int min_blue = 1;

  for (std::string game; getline(infile, game);) {

    game = game.substr(game.find(":") + 1);

    std::vector<std::string> sets = split(game, ';');

    for (auto set : sets) {
      std::vector<std::string> balls = split(set, ',');

      for (auto ball : balls) {
        std::string color = ball.substr(ball.find(" ") + 1);
        color = color.substr(color.find(" ") + 1);
        if (color == "red" && stoi(ball) > min_red) {
          min_red = stoi(ball);
        } else if (color == "green" && stoi(ball) > min_green) {
          min_green = stoi(ball);
        } else if (color == "blue" && stoi(ball) > min_blue) {
          min_blue = stoi(ball);
        }
      }
      balls.clear();
    }

    // std::cout << min_red << ", " << min_green << ", " << min_blue <<
    // std::endl;

    sum += min_red * min_green * min_blue;
    min_red = 0;
    min_green = 0;
    min_blue = 0;
    sets.clear();
  }

  std::cout << "The sum of the powers of the set of cubes is: " << sum
            << std::endl;
  return 0;
}
