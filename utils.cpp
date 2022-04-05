#include <random>

double rand_double() {
    return (double)std::rand() / RAND_MAX;
}