#include "api.h"
#include "main.h"

#ifndef PID_H
#define PID_H

class PIDController {
   public:
    PIDController(double p, double i, double d);
    double calculateError(double curPosition, double goal);
    void setExitCondition(double err, bool isInches, int time, int maxTime);
    bool stop = false;
    double kP;
    double kI;
    double kD;
    double goal;
    double Proportional;
    double Integral;
    double Derivative;
    double prevError;
    double timer = 0;
    int maxTime = 5000;  // time in ms; when robot has been in this action for long enough, break;
    double exitError = 0;
    int exitTime = 0;
    int maxTimeTimer = 0;
};
#endif  // PID_H