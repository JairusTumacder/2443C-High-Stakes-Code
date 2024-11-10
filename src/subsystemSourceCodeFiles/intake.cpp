#include "main.h"

void runIntake()
{
    // runs the intake and conveyor at max speed (127%)
    intake.move(127);
    conveyor.move(127);
}

void outtake()
{
    // reverses the spin directions of the intake and conveyor and runs them at max speed (127%)
    intake.move(-127);
    conveyor.move(-127);
}

void macroIntake(){
    //runs the intake and conveyor at max speed (127%) for 0.3 secs or 300 msecs
    intake.move(127);
    intake.move(127);
    delaySecs(0.3);
}

void stopIntake()
{
    // stops the intake and conveyor
    intake.move(0);
    conveyor.move(0);
}

