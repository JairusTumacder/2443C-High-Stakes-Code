#include "main.h"

double secToMsec(double seconds)
{
    //converts from seconds to milliseconds
    return seconds * 1000;
}

void delaySecs(double seconds)
{
    //delay for x seconds (converted to milliseconds) then update to save resources
    pros::delay(seconds * 1000);
}

//pure pursuit paths for auton skills routine
ASSET(_asset_static_start_2443CsPath1_txt);
ASSET(_asset_static_start_2443CsPath2_txt);
ASSET(_asset_static_start_2443CsPath3_txt);

// auton skills routine
void skills()
{
    // score ring on alliance stake
    macroIntake();
    chassis.follow(_asset_static_start_2443CsPath1_txt, 5, secToMsec(3.25), false);
    // grab mobile goal
    mogo.set_value(true);
    runIntake();
    chassis.follow(_asset_static_start_2443CsPath2_txt, 5, secToMsec(6), true);
    // intake 5 rings
    chassis.follow(_asset_static_start_2443CsPath3_txt, 5, secToMsec(2), false);
    // drop mobile goal in the corner
    mogo.set_value(false);
}