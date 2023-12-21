#include "Drive.h"
#include <MsTimer2.h>

namespace Drive
{
    double Vc = 40; //直线速度 (cm/s)
    double Wc = 0; //转弯速度 (rad/s)

/*******************一些简单动作函数*******************/
    void RightTurn() {
        motor_LF.reverse_rotate();
        motor_RF.rotate();
        motor_LB.reverse_rotate();
        motor_RB.rotate();
    }
    void LeftTurn() {
        motor_LF.rotate();
        motor_RF.reverse_rotate();
        motor_LB.rotate();
        motor_RB.reverse_rotate();
    }
    void LeftMove() {
        motor_LF.rotate();
        motor_RF.reverse_rotate();
        motor_LB.reverse_rotate();
        motor_RB.rotate();
    }
    void RightMove() {
        motor_LF.reverse_rotate();
        motor_RF.rotate();
        motor_LB.rotate();
        motor_RB.reverse_rotate();
    }
    void Forward() {
        motor_LF.rotate();
        motor_RF.rotate();
        motor_LB.rotate();
        motor_RB.rotate();
    }
    void Backward() {
        motor_LF.reverse_rotate();
        motor_RF.reverse_rotate();
        motor_LB.reverse_rotate();
        motor_RB.reverse_rotate();
    }
    void Park() {
        motor_LF.stop();
        motor_RF.stop();
        motor_LB.stop();
        motor_RB.stop();
    }


/**********************执行任务**********************/
    void patrol() {
        //*/
        if (!L1_IR.get_IR_status() && !R1_IR.get_IR_status()) {
            Forward();
        } else {
            if (!L2_IR.get_IR_status()) {
                LeftTurn();
            } else if (!R2_IR.get_IR_status()) {
                RightTurn();
            }
        }
        //*/
    }

    void run_task_for(void (*task)(), long runTime) {
        MsTimer2::stop();
        MsTimer2::set(Motor::period, task);
        MsTimer2::start();
        delay(runTime);
        MsTimer2::stop();
    }

    void patrol_end_check() {
        if ( L1_IR.get_IR_status() && R1_IR.get_IR_status() 
            && L2_IR.get_IR_status() && R2_IR.get_IR_status() )
        {
            run_task_for(Park, 300);
            //原地旋转180度
            run_task_for(LeftTurn, 350);
            run_task_for(RightTurn, 350);
            MsTimer2::set(Motor::period, Park);
            MsTimer2::start();
            RobotArm::claw_reset();
            while (1) {
                delay(10);
            }
        }
    }

    void obstacle_avoidace() {
        if (sonar.get_distance() < 20) {
            run_task_for(Park, 1000);
            sonarServo.write(0);
            delay(100);
            sonarServo.write(90);
            delay(100);
            double right_dis = sonar.get_distance();            
            sonarServo.write(180);
            delay(200);
            sonarServo.write(90);
            delay(100);
            double left_dis = sonar.get_distance();
            sonarServo.write(0);
            delay(100);
            sonarServo.write(90);
            delay(100);
              if (left_dis > right_dis) {
                  run_task_for(LeftTurn, 1300);
              } else {
                  run_task_for(RightTurn, 1300);
              }
            MsTimer2::set(Motor::period, patrol);
            // MsTimer2::set(Motor::period, Forward);
            MsTimer2::start();
        }
    }
}