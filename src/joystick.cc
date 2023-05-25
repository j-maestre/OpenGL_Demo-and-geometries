

#include "joystick.h"
#include "EDK3/dev/glfw3.h"

Joystick::Joystick(int location){
    conected_ = false;
    location_ = location;
    leftDeadZone_ = 0.18f;
    rightDeadZone_ = 0.18f;
}

Joystick::Joystick(const Joystick& j){};


Joystick::~Joystick(){};


void Joystick::conect(){
    conected_ = glfwJoystickPresent(location_);
}

void Joystick::getInputFromPS4(){

    if(conected_){
        axes_ = glfwGetJoystickAxes(location_,&axesCount_);

        leftAxis_[0] = axes_[0];
        leftAxis_[1] = axes_[1];
        rightAxis_[0] = axes_[2];
        rightAxis_[1] = axes_[3];
        r2Trigger_ = axes_[4];
        l2Trigger_ = axes_[5];
    }
}
void Joystick::getInputFromXBox(){
  if(conected_){
    axes_ = glfwGetJoystickAxes(location_, &axesCount_);

    leftAxis_[0] = axes_[0];
    leftAxis_[1] = axes_[1];
    rightAxis_[0] = axes_[4];
    rightAxis_[1] = axes_[3];
    r2Trigger_ = axes_[2];
    l2Trigger_ = axes_[6];



  }

}

bool Joystick::isConected(){
    return conected_;
}






