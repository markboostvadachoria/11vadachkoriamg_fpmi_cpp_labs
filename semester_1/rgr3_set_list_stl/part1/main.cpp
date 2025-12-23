#include <iostream>
#include <set>
#include <cmath>


void eratosthenes_sieve(int N) {
    std::set<int> numbers;
    
    for (int i = 2; i <= N; i++) {
        numbers.insert(i);
    }
    
    for (int p = 2; p <= std::sqrt(N); p++) {
        if (numbers.find(p) != numbers.end()) {
            for (int multiple = p * p; multiple <= N; multiple += p) {
                numbers.erase(multiple);
            }
        }
    }
    
    for (int prime : numbers) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;
}

int main() {
    try {
        int N;
        std::cout << "Enter number N: ";
        std::cin >> N;
        
        if (!std::cin) {
            throw "Error: bad input. Enter number please.";
        }
        
        if (N < 0) {
            throw "Error: negative number. Enter positive number.";
        }
        
        if (N > 1000000) {
            throw "Error: number too big. Maximum is 1000000.";
        }
        
        eratosthenes_sieve(N);
        
    } catch (const char* error_msg) {
        std::cout << error_msg << std::endl;
    }
    
    return 0;
}