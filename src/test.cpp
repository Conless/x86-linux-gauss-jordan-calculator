#include "../include/fraction.h"

int main() {
    Fraction a[100];
    for (int i = 1; i <= 50; i++) {
        std::cin >> a[i];
        a[i] = a[i] + a[i - 1];
        std::cout << a[i] << std::endl;
    } 
}