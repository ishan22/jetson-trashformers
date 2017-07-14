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
#include "Head.h"
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
        Humanoid(int argc, char** argv);

        /**
         * Deconstructor for Humanoid
         */
        virtual ~Humanoid();

        /**
         * Runs a while loop in keyboardController to send zigbee commands via keyboard input
         */
        void UseKeyboard();
        
        //Movement commands through Zigbee
        void Stop();
        
        void WalkForward();
        void WalkBackward();

        void TurnLeft();
        void TurnRight();

        void WalkForwardLeft();
        void WalkForwardRight();

        void SidestepLeft();
        void SidestepRight();

        void FastSidestepLeft();
        void FastSidestepRight();

        void StepDiagonalFrontalLeft();
        void StepDiagonalFrontalRight();

        void StepDiagonalDorsalLeft();
        void StepDiagonalDorsalRight();

        void GetUpFacingUp();
        void GetUpFacingDown();

        SerialHandler* serialHandler;
        Arm* arm;
        Head* head;
        DetectNetController* detectnetController;
        BehaviorController* behaviorController; 
    private:
        ZigbController* zigb;
        KeyboardController* keyboardController;
};

#endif // HUMANOID_H_
