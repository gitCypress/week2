//
// Created by 27301 on 25-3-1.
//

#include "ParkingLot.hpp"

#include <stdexcept>

template<const int V>
template <typename T, const int U>
void ParkingLot<V>::LimitedDeque_<T, U>::push_back(const T& value) {
    if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
    deque<T>::push_back(value);
}

template<const int V>
template<typename T, const int U>
void ParkingLot<V>::LimitedDeque_<T, U>::push_back(T &&value) {
    if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
    deque<T>::push_back(value);
}

template<const int V>
ParkingLot<V> & ParkingLot<V>::getInstance() {
    static ParkingLot<V> instance;
    return instance;
}

template<const int V>
ParkingLot<V> & ParkingLot<V>::operator<<(ParkingLot &park, const string &carID) {
    in(carID);
    return park;
}

template<const int V>
ParkingLot<V> & ParkingLot<V>::operator>>(ParkingLot &park, const string &carID) {
    out(carID);
    return park;
}



