//
// Created by 27301 on 25-3-1.
//

#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP

#include <stack>
#include <queue>
#include <string>
using namespace std;

template <const int V>
class ParkingLot {

    template <typename T, const int U>
    class LimitedDeque_ : public deque<T> {
        size_t maxSize = U;
    public:
        void push_back(const T& value);
        void push_back(T&& value);
    };

    stack<string, LimitedDeque_<string, V>> park;  // 停车场
    stack<string> assistant;  // 离场辅助
    queue<string> passage; // 便道

    // 单例限制
    ParkingLot() = default;

public:
    // 单例模式，并禁止拷贝和赋值
    static ParkingLot& getInstance();
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;
    ParkingLot(ParkingLot&&) = delete;
    ParkingLot& operator=(ParkingLot&&) = delete;

    // 基本操作
    void in(string carID);
    void out(string carID);

    // 语法糖
    ParkingLot& operator<<(ParkingLot& park, const string &carID);  // 对应 in
    ParkingLot& operator>>(ParkingLot& park, const string &carID);  // 对应 out
};



#endif //PARKINGLOT_HPP
