#include "Device.h"
#include "Drive.h"

#define MOTOR_LF_IN1 A0
#define MOTOR_LF_IN2 A1
#define MOTOR_RF_IN1 A2
#define MOTOR_RF_IN2 A3
#define MOTOR_LB_IN1 2
#define MOTOR_LB_IN2 3
#define MOTOR_RB_IN1 0
#define MOTOR_RB_IN2 1
Motor motor_LF(MOTOR_LF_IN1, MOTOR_LF_IN2);
Motor motor_RF(MOTOR_RF_IN1, MOTOR_RF_IN2);
Motor motor_LB(MOTOR_LB_IN1, MOTOR_LB_IN2);
Motor motor_RB(MOTOR_RB_IN1, MOTOR_RB_IN2);

#define L2_IR_PIN 11
#define L1_IR_PIN 10
#define R1_IR_PIN 9
#define R2_IR_PIN 8
IR L2_IR(L2_IR_PIN);
IR L1_IR(L1_IR_PIN);
IR R1_IR(R1_IR_PIN);
IR R2_IR(R2_IR_PIN);
IR *IR_Group[4] = {&L2_IR, &L1_IR, &R1_IR, &R2_IR};

#define SONAR_TRIG_PIN A4
#define SONAR_ECHO_PIN A5
UltraSonic sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);

#define SERVO_LIFT_PIN 7
#define SERVO_CLAW_PIN 6
#define SERVO_BASE_PIN 5
#define SERVO_PUSH_PIN 4
Servo lift;
Servo claw; //夹爪
Servo base;
Servo push;

#define SERVO_SONAR_PIN 12
Servo sonarServo;

// Adafruit_SSD1306 OLED(128,64);
void set_OLED(Adafruit_SSD1306 *oled)
{
    oled->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled->setTextColor(WHITE);
    oled->setTextSize(1);
    oled->cp437(true);
    oled->clearDisplay();
    oled->display();
}
/// @brief OLED屏幕显示一些信息
void OLED_display_info()
{
    OLED.clearDisplay();
    OLED.setCursor(0, 0);
    //*/ 显示电机的速度和PWM输出
    OLED.println();
    OLED.print("\nLeft speed:  ");
    OLED.display();
    /*/ 显示光电传感器的结果以及底盘参考速度
    for ( int i=0; i<7; i++ ) {
        if ( IRGroup[i].get_IR_status() ) {
            OLED.print("+");
        } else {
            OLED.print("-");
        }
    }
    OLED.println();
    OLED.print("\nVc: ");
    OLED.println(Drive::Vc);
    OLED.print("Wc: ");
    OLED.println(Drive::Wc);
    OLED.print("wL: ");
    OLED.println(Drive::wL);
    OLED.print("wR: ");
    OLED.println(Drive::wR);
    OLED.display();
    //*/
}

void device_init()
{
    // set_OLED(&OLED);
    // OLED.clearDisplay();
    // OLED.setCursor(0, 0);
    // OLED.println("Car initializing...");
    // OLED.display();
    motor_LF.stop();
    motor_RF.stop();
    motor_LB.stop();
    motor_RB.stop();
    sonar.init();
    lift.attach(SERVO_LIFT_PIN);
    claw.attach(SERVO_CLAW_PIN);
    base.attach(SERVO_BASE_PIN);
    push.attach(SERVO_PUSH_PIN);
    sonarServo.attach(SERVO_SONAR_PIN);
    sonarServo.write(90);
    RobotArm::claw_reset();
    // OLED.println("Initialize success!");
    // OLED.display();
} 