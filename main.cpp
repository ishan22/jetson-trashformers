#include "include/Humanoid.h"
#include "include/BehaviorController.h"
#include <iostream>
#include <thread>

/**
* Main function that is called when the program runs.
*/
int main (int argc, char** argv){
    Humanoid* humanoid = new Humanoid(argc, argv);
    
    //Send STOP command to init zigbeecontroller
    humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    
    humanoid->arm->SetDefaultPose();

    //do nothing until detectNet is ready
    while(!humanoid->detectnetController->IsDetectNetReady()) {}

    humanoid->detectnetController->ReadCameraResolution();

    //Define acceptable distance tolerances where robot will no longer react and try to turn
    int xReactionTolerance = 0.10 * humanoid->detectnetController->GetCameraWidth();
    int areaTolerance = 0.50 * humanoid->detectnetController->GetCameraWidth() * humanoid->detectnetController->GetCameraHeight();

    // boolean to check if we should run the grab routine
    bool grab = false;

    //main loop that handles walking, turning and grabbing
    while(true){
    
        //sort the bb array from detectnet
        humanoid->detectnetController->SortBBArrayByTargetDistance();
        
        //store error (difference from set offset) of x coordinate of targetBB
        float xError = humanoid->detectnetController->GetErrorXOfTargetBB();

        //store area of target bb
        float bbArea = humanoid->detectnetController->GetAreaOfTargetBB(); 

        /* if state to handle reaction depending on location of target BB:
        * Note, the order of the else/if statements is important. It first strafes and lines up the x coordinates of the cup, and then walks forward
        */

        //if no bounding box is detected: either grab or stop
        if(xError == NULL || bbArea == -1) {
            if(grab){
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
                humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
                printf("GRABBING\n"); 
                sleep(1);
                humanoid->arm->SetReadyPose();
                sleep(1);
                humanoid->arm->SetGrabbingPose();
                sleep(1);
                humanoid->arm->GrabCup();
                break;
            }
            else {
               printf("STOP\n"); 
               humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            }
        } else if(xError >= xReactionTolerance) { // if x coordinate of bb is less than offset, strafe left
            printf("STRAFING RIGHT\n");
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
        } else if(xError <= (xReactionTolerance)*-1) { // if x coordinate of bb is less than offset, strafe left
            printf("STRAFING LEFT\n");
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        } else if(bbArea <= areaTolerance){ //if targetbb area is less then threshold (almost always)
            printf("WALKING FORWARD\n");
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } else { // if area is too large, stop (this should pretty much never happen)
            printf("ERROR: %f | STOP DUE TO LARGE AREA\n", xError);
            humanoid->behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } 

        
        //if no bounding boxes seen, don't grab
        if(humanoid->detectnetController->bbArraySorted.size() < 1){
            grab = false; 
            printf("SETTING FALSE");
        }
        // the y coordinate of the target bb is on the bottom 2/3rds of the camera frame set grab as true
        else if( humanoid->detectnetController->GetCenterYFromBB(humanoid->detectnetController->bbArraySorted[0]) > ((2.0/3.0) * humanoid->detectnetController->GetCameraHeight()) ){
            grab = true; 
            printf("SETTING TRUE");
            printf("CENTER Y of BB: %f\n", humanoid->detectnetController->GetCenterYFromBB(humanoid->detectnetController->bbArraySorted[0]) );
            printf("image threshold: %f\n", (2.0/3.0) * humanoid->detectnetController->GetCameraHeight() );
        }

        sleep(1);
    }

    printf("Exiting..");

    return 0;
}
