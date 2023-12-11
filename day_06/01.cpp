#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <numeric>

int main() {

  const std::array<int, 4> race_times = {47, 98, 66, 98};
  const std::array<int, 4> best_distances = {400, 1213, 1011, 1540};

  int ans = 1;

  for (int i = 0; i < race_times.size(); i++) {

    std::list<int> hold_times(race_times[i] + 1);

    std::iota(hold_times.begin(), hold_times.end(), 0);

    std::list<int> distance_traveled(hold_times.size());

    for (auto &time_held : hold_times) {
      int dist = (race_times[i] - time_held) * time_held;
      distance_traveled.push_back(dist);
    }

    ans *= std::count_if(
        distance_traveled.begin(), distance_traveled.end(),
        [&best_distances, i](int val) { return val > best_distances[i]; });
  }

  std::cout << "The answer is: " << ans << std::endl;

  return 0;
}
