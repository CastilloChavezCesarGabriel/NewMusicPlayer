#include "Dice.h"
#include <stdexcept>

Dice::Dice() : engine_(std::random_device{}()) {}

int Dice::roll(const int faces) {
    if (faces <= 0) throw std::invalid_argument("Faces have to be more than 0 for rolling");
    std::uniform_int_distribution<> distribution(1, faces);
    return distribution(engine_);
}