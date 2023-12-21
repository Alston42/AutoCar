#ifndef MOTOR_H_
#define MOTOR_H_
#include <Arduino.h>

/// @brief 底盘电机
class Motor
{
private:
    uint8_t EN, IN1, IN2;
public:
    static const int period = 20;
    Motor(
        // uint8_t EN, 
        uint8_t _IN1, uint8_t _IN2);
    ~Motor() {};

    void stop();
    void rotate();
    void reverse_rotate();
};

#endif // MOTOR_H