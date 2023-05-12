

#include "joystick.h"
#include "EDK3/dev/glfw3.h"

Joystick::Joystick(int location){
    conected_ = false;
    location_ = location;
}

Joystick::Joystick(const Joystick& j){};


Joystick::~Joystick(){};


void Joystick::conect(){
    conected_ = glfwJoystickPresent(location_);
}

void Joystick::getInput(){

    if(conected_){
        axes_ = glfwGetJoystickAxes(location_,&axesCount_);

        leftAxis_[0] = axes_[0];
        leftAxis_[1] = axes_[1];
        rightAxis_[0] = axes_[2];
        rightAxis_[1] = axes_[3];
        l2Trigger_ = axes_[4];
        r2Trigger_ = axes_[5];
    }
}

bool Joystick::isConected(){
    return conected_;
}






