#include "Motor.h"

const double Pi = acos(-1);

/// @brief 实例化一个电机对象
/// @param EN PWM输出端口
/// @param IN1 正反转控制引脚
/// @param IN2 正反转控制引脚
Motor::Motor(
    // uint8_t EN, 
    uint8_t _IN1, uint8_t _IN2)
    : IN1(_IN1), IN2(_IN2)
{
    // pinMode(EN, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN1, OUTPUT);
}

void Motor::stop()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}

void Motor::rotate()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void Motor::reverse_rotate()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}