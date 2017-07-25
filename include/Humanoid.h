#ifndef HUMANOID_H_
#define HUMANOID_H_

#include <stdio.h>
#include <iostream>

#include "ZigbController.h"
#include "KeyboardController.h"
#include "DetectNetController.h"
#include "Controls.h"
#include "Arm.h"
#include "Servo.h"
#include "SerialHandler.h"
#include "BehaviorController.h"

/**
 * @brief holds the instances of many of the hardware/software modules of the program.
 */
class Humanoid {
    public:
        /**
         * Constructor for Humanoid:
         * Creates instances of serialhandler, behaviorcontroller, 
         * arm, head, detectnet controller, and keyboardcontroller
        */
        Humanoid(int camPort, std::string model);
        virtual ~Humanoid();

        /**
         * Runs a while loop in keyboardController to send zigbee commands via keyboard input
         */
        void UseKeyboard();

        /**
         * Updates the current state of the robot based on the 
         * current position of the cup bounding box.
         */
        void UpdateState(int xReactionTolerance, int areaTolerance);
       
        /**
         * Routine to grab a cup that is sitting vertically
         * on the ground
         */ 
        void GrabVerticalCup();
        
        SerialHandler* serialHandler;
        Arm* arm;
        DetectNetController* detectnetController;
        BehaviorController* behaviorController; 
    private:
        KeyboardController* keyboardController;
        bool grab = false;
};

#endif // HUMANOID_H_
