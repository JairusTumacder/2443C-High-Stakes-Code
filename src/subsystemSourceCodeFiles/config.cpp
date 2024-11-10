#include "main.h"

#define lFPort -1 
#define lMPort -2
#define lBPort -3
#define rFPort 4
#define rMPort 5
#define rBPort 6
#define inertialPort 7
#define mogoPort 'A'
#define doinkerPort 'B'
#define intakePort 8
#define conveyorPort -9
#define rotationPort 10
#define armPort 11

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//left motor group
pros::MotorGroup lGrp({lFPort, lMPort, lBPort}, pros::MotorGearset::blue, pros::MotorEncoderUnits::counts);

//right motor group
pros::MotorGroup rGrp({rFPort, rMPort, rBPort}, pros::MotorGearset::blue, pros::MotorEncoderUnits::counts);

//drivetrain (6 11W motors)
lemlib::Drivetrain drivetrain(&lGrp, &rGrp, 16, lemlib::Omniwheel::NEW_325, 360, 2);

//inertial sensor
pros::Imu inertial(inertialPort);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr as we are using IMEs (acceptable)
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs (acceptable)
                            nullptr, // horizontal tracking wheel 1, set to nullptr as we are using an Omniwheel-only drivetrain (not recommended)
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we are using an Omniwheel-only drivetrain (not recommended)
                            &inertial
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

//creates the chassis
lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);

//mogo mech (pneumatics)
pros::ADIDigitalOut mogo(mogoPort);

//doinker mech (pneumatics)
pros::ADIDigitalOut doinker(doinkerPort);

//intake (5.5W motor)
pros::Motor intake(intakePort);

//conveyor (11W motor)
pros::Motor conveyor(conveyorPort, pros::MotorGearset::blue, pros::MotorEncoderUnits::counts);

//rotation sensor
pros::Rotation rotation(rotationPort);

//arm (5.5W motor)
pros::Motor arm(armPort);