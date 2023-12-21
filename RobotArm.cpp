#include "RobotArm.h"
#define LIFT_DOWN 80
#define LIFT_UP 0
#define CLAW_FREE 90
#define CLAW_HOLD 178
#define PUSH_FORWARD 170
#define PUSH_BACKWARD 50
#define BASE_LEFT 60
#define BASE_RIGHT 120

#define BASE_MIN 0
#define BASE_MAX 180
#define LIFT_MIN 30
#define LIFT_MAX 120
#define PUSH_MIN 40
#define PUSH_MAX 180
#define CLAW_MIN 90  // 张开
#define CLAW_MAX 178 // 闭合

#define BASE_RESET 90
#define LIFT_RESET 120
#define PUSH_RESET 40
#define CLAW_RESET 178

namespace RobotArm
{
    void claw_grab()
    {
        claw.write(CLAW_FREE);
        delay(900);
        base.write(BASE_RIGHT);
        delay(900);
        push.write(PUSH_FORWARD);
        delay(900);
        lift.write(LIFT_DOWN);
        delay(900);
        claw.write(CLAW_HOLD);
        delay(700);
        claw_reset();
    }

    void claw_free()
    {
        base.write(BASE_RIGHT);
        delay(900);
        push.write(PUSH_FORWARD);
        delay(900);
        lift.write(LIFT_DOWN);
        delay(900);
        claw.write(CLAW_FREE);
        delay(900);
        claw_reset();
    }

    void claw_reset()
    {
        push.write(PUSH_RESET);
        delay(900);
        base.write(BASE_RESET);
        delay(900);
        lift.write(LIFT_RESET);
        delay(900);
        claw.write(CLAW_RESET);
        delay(1000);
    }
}