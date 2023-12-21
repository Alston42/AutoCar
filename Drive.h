#ifndef DRIVE_H_
#define DRIVE_H_
#include "Device.h"
#include "RobotArm.h"

namespace Drive
{
    extern double Vc, Wc, wL, wR;

    /// @brief 泊车模式，车会自己定住
    void Park();
    /// @brief 转弯
    void RightTurn();
    void LeftTurn();
    /// @brief 平移
    void RightMove();
    void LeftMove();
    /// @brief 前进
    void Forward();
    /// @brief 后退
    void Backward();
    /// @brief 自动巡线
    void patrol();
    /// @brief 超声波避障
    void obstacle_avoidace();
    /// @brief 到达巡线终点时执行的程序
    void patrol_end_check();

    /// @brief 让一个任务重复运行固定的时间
    /// @param task 要执行的任务
    /// @param runTime 运行时间（ms）
    void run_task_for(void (*task)(), long runTime);
}

#endif // DRIVE_H