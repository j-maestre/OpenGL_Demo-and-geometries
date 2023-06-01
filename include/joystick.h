

#ifndef JOYSTICK__H__
#define JOYSTICK__H__ 1

#include "EDK3/referenced.h"

/**
 * @class Joystick
 * @brief Represents a joystick device derived from EDK3::Referenced.
 *
 * This class defines a joystick device used for input.
 */
class Joystick: public EDK3::Referenced{

    private:
        Joystick& operator=(const Joystick&) = delete;
        Joystick(const Joystick&);
    public:

        /**
        * @brief Constructor.
        *
        * @param location The location of the joystick (default: 0).
        */
        Joystick(int location = 0);

        /**
        * @brief Destructor.
        */
        ~Joystick();

        /**
        * @brief Connects the joystick.
        */
        void conect();

        /**
        * @brief Gets input from a PlayStation 4 controller.
        */
        void getInputFromPS4();
        /**
        * @brief Gets input from an Xbox controller.
        */
        void getInputFromXBox();
        /**
        * @brief Checks if the joystick is connected.
        *
        * @return True if the joystick is connected, false otherwise.
        */
        bool isConected();

        int location_;          ///< The location of the joystick.
        int axesCount_;         ///< The number of axes on the joystick.
        
        // X and Y axis
        float rightAxis_[2];    ///< The values of the right axis (X and Y).
        float leftAxis_[2];     ///< The values of the left axis (X and Y).
        float l2Trigger_;       ///< The value of the L2 trigger.
        float r2Trigger_;       ///< The value of the R2 trigger.
        bool conected_;         ///< Indicates if the joystick is connected.

        float rightDeadZone_;   ///< The dead zone for the right axis.
        float leftDeadZone_;    ///< The dead zone for the left axis.

    protected:

        const float *axes_;


};



#endif