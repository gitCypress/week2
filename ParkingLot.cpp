//
// Created by 27301 on 25-3-1.
//

#include "ParkingLot.hpp"

#include <stdexcept>

template<const char* NAME, const int V>
template <typename T, const int U>
void ParkingLot<NAME, V>::LimitedDeque_<T, U>::push_back(const T& value) {
    if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
    deque<T>::push_back(value);
}

template<const char* NAME, const int V>
template<typename T, const int U>
void ParkingLot<NAME, V>::LimitedDeque_<T, U>::push_back(T &&value) {
    if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
    deque<T>::push_back(value);
}

template<const char* NAME, const int V>
ParkingLot<NAME, V> & ParkingLot<NAME, V>::getInstance() {
    static ParkingLot<NAME, V> instance;
    return instance;
}

template<const char *NAME, const int V>
void ParkingLot<NAME, V>::in(string carID) {
    // TODO: 实现函数
}

template<const char *NAME, const int V>
void ParkingLot<NAME, V>::out(string carID) {
    // TODO: 实现函数
}

template<const char* NAME, const int V>
ParkingLot<NAME, V> & ParkingLot<NAME, V>::operator<<(ParkingLot &park, const string &carID) {
    in(carID);
    return park;
}

template<const char* NAME, const int V>
ParkingLot<NAME, V> & ParkingLot<NAME, V>::operator>>(ParkingLot &park, const string &carID) {
    out(carID);
    return park;
}



