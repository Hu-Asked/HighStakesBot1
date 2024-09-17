#include "api.h"
#include "main.h"

#ifndef PID_H
#define PID_H

class PIDController {
    public:
        PIDController(double p, double i, double d);
        double calculateError(double curPosition, double goal);
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
};
#endif // PID_H