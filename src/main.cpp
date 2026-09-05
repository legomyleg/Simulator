#include <iostream>
#include <string>
#include <thrust.hpp>
using std::cout;

int main() {
    cout << "Starting...\n";
    ThrustCurve curve;
    std::string path = std::string(ROOT_DIR) + "/resources/AeroTech_O5500X-PS.txt";
    curve.load(path);
    cout << "Curve loaded.\n";
    for (auto point : curve.points) {
        cout << point.t << " -> " << point.N << "\n";
    }

    return 0;
}
