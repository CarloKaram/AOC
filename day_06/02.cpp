#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>

int main() {

  long race_time = 47986698;
  long best_distance = 400121310111540;

  long ans = 1;

  std::list<long> hold_times(race_time + 1);

  std::iota(hold_times.begin(), hold_times.end(), 0);

  std::list<long> distance_traveled(hold_times.size());

  for (auto &time_held : hold_times) {
    long dist = (race_time - time_held) * time_held;
    distance_traveled.push_back(dist);
  }

  ans *=
      std::count_if(distance_traveled.begin(), distance_traveled.end(),
                    [&best_distance](long val) { return val > best_distance; });

  std::cout << "The answer is: " << ans << std::endl;

  return 0;
}
