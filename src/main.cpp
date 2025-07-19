#include "plot.hpp"
#include <iostream>
#include <cmath>
#include <numeric>

int main() {

    // Dissonance Weight Function
    auto dissonance_weight = [](double q) -> double {
        return std::pow(2, std::exp(1.0) * 4 * q * std::exp(-4.0 * q));
    };

    std::array<double, 1700> x_values;
    std::iota(x_values.begin(), x_values.end(), 0.0);
    std::ranges::for_each(x_values, [](double& x) { x = 0.001 * x; });
    std::ranges::for_each(x_values, [](double& x) { std::cout << x << " "; });
    std::cout << std::endl <<  " ------------- " << std::endl;

    std::array y_values = x_values;
    std::ranges::for_each(y_values, [&](double& d) { d = dissonance_weight(d); });
    std::ranges::for_each(y_values, [](double& x) { std::cout << x << " "; });

    using namespace plot;
    using namespace plot::ansi;

    // Clear screen
    std::cout << clear;

    // Plot parameters
    const int width = 150;
    const int height = 50;
    const double pi = 3.14159265358979323846;

    // Plot sine wave
    std::cout << foreground(plot::ansi::Color::Cyan);
    // Find min/max for scaling
    auto [y_min_it, y_max_it] = std::minmax_element(y_values.begin(), y_values.end());
    double y_min = *y_min_it;
    double y_max = *y_max_it;

    // Plot all points, scaling to fit width and height
    for (size_t i = 0; i < x_values.size(); ++i) {
        // Scale x to plot width
        int x_plot = static_cast<int>(i * (width - 1) / (x_values.size() - 1));
        // Scale y to plot height (invert y axis for terminal)
        double y_scaled = (y_values[i] - y_min) / (y_max - y_min);
        int y_plot = static_cast<int>((height - 1) - y_scaled * (height - 2));
        std::cout << move_to({x_plot + 1, y_plot + 1}) << "*";
    }

    // Reset attributes
    std::cout << reset;
    std::cout << move_to({1, height + 2});
    return 0;
}
