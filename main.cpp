#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "CityMap.hpp"

void printResult(const std::string& algorithm,
                 const std::pair<std::vector<std::string>, int>& result);

int main() {
    CityMap city;

    std::cout << "=== George's City Navigation System ===\n\n";

    city.printCity();
    std::cout << "\n";

    std::cout << "--- Route: Downtown -> Airport ---\n\n";

    printResult("Greedy", city.greedyPath(0, 2));

    /* Test all three algorithms on this route */

    std::cout << "\n";

    std::cout << "--- Route: Downtown -> Suburb South ---\n\n";

    printResult("Greedy", city.greedyPath(0, 7));

    /* Test all three algorithms on this route */

    std::cout << "\n";

    std::cout << "--- Route: Downtown -> Downtown ---\n\n";

    printResult("Greedy", city.greedyPath(0, 0));

    /* Pick your own start/end pair and test all three algorithms */

    return 0;
}

void printResult(const std::string& algorithm,
                 const std::pair<std::vector<std::string>, int>& result) {
    std::cout << "[" << algorithm << "]\n";
    if (result.first.empty() || result.second == -1) {
        std::cout << "  No path found.\n";
        return;
    }
    std::cout << "  Path: ";
    for (int i = 0; i < (int)result.first.size(); i++) {
        std::cout << result.first[i];
        if (i < (int)result.first.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n  Total time: " << result.second << " min\n";
}
