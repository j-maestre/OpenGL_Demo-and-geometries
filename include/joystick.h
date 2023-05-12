

#ifndef JOYSTICK__H__
#define JOYSTICK__H__ 1

#include "EDK3/referenced.h"

class Joystick: public EDK3::Referenced{

    private:
        Joystick& operator=(const Joystick&) = delete;
        Joystick(const Joystick&);
    public:
        Joystick(int location = 0);
        ~Joystick();

        void conect();
        void getInput();

        bool isConected();

        int location_;
        int axesCount_;
        
        // X and Y axis
        float rightAxis_[2];
        float leftAxis_[2];
        float l2Trigger_;
        float r2Trigger_;
        bool conected_;

        float rightDeadZone_;
        float leftDeadZone_;

    protected:

        const float *axes_;


};



#endif