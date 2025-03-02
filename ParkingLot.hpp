//
// Created by 27301 on 25-3-1.
//

#ifndef PARKINGLOT_HPP
#define PARKINGLOT_HPP

#include <chrono>
#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <thread>
using namespace std;

template<const char * NAME, const int V>
class ParkingLot {
    enum placeIndex { OUTSIDE, PARK, ASSISTANT, PASSAGE };

    // 练手，实现有容量上限的底层结构
    template<typename T, const int U>
    class LimitedDeque_ : public deque<T> {
        const size_t maxSize = U;

    public:
        void push_back(const T &value) {
            if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
            deque<T>::push_back(value);
        }

        void push_back(T &&value) {
            if (this->size() >= maxSize) throw overflow_error("- [LimitedDeque]: Reached maximum size.");
            deque<T>::push_back(value);
        }
    };

    const int maxSize_ = V; // 最大容量
    const string name_ = NAME; // 停车场名
    double billingRatio_ = 1.0;  // 收费比率

    bool testMode = true;

    stack<string, LimitedDeque_<string, V> > park_; // 停车场
    map<string, chrono::steady_clock::time_point> parkTime;  // 入场时间记录
    stack<string> assistant_; // 离场辅助中转区
    queue<string> passage_; // 等候区

    // 日志打印函数
    void printLog(const string &text, chrono::milliseconds delay = 0ms) const {
        const auto now = std::chrono::system_clock::now();
        const std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        const std::tm local_time = *std::localtime(&now_time_t);

        if (testMode) this_thread::sleep_for(delay);
        cout << "- [" << name_ << "(" << park_.size() << "/" << maxSize_ << "): " << std::put_time(
            &local_time, "%m-%d %H:%M:%S") << "] " << text << endl;
    }

    // 单例限制
    ParkingLot() {
        cout << "- [" << name_ << "]" << " 停车场名称: " << name_ << ", 设计容量:" << maxSize_ << ", 收费比率(元每秒): " <<
                billingRatio_ <<
                endl;
    }

public:
    // 单例模式，并禁止拷贝和赋值
    static ParkingLot &getInstance() {
        static ParkingLot instance;
        return instance;
    }

    ParkingLot(const ParkingLot &) = delete;

    ParkingLot &operator=(const ParkingLot &) = delete;

    ParkingLot(ParkingLot &&) = delete;

    ParkingLot &operator=(ParkingLot &&) = delete;

    // 基本操作
    void in(string carID, placeIndex from = OUTSIDE) {
        try {
            // 尝试停车并计时
            park_.push(carID);
            parkTime[carID] = chrono::steady_clock::now();

            string where;
            if (from == OUTSIDE) where = "外界";
            else if (from == PASSAGE) where = "过道";


            printLog("car#" + carID + " 从" + where + "进入停车场", 200ms);
        } catch (const overflow_error) {
            // 车满了
            printLog("停车场已满, car#" + carID + " 进入过道等候", 200ms);
            passage_.push(carID); // 排进过道
        }
    }

    void out(const string &carID) {
        printLog("在停车场寻找 car#" + carID, 100ms);
        // 遍历停车场找车然后退出去
        bool isFound = false;
        while (!park_.empty()) {
            string currentCar = park_.top();
            if (currentCar == carID) {
                isFound = true;

                // 计费部分
                const chrono::duration<double> elapsedSeconds = chrono::steady_clock::now() - parkTime[carID];
                const double seconds = elapsedSeconds.count();
                const auto price = seconds * billingRatio_;

                printLog("car#" + carID + " 离开停车场，停车时间: " + to_string(seconds) + "秒, 收费: " + std::to_string(price) + "元", 500ms);
                park_.pop();
                break;
            }

            assistant_.push(currentCar);
            park_.pop();
            printLog("car#" + currentCar + " 从停车场暂离至中转区", 50ms);
        }
        // 没找到车是要报错的，这里不能使用 park_.empty() 判断，如果找的是最后一辆会误判
        if (!isFound) printLog("停车场内未找到 car#" + carID, 200ms);

        // 放回原有车辆
        while (!assistant_.empty()) {
            park_.push(assistant_.top());
            printLog("car#" + assistant_.top() + " 从中转区回到停车场", 50ms);
            assistant_.pop();
        }

        // 如果有的话，存入一辆排队车辆
        if (!passage_.empty()) {
            in(passage_.front(), PASSAGE); // 涉及计时，必须用 in
            passage_.pop();
        }
    }

    // getter 与 setter
    [[nodiscard]] double billing_ratio() const {
        return billingRatio_;
    }

    void set_billing_ratio(const double billing_ratio) {
        billingRatio_ = billing_ratio;
        cout << "- [" << name_ << "] 已修改收费比率: " << billing_ratio << endl;
    }

    [[nodiscard]] bool test_mode() const {
        return testMode;
    }

    void set_test_mode(const bool test_mode) {
        testMode = test_mode;
    }

    // 语法糖
    template<const char * NAME_, const int V_>
    friend ParkingLot<NAME_, V_> &operator<<(ParkingLot<NAME_, V_> &park, const string &carID) {
        park.in(carID);
        return park;
    } // 对应 in
    template<const char * NAME_, const int V_>
    friend ParkingLot<NAME_, V_> &operator>>(ParkingLot<NAME_, V_> &park, const string &carID) {
        park.out(carID);
        return park;
    } // 对应 out
};

#endif //PARKINGLOT_HPP
