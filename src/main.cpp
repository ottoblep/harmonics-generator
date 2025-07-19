#include "plot.hpp"
#include <iostream>
#include <cmath>

int main() {

    // Dissonance Weight Function
    // exp(-0.84q) - exp(-1.38q) with q = (g-f) / 0.021f + 19
    // g and f are two frequencies in Hz
    auto dissonance_weight = [](double q) -> double {
        // double q = (g - f) / ((0.021 * f) + 19.0);
        return std::exp(-0.84 * q) - std::exp(-1.38 * q);
    };

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

    // Draw axes
    for (int y = 0; y < height; ++y) {
        std::cout << move_to({1, y + 1});
        if (y == height / 2) {
            std::cout << foreground(plot::ansi::Color::Gray);
            for (int x = 0; x < width; ++x) std::cout << "-";
        } else {
            std::cout << foreground(plot::ansi::Color::Gray) << "|";
        }
    }

    // Plot sine wave
    std::cout << foreground(plot::ansi::Color::Cyan);
    for (int x = 0; x < width; ++x) {
        double value = height * dissonance_weight(20 * (double) x / width);
        int y = static_cast<int>((height / 2) - value * (height / 2 - 2));
        std::cout << move_to({x + 1, y + 1}) << "*";
    }

    // Reset attributes
    std::cout << reset;
    std::cout << move_to({1, height + 2});
    return 0;
}
