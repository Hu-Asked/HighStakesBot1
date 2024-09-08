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
	double pid = Proportional*kP + Integral*kI + Derivative*kD;
	if (error == 0 || curPosition > goal) {
		Integral = 0;
	}
	if(fabs(Derivative) < 0.2) {
		timer += 10;
		if(timer >= 200) {
			stop = true;
		}
	} else {
		timer = 0;
		stop = false;
	}
	return std::clamp(pid, -1.0, 1.0);
}