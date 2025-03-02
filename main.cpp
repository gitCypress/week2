#include "ParkingLot.hpp"
using namespace std;

constexpr char SDU_PARK_1[] = "SDUPark#01";  // 停车场的名字

int main() {

    // 停车场单例获取，使用模板参数可以获得其他类型的停车场
    auto& park = ParkingLot<SDU_PARK_1, 4>::getInstance();
    park.set_billing_ratio(0.01);

    // 以下测试存在手动延迟模拟停车场场景，如果不需要延迟，使用下行：
    // park.set_test_mode(false);

    // 测试无车行为
    park << "100001" ;
    park >> "1";

    // 停车场入场
    for (int i = 100002; i < 100008; i++) {
        park.in(to_string(i));
    }

    // 出场测试
    park >> "100001" >> "100002" >> "100003" >> "100004";
}