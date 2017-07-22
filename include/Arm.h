#ifndef ARM_H_
#define ARM_H_

#include <stdio.h>
#include <iostream>
#include "Servo.h"
#include "dynamixel_sdk.h"
#include "SerialHandler.h"

#define SHOULDER_MAX 800
#define SHOULDER_MIN 150

#define ELBOW_MAX 1023
#define ELBOW_MIN 350

#define WRIST_MAX 762
#define WRIST_MIN 250

#define CLAW_MAX 610
#define CLAW_MIN 220

/**
 * @brief holds the instances of servos for the arm and
 * methods to control the motion of each individual joint
 * and all joints at once.
 */
class Arm {     
    public:
        
        /**
         * Constructor for Arm:
         * Creates instances of Servo for shoulder,
         * elbow, wrist, and claw
         */
        Arm(SerialHandler* serialHandler);
        virtual ~Arm();

        /**
         * Defines an enum for the current arm position
         */ 
        enum class ArmPose {
            DEFAULT, /**<Default position */
            READY, /**<Ready position */
            GRABBING, /**<Grabbing position */
            GRAB /**<Grab cup position */
        };

        /**
         * Sets the position and velocity of each joint in the arm
         * @param pos_shoulder the position setpoint of the shoulder (150 - 800)
         * @param pos_elbow the position setpoint of the elbow (350 - 1023)
         * @param pos_wrist the position setpoint of the wrist (250 - 762)
         * @param pos_claw the position setpoint of the claw (220 - 610)
         * @param vel_setpoint the velocity setpoint of the arm (0 - 1023)
         */
        void Set(int pos_shoulder, int pos_elbow, int pos_wrist, int pos_claw, int vel_setpoint);

        /**
         * Sets the position and velocity of the shoulder
         */
        void SetShoulder(int pos_shoulder, int vel);
        
        /**
         * Sets the position and velocity of the elbow
         */
        void SetElbow(int pos_elbow, int vel);
        
        /**
         * Sets the position and velocity of the wrist
         */
        void SetWrist(int pos_wrist, int vel);
        
        /**
         * Sets the position and velocity of the claw
         */
        void SetClaw(int pos_claw, int vel);

        /**
         * Sets the arm pose
         */
        void SetPose(ArmPose pose);
       
    private:
        SerialHandler* m_serialHandler;
        Servo *shoulder, *elbow, *wrist, *claw;
        int pos_shoulder, pos_elbow, pos_wrist, pos_claw;
        int pose_default[4] = {342, 572, 762, 610};   
        int pose_ready[4] = {650, 700, 350, 220};
        int pose_grabbing[4] = {650, 480, 250, 540};
        
        /**
         * Sets the arm to the deafult startup pose
         */
        void SetDefaultPose();
        
        /**
         * Sets the arm to the ready position
         */
        void SetReadyPose();
        
        /**
         * Sets the arm to the grabbing position
         */
        void SetGrabbingPose();
        
        /**
         * Moves the wrist and claw to grab the cup
         */
        void GrabCup(); 
};

#endif //ARM_H_
