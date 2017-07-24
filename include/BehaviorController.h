#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "ZigbController.h"
#include "Controls.h"
#include "SerialHandler.h"

/** 
 * This class controls the current behavior of the robot
 * through the ZigbController SDK.
 */
class BehaviorController {

    public:

        /**
         * Enumeration for the current behavioral
         * state of the robot.
         */
        enum class ControllerState {
            WALK_FORWARD,
            WALK_BACKWARD,
            TURN_RIGHT,
            TURN_LEFT,
            STRAFE_LEFT,
            STRAFE_RIGHT,
            DIAGONAL_RIGHT,
            DIAGONAL_LEFT, 
            BEND_DOWN,
            STOP

        };

        /**
         * Constructor for BehaviorController:
         * Gets the instance of zigb controller from
         * SerialHandler.
         */
        BehaviorController(SerialHandler* serialHandler);
        virtual ~BehaviorController();
        
        /**
         * Changes the state of the robot
         */
        void ChangeState(ControllerState state);


    private:
        ZigbController* m_zigb;
        SerialHandler* m_serialHandler;
};

#endif

