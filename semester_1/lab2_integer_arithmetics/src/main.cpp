#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>


struct Triple {
    double x{-1};
    double y{-1};
    double z{-1};
};

bool isPerfectSquare(int n) {
    if (n < 0) return false;
    int root = static_cast<int>(std::sqrt(n));
    return root * root == n;
}


std::vector<Triple> findPythagoreanTriples(int n) {
    if (n < 0) {
        throw std::invalid_argument("n is int >0");
    }

    std::vector<Triple> triples;
    
    for (int z = 1; z <= n; z++) 
        for (int x = 1; x < z; x++) {
            int y_square = z * z - x * x;
            if (isPerfectSquare(y_square)) {
                double y = std::sqrt(y_square);                
                if (x <= y) {
                    Triple triple;
                    triple.x = static_cast<double>(x);
                    triple.y = y;
                    triple.z = static_cast<double>(z);
                    triples.push_back(triple);
                }
            }
        }
    
    return triples;
}
