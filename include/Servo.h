#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <iostream>
#include <string> 

#include "../util/dynamixel_sdk.h"

#define ADDR_MX_TORQUE_ENABLE 24
#define ADDR_MX_GOAL_TORQUE 34
#define ADDR_MX_GOAL_POSITION 30
#define ADDR_MX_PRESENT_POSITION 36
#define ADDR_MX_GOAL_SPEED 32
#define PROTOCOL_VERSION 1

#define BAUDRATE 1000000 

#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0

#define DEVICENAME_DEFAULT "/dev/ttyUSB0"

/**
* Servo class to control Dynamixel servos
*/
class Servo {
    public:				
        
        /**
         * Creates a Servo object with specified PortHandler
         * and ID number
         */
        Servo(int dxl_id, dynamixel::PortHandler* portHandler);
        
        virtual ~Servo();

        /**
         * Enables the servo to be able to move
         */
        int Enable(bool enable);
        
        /**
         * Sets the position for the servo to move to
         * (setpoint must be between 0 and 1023)
         */
        int SetPositionSetpoint(uint16_t setpoint);
        
        /**
         * Returns the current position of the servo
         */
        int GetPosition();


        /**
         * Sets the velocity of the servo
         * (setpoint must be between 0 and 1023)
         */
        int SetVelocitySetpoint(uint16_t setpoint);
        
        /**
         * Sets the torque of the motor to be at a
         * safe value to prevent overload errors
         */		
        void SetSafeTorque();
    
    private: 
        int m_dxl_id;
        std::string* m_devicename;
        int dxl_comm_result = COMM_TX_FAIL;
        uint8_t dxl_error = 0;
        uint16_t dxl_present_position;

        dynamixel::PortHandler* m_portHandler;
        dynamixel::PacketHandler* packetHandler;
        
        /**
         * Checks for communication error
         */
        bool CheckError();
};
#endif
