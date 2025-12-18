#ifndef RAND_HPP
#define RAND_HPP
#pragma once
#include <chrono>
#include <concepts>
#include <iterator>
#include <random>
#include <ranges>
namespace rnd {
[[nodiscard]] constexpr std::mt19937 &Generator() {
    static std::random_device random_device;
    static unsigned int seed{
        (random_device.entropy() == 0)
            ? static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())
            : random_device()};
    static std::mt19937 generator{seed};
    return generator;
}

template <typename T>
concept NumericType = std::integral<T> || std::floating_point<T>;

template <typename G>
concept RandomGenerator = std::uniform_random_bit_generator<G>;

template <typename I>
concept Iterator = std::forward_iterator<I>;

template <typename R>
concept Range = std::ranges::forward_range<R>;

template <typename R>
concept Borrowed_Range = std::ranges::borrowed_range<R>;

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
template <NumericType T> [[nodiscard]] constexpr T unifrnd(T lower_limit, T upper_limit) {
    return unifrnd<T>(lower_limit, upper_limit, Generator());
}
[[nodiscard]] constexpr double rand() { return unifrnd<double>(0., 1.); }
template <Iterator I, RandomGenerator G>
[[nodiscard]] constexpr I select_randomly(I first, I last, G &generator) {
    if constexpr (std::random_access_iterator<I>) {
        std::uniform_int_distribution<std::iter_difference_t<I>> dis(0, last - first - 1);
        return first + dis(gen);
    } else {
        std::uniform_int_distribution<std::iter_difference_t<I>> dis(0, std::distance(first, last) -
                                                                            1);
        std::advance(first, dis(gen));
        return first;
    }
}
template <Iterator I> [[nodiscard]] constexpr I select_randomly(I first, I last) {
    return select_randomly(start, end, Generator());
}

template <Borrowed_Range R, RandomGenerator G>
[[nodiscard]] constexpr auto select_randomly(R &&r, G &generator) {
    return select_randomly(std::ranges::begin(r), std::ranges::end(r), generator);
}

template <Borrowed_Range R> [[nodiscard]] constexpr auto select_randomly(R &&r) {
    return select_randomly(std::ranges::begin(r), std::ranges::end(r));
}
template <Range R> [[nodiscard]] constexpr auto select_randomly_value(R &&r) {
    auto it = select_randomly(std::ranges::begin(r), std::ranges::end(r));
    return *it;
}

} // namespace rnd
#endif // !RAND_HPP
