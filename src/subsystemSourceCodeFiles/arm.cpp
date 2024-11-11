#include "main.h"

double error = 0;
double prevError = 0;
double integral = 0;
double derivative = 0;

const double threshold = 0;

const double kP = 0; // proportional gain (kP)
const double kI = 0; // integral gain (kI)
const double kD = 0; // derivative gain (kD)

int time = 0; // time (seconds) for the PID to delay for then update to save resources

double armPID(double desiredPos, double time){
    while(true){
    //save previous error for derivative term
    prevError = error;

    //calculate new error by finding the difference between the desired rotation sensor position and the current rotation sensor position
    error = desiredPos - rotation.get_position(); 

    //sum errors into integral term if the error is below threshold
    if(error < threshold){
        integral += error;
    }
    //if error is not below threshold
    else{
        //reset integral term to prevent it from growing too large
        integral = 0;
    }

    //calculate derivative term by finding the difference between the current error and the previous error
    derivative = error - prevError;

    //delay for time seconds (converted to milliseconds) then update to save resources
    delaySecs(time);
    
    //return value of the combined parts of the PID function into the PID algorithm
    return error * kP + integral * kI + derivative * kD;
    }
}

void runArm(double desiredPos){
    //run the arm to a desired rotation sensor position using the PID algorithm
    arm.move(armPID(desiredPos));
}