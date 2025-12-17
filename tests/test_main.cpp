#include <Random-Helper.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

TEST_CASE("random double between 0 and 1") {
    const auto value = rnd::rand();
    REQUIRE((value >= 0.0 && value <= 1.0));
}

TEST_CASE("random int between 1 and 5") {
    const int max = 5;
    const auto value = rnd::unifrnd(1, max);
    REQUIRE((value >= 1 && value <= max));
}

TEST_CASE("random float between 0.1 and 0.5") {
    const auto min = 0.1F;
    const auto max = 0.5F;
    const auto value = rnd::unifrnd<float>(min, max);
    REQUIRE((value >= min && value <= max));
}

TEST_CASE("select_randomly must return a valid iterator") {
    const std::vector<std::string> strings_vector{"Hello!", "Hi!", "How are you?", "Good bye!"};

    const auto iter = rnd::select_randomly(strings_vector.begin(), strings_vector.end());
    REQUIRE((iter != strings_vector.end()));
}
