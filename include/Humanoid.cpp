#include "Humanoid.h"

#define DEFAULT_ZIGBEE_DEVICEINDEX 0

Humanoid::Humanoid(int camPort, std::string model) { //CONSTRUCTOR
    serialHandler = new SerialHandler();
    zigb = serialHandler->GetZigbController();
    behaviorController = new BehaviorController(serialHandler);    
    arm = new Arm(serialHandler);
    detectnetController = new DetectNetController(camPort, model);
    keyboardController = new KeyboardController(zigb);
}

Humanoid::~Humanoid() {

}

void Humanoid::UseKeyboard(){
    keyboardController->Init();
    keyboardController->RunInput();
}
        
void Humanoid::UpdateState(float xReactionTolerance, int areaTolerance) {
    detectnetController->SortBBArrayByTargetDistance();
    float xErrorFromCenter = detectnetController->GetErrorXOfTargetBB(0.0);
    float xError = detectnetController->GetErrorXOfTargetBB((1.0/4.0) * detectnetController->GetCameraWidth());
    float yError = detectnetController->GetErrorYOfTargetBB();
    float bbArea = detectnetController->GetAreaOfTargetBB(); 
        
    float xCenterTolerance = 0.1 * detectnetController->GetCameraWidth();
    float yCenterTolerance = 0.05 * detectnetController->GetCameraHeight();
   
    printf("XERROR: %f \nYERROR: %f \n",xErrorFromCenter, yError);
    printf("XTOLERANCE: %f\nYTOLERANCE: %f\n", xCenterTolerance, yCenterTolerance);
     
    if(!seenCup && detectnetController->bbArraySorted.size() > 0){ //if orientation has not been determined and a cup is seen 
        if(xErrorFromCenter >= xCenterTolerance) {
            printf("FINDING CUP TURNING RIGHT\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
        } else if(xErrorFromCenter <= (xCenterTolerance)*-1.0) {
            printf("FINDING CUP TURNING LEFT\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
        } else if(yError <= yCenterTolerance * -1.0) {
            printf("FINDING CUP WALKING FORWARD\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        } else if(yError >= yCenterTolerance) {
            printf("FINDING CUPWALKING BACKWARD\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::WALK_BACKWARD);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        }
        else {
            printf("SEENCUP = TRUE!!!!!!!!!!!!!!\n");
            sleep(3);
            cupOrientation = detectnetController->GetCupOrientation(); 
            if(cupOrientation == DetectNetController::CupOrientation::VERTICAL){
                printf("CUP ORIENTATION: VERTICAL\n");
            }
            else if(cupOrientation == DetectNetController::CupOrientation::HORIZONTAL){
                printf("CUP ORIENTATION: HORIZONTAL\n");
            }
            seenCup = true;
        }
    }
    else if(bbArea == -1) { //else if no cup is seeen
        if(seenCup && grab && (cupOrientation == DetectNetController::CupOrientation::VERTICAL)){
            printf("RUNNING: VERTICAL\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
            sleep(1);
            GrabVerticalCup();
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            grab = false; 
            seenCup = false;
        }
        if(seenCup && grab && (cupOrientation == DetectNetController::CupOrientation::HORIZONTAL)){
            printf("RUNNING: HORIZONTAL\n");
            behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
            printf("BEND DOWN\n"); 
            sleep(1);
            GrabVerticalCup();
            behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
            grab = false; 
            seenCup = false;
        }
        else {
           printf("STOP\n"); 
           behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
        }
    } else if(xError >= xReactionTolerance) {
        printf("TURNING RIGHT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_RIGHT);
    } else if(xError <= (xReactionTolerance)*-1) {
        printf("TURNING LEFT\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STRAFE_LEFT);
    } else if(bbArea <= areaTolerance){
        printf("WALKING FORWARD\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::WALK_FORWARD);
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    } else {
        printf("STOP DUE TO LARGE AREA\n");
        behaviorController->ChangeState(BehaviorController::ControllerState::STOP);
    } 

    if(seenCup) {
	    if(detectnetController->bbArraySorted.size() < 1){
		grab = false; 
		printf("GRAB: NO CUP\n");
	    }
	    else if( detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) > ((2.0/3.0) * detectnetController->GetCameraHeight()) ){
		grab = true; 
		printf("GRAB: TRUE\n");
		printf("CENTER Y of BB: %f\n", detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) );
		printf("image threshold: %f\n", ((2.0/3.0) * detectnetController->GetCameraHeight()) );
	    }
	    else {
		grab = false; 
		printf("GRAB: TOO HIGH\n");
		printf("CENTER Y of BB: %f\n", detectnetController->GetCenterYFromBB(detectnetController->bbArraySorted[0]) );
		printf("image threshold: %f\n", ((2.0/3.0) * detectnetController->GetCameraHeight()) );
		printf("CENTER X of BB: %f\n", detectnetController->GetCenterXFromBB(detectnetController->bbArraySorted[0]) );
		std::cout << (detectnetController->bbArraySorted[0])[0] << std::endl;
	    }
    }
    
    sleep(2);

}

void Humanoid::GrabVerticalCup() { 
    arm->SetPose(Arm::ArmPose::READY);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRABBING);
    sleep(1);
    arm->SetPose(Arm::ArmPose::GRAB);
    sleep(2);
    arm->SetPose(Arm::ArmPose::DEFAULT);
}
