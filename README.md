# Random-Helper-functions-CPP
Simple functions to generate random numbers

All functions are in the namespacce `rnd`

# Functions

## `double rand()`

generate a random double between 0 and 1 on a uniform distribution

## `T unifrnd(T a,T b)`

generate a uniform random number in the range specified by (a,b) inclusive.
You can provide a random generator as the third argument.

## `Iter select_randomly(Iter start, Iter end)`

select a random iterator from a container (array, vector, list, ...) or user defined ones that implement std::advance() and std::distance()
You can provide a random generator as the third argument.

## `std::mt19937& Generator()`

generates a mt19937 generator from random_device and returns it for other functions to use.
