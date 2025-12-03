#ifndef RAND_HPP
#define RAND_HPP
#pragma once
#include <chrono>
#include <concepts>
#include <iterator>
#include <random>
namespace rnd {
[[nodiscard]] constexpr std::mt19937 &Generator() {
  static std::random_device random_device;
  static unsigned int seed{
      (random_device.entropy() == 0)
          ? static_cast<unsigned int>(
                std::chrono::system_clock::now().time_since_epoch().count())
          : random_device()};
  static std::mt19937 generator{seed};
  return generator;
}

template <typename T>
concept NumericType = std::integral<T> || std::floating_point<T>;

template <typename G>
concept RandomGenerator = std::uniform_random_bit_generator<G>;

template <typename I>
concept Iterator = std::input_iterator<I>;

template <NumericType T, RandomGenerator G>
[[nodiscard]] constexpr T unifrnd(T lower_limit, T upper_limit, G &generator) {
  if constexpr (std::is_integral_v<T>) {
    std::uniform_int_distribution<T> dis(lower_limit, upper_limit);
    return dis(generator);
  } else {
    std::uniform_real_distribution<T> dis(lower_limit, upper_limit);
    return dis(generator);
  }
}
template <NumericType T>
[[nodiscard]] constexpr T unifrnd(T lower_limit, T upper_limit) {
  return unifrnd<T>(lower_limit, upper_limit, Generator());
}
[[nodiscard]] constexpr double rand() { return unifrnd<double>(0., 1.); }
template <Iterator I, RandomGenerator G>
[[nodiscard]] constexpr I select_randomly(I start, I end, G &generator) {
  std::uniform_int_distribution<long long int> dis(
      0, std::distance(start, end) - 1);
  std::advance(start, dis(generator));
  return start;
}
template <Iterator I>
[[nodiscard]] constexpr I select_randomly(I start, I end) {
  return select_randomly(start, end, Generator());
}
} // namespace rnd
#endif // !RAND_HPP
