#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include <iostream>
#include <thread>

int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    int inputChar; 
       
    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    
    //humanoid->arm->SetDefaultPose();
    
    while(true) {
        humanoid->arm->LivePose();
        std::cin.ignore();
    }    
    //humanoid->detectnetController->JoinDetectThread();
    printf("Exiting..");

    return 0;
}
