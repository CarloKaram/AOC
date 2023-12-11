#include <cmath>
#include <iostream>

int main() {

  long race_time = 47986698;
  long best_distance = 400121310111540;

  long ans = 1;
  long x1, x2;

  // Equation is of the form, held_time^2 - race_time*held_time - best_distance
  // < 0
  long discriminant = race_time * race_time - 4 * 1 * best_distance;

  if (discriminant > 0) {
    x1 = (-1 * race_time + sqrt(discriminant)) / (2 * 1);
    x2 = (-1 * race_time - sqrt(discriminant)) / (2 * 1);
  }

  ans = std::abs(x1 - x2);

  std::cout << "The answer is: " << ans << std::endl;

  return 0;
}
