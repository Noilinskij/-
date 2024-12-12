#include "lab5_ex6_vector.cpp"
#include <algorithm>

int main() {
    vector a = {5, 4, 3};
    vector f = {1, 2, 3};

    std::sort(a.begin(), a.end());
    for (auto val : a) {
        std::cout << val << " ";
    }

}