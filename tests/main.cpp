#include "rand.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Test 1: random double between 0 and 1
  {
    const auto value = rnd::rand();
    assert(value >= 0.0 && value <= 1.0);
  }

  // Test 2: random int between 1 and 5
  {
    const int max = 5;
    const auto value = rnd::unifrnd(1, max);
    assert(value >= 1 && value <= max);
  }

  // Test 3: random float between 0.1 and 0.5
  {
    const auto min = 0.1F;
    const auto max = 0.5F;
    const auto value = rnd::unifrnd<float>(min, max);
    assert(value >= min && value <= max);
  }

  // Test 4: select_randomly must return a valid iterator
  {
    const std::vector<std::string> strings_vector{"Hello!", "Hi!",
                                                  "How are you?", "Good bye!"};

    const auto iter =
        rnd::select_randomly(strings_vector.begin(), strings_vector.end());
    assert(iter != strings_vector.end());
  }

  // Optional: smoke test prints
  std::cout << "All RandomHelper tests passed successfully.\n";

  return 0;
}
