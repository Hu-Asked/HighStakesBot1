#include "main.h"

ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-1,-2,-3}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{4,5,6}

  // IMU Port
  ,14

  ,3.25

  // Cartridge RPM
  ,600

  ,0.75
);


// Odometry odometry;
pros::Motor intake1(9, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2(10, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_DEGREES);

// pros::ADIDigitalOut piston1('A');
// pros::ADIDigitalOut piston2('B');
// pros::ADIDigitalOut piston3('C');
// pros::ADIDigitalOut piston4('D');

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  pros::delay(500);
  chassis.opcontrol_curve_buttons_toggle(true); 
  chassis.opcontrol_drive_activebrake_set(2); 
  chassis.opcontrol_curve_default_set(5, 5); 
  default_constants();
  ez::as::auton_selector.autons_add({
    Auton("Red Left", RedLeft),
    Auton("Red Right", RedRight),
    Auton("Blue Left", BlueLeft),
    Auton("Blue Right", BlueRight),
    Auton("Skills", AutonomousSkills),
    Auton("Drive Example\n\nRobot drives forward 20 inches.", drive_example),
    Auton("Turn Example\n\nRobot turns 90 degrees.", turn_example),
    Auton("Swing Example\n\nRobot swings 90 degrees.", swing_example),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  chassis.initialize();
  chassis.pid_tuner_increment_p_set(0.1);
  chassis.pid_tuner_increment_i_set(0.1);
  chassis.pid_tuner_increment_d_set(0.1);
  chassis.pid_tuner_increment_start_i_set(0.1);
  ez::as::initialize();
  master.rumble(".");
}

void disabled() {}

void competition_initialize() {}


void autonomous() {
  ez::as::auton_selector.selected_auton_call();
}

void opcontrol() {
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  
  while (true) {
    if (!pros::competition::is_connected()) {
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_UP)) 
        chassis.pid_tuner_toggle();
        
      if (master.get_digital_new_press(DIGITAL_RIGHT)) 
        autonomous();
        pros::lcd::set_text(2, to_string(chassis.imu.get_heading()));
      
      chassis.pid_tuner_iterate();
    }
    chassis.opcontrol_arcade_standard(ez::SPLIT);
    
    if(master.get_digital(DIGITAL_L1)) {
      activateIntake(115);
    } else if(master.get_digital(DIGITAL_L2)) {
      activateIntake(-115);
    } else {
      activateIntake(0);
    }

    // if(master.get_digital(DIGITAL_B)) toggleClamp();
    // if(master.get_digital(DIGITAL_A)) toggleLift();
    // if(master.get_digital(DIGITAL_Y)) toggleIntakeCount();
    
    pros::delay(ez::util::DELAY_TIME);
  }
}
