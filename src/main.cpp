#include <iostream>
#include "rand.hpp"
#include <vector>
int main() {
  double x{rnd::rand()}; //uniform random double between 0-1
  int y{rnd::unifrnd(1,5)}; //uniform random int between 1-5
  float z{rnd::unifrnd<float>(0.1,0.5)}; //uniform random float between 0.1-0.5
  std::vector<std::string> v{"Hello!","Hi!","How are you?","Good bye!"};
  std::string s{*rnd::select_randomly(v.begin(),v.end())}; // select a random entry from the vector
  std::cout << "x=" << x << '\n';
  std::cout << "y=" << y << '\n';
  std::cout << "z=" << z << '\n';
  std::cout << "s=" << s << '\n';
  return 0;
}
