#include "pid.hpp";

PIDController::PIDController(double p, double i, double d) {
    kP = p;
    kI = i;
    kD = d;
}
double PIDController::calculateError(double curPosition, double goal) {
    double error = goal - curPosition;
    Proportional = error;
    Integral += error;
    double maxIntegral = 1.0;
    Integral = std::clamp(Integral, -maxIntegral, maxIntegral);
    Derivative = error - prevError;
    prevError = error;
    double pid = Proportional * kP + Integral * kI + Derivative * kD;
    if (error == 0 || curPosition > goal) {
        Integral = 0;
    }

    if (error <= exitError) {
        timer += 10;
        if (timer >= exitTime) {
            stop = true;
        }
    } else {
        timer = 0;
        stop = false;
    }
    if (maxTimeTimer >= maxTime) {
        stop = true;
    }
    maxTimeTimer += 10;
    return std::clamp(pid, -1.0, 1.0);
}
// set exit conditions: distance from target, true (inches) / false (degrees), time before stop (ms), max time for action(ms)
void PIDController::setExitCondition(double err, bool isInches, int time, int maxTime) {
    if (isInches) {
        exitError = inchesToDegrees(err);
    } else {
        exitError = err;
    }
    exitTime = time;
    maxTime = maxTime;
}