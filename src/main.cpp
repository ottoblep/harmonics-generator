#include "plot.hpp"
#include <iostream>
#include <cmath>
#include <numeric>

int main() {

    // Dissonance Weight Function
    auto dissonance_weight = [](double q) -> double {
        return std::pow(2, std::exp(4.0 * q) - std::exp(-4.0 * q));
    };

    std::array<double, 100> x_values {};
    std::iota(x_values.begin(), x_values.end(), 0.0);
    std::ranges::for_each(x_values.begin(), x_values.end(), [](double& x) { x = 0.1 * x; });

    using namespace plot;
    using namespace plot::ansi;

    // Set terminal title
    std::cout << title("Sine Wave Plot");
    
    // Clear screen
    std::cout << clear;

    // Plot parameters
    const int width = 150;
    const int height = 50;
    const double pi = 3.14159265358979323846;

    // Plot sine wave
    std::cout << foreground(plot::ansi::Color::Cyan);
    for (int x = 0; x < width; ++x) {
        double value = 0.05 * dissonance_weight((double) x / width - 0.2);
        int y = static_cast<int>((height) - value * (height - 2));
        std::cout << move_to({x + 1, y + 1}) << "*";
    }

    // Reset attributes
    std::cout << reset;
    std::cout << move_to({1, height + 2});
    return 0;
}
