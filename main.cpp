#include <iostream>

#include "KDTree.h"

int main() {
    std::vector<std::vector<double>> coords = {
            {7, 2}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {2, 3}
    };
    std::vector<char> data = {'A', 'B', 'C', 'D', 'E', 'F'};

    KDTree<char> tree;

    tree.add_nodes(coords, data);

    return 0;
}
