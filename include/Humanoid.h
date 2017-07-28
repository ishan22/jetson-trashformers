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

class Humanoid {
    public:
        Humanoid(int camPort, std::string model);
        virtual ~Humanoid();

        enum class HumanoidState {
            SEARCHING,
            POSITIONING,
            GRABBING,
            RELEASING
        };

        double GetCupCenterY();
        double GetCupCenterX();

        void UseKeyboard();

        void UpdateState(int xReactionTolerance, int areaTolerance);

        void UpdateState();
        
        void GrabVerticalCup();
        
        void ReleaseCup();

        void Grab();

        SerialHandler* serialHandler;
        Arm* arm;
        DetectNetController* detectnetController;
        BehaviorController* behaviorController; 



    private:
        ZigbController* zigb;
        KeyboardController* keyboardController;
        bool shouldGrab = false;
        bool searchForTrashCan = false;
        bool release = false;
        
        HumanoidState humanoidState;
        DetectNetController::ClassID classID;  
};

#endif // HUMANOID_H_
