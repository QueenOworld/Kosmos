#include <iostream>
#include "./types/CosmicObject.h"
#include <vector>

int main() {
    CosmicObject a = CosmicObject{8};
    std::cout << a.Hash;
}