#include <iostream>
#include <vector>
#include "ParkingLot.hpp"
using namespace std;

constexpr char sduPark1[] = "SDUPark#01";  // 停车场的名字

int main() {

    auto& park = ParkingLot<sduPark1, 10>::getInstance();

    vector<string> cars;
    for (int i = 100001; i <= 100010; i++) {
        cars.push_back(to_string(i));
    }

    for (const auto& i : cars) {
        park.in(i);
    }

}