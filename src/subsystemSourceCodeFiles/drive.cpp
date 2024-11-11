#include "main.h"

//arcade control scheme 
void arcadeDriveControl(){
    //get left y and right x positions of the left and right joysticks
    int leftY = controller.get_analog(ANALOG_LEFT_Y); 
    int rightX = controller.get_analog(ANALOG_RIGHT_X); 
    //move the robot based on the positons of the left and right joysticks
    chassis.arcade(leftY, rightX);
}

//tank control scheme
void tankDriveControl(){
    //get left x and right x positions of the left and right joysticks
    int leftX = controller.get_analog(ANALOG_LEFT_X);
    int rightX = controller.get_analog(ANALOG_RIGHT_X);
    //move the robot based on the positions of the left and right joysticks
    chassis.tank(leftX, rightX);
}

//intake control scheme
void intakeControl(){
    //get value of r1 on the controller and if true
    if(controller.get_digital(DIGITAL_R1)){
        //intakes a ring
        runIntake();
    }
    //get value of r2 on the controller and if true
    else if(controller.get_digital(DIGITAL_R2)){
        //outtakes a ring
        outtake();
    }
    //get value of up arrow on the controller and if pressed
    else if(controller.get_digital_new_press(DIGITAL_UP)){
        //intakes a ring for a short time
        macroIntake();
    }
    //if r1 and r2 are not being pressed
    else{
        //stops the intake
        stopIntake();
    }
}

bool isMogo = false;

//mogo control scheme
void mogoControl(){
    //get value of l1 on the controller and if pressed
    if(controller.get_digital_new_press(DIGITAL_L1)){
        //sets mogo mech:
        //if isMogo is false, activate -> if isMogo is true, deactivate
        mogo.set_value(!isMogo);
        //if isMogo is false, deactivate on next press -> if isMogo is true, activate on next press
        isMogo = !isMogo;
    }
}

bool isDoinker = false;

//doinker control scheme
void doinkerControl(){
    //get value of x on the controller and if pressed
    if(controller.get_digital_new_press(DIGITAL_X)){
        //sets doinker mech:
        //if isDoinker is false, activate -> if isDoinker is true, deactivate
        doinker.set_value(!isDoinker);
        //if isDoinker is false, deactivate on next press -> if isDoinker is true, activate on next press
        isDoinker = !isDoinker;
    }
}

bool isStaged = false;

//arm control scheme
void armControl(){
    //get value of l2 on the controller and while pressed
    while(controller.get_digital(DIGITAL_L2)){
        //get value of r1 on the controller and if pressed
        if(controller.get_digital_new_press(DIGITAL_R1)){
            //if isStaged is false
            if(!isStaged){
                //runs the arm to its staging position (0 degrees)
                runArm(0);
                //on next press, isStaged is true
                isStaged = true;
            }
            //if isStaged is true
            else{
                //runs the arm to its scoring position (0 degrees)
                runArm(0);
                //on next press, isStaged is false
                isStaged = false;
            }
        }
        //get value of r2 on the controller and if pressed
        else if(controller.get_digital_new_press(DIGITAL_R2)){
            //runs the arm to its starting position (0 degrees)
            runArm(0);
        }
    }
}

//driver control scheme
void driverControl(){
    //combine all of the subsystem's control schemes into the main control scheme for the driver
    arcadeDriveControl();
    intakeControl();
    mogoControl();
    doinkerControl();
    armControl();
}