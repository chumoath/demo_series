#include "math_utils.hpp"
#include <cmath>

MathUtils::MathUtils(double value) : startValue_(value) {}

double MathUtils::getValue() const {
    return startValue_;
}

double MathUtils::distance(double x1, double y1, double x2, double y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double MathUtils::add(double x) {
    startValue_ += x;
    return startValue_;
}