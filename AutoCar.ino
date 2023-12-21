#include <MsTimer2.h>
#include "Motor.h"
#include "Sensor.h"
#include "Device.h"
#include "Drive.h"


void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    device_init();
    RobotArm::claw_grab();
    MsTimer2::set(Motor::period, Drive::patrol);
    // MsTimer2::set(Motor::period, Drive::Forward);
    MsTimer2::start();
    // Serial.begin(9600);
}


void loop()
{
    HeartBeat();
    // DisplayInfo();
    // OLED_display_info();
    sonarServo.write(90);
    Drive::obstacle_avoidace();
    Drive::patrol_end_check();
    delay(Motor::period);
}

bool heartBeatFlag = false;
/// @brief 让开发板的自带LED灯闪烁，证明开发板还活着。
/// @note 如子果程序未能退出或者硬件出现故障，loop不能正常循环，则灯会停止闪烁。
void HeartBeat() {
    if ( heartBeatFlag ) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
    heartBeatFlag = !heartBeatFlag;
}

/// @brief 串口打印一些信息
// void DisplayInfo() {
//     //*/ 显示光电传感器的结果
//     for ( int i=0; i<4; i++ ) {
//         if ( IR_Group[i]->get_IR_status() ) {
//             Serial.print("+");
//         } else {
//             Serial.print("-");
//         }
//     }
//     Serial.println();
//     // 显示超声波获取的距离
//     Serial.println(sonar.get_distance());
// }