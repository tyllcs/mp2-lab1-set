#include <iostream>
#include "trafficLight.h"


int main() {
    Crossroad r;
    std::cout << "Init: \n";
    std::cout << r;

    for (int i = 0; i < 4; i++) {
        r.switchLight();
        std::cout << "After switch " << i + 1 << ":" << std::endl;
        std::cout << r;
    }
}