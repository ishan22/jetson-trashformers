#ifndef SERVO_H_
#define SERVO_H_

#include <stdio.h>
#include <iostream>
#include <string> 

#include "../util/dynamixel_sdk.h"

#define ADDR_MX_TORQUE_ENABLE 24
#define ADDR_MX_GOAL_POSITION 30
#define ADDR_MX_PRESENT_POSITION 36
#define ADDR_MX_GOAL_SPEED 32
#define PROTOCOL_VERSION 1

#define BAUDRATE 1000000 

#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0

#define DEVICENAME_DEFAULT "/dev/ttyUSB0"
class Servo {
	public:				
		Servo(int dxl_id, dynamixel::PortHandler* portHandler);
		Servo(int dxl_id, std::string* devicename, dynamixel::PortHandler* portHandler);
		virtual ~Servo();

		int Enable(bool enable);
		int SetPositionSetpoint(uint16_t setpoint);
		int GetPosition();
        
        	int SetVelocitySetpoint(uint16_t setpoint);		
	private: 
		int m_dxl_id;
		std::string* m_devicename;
       		int dxl_comm_result = COMM_TX_FAIL;
        	uint8_t dxl_error = 0;
        	uint16_t dxl_present_position;

        	dynamixel::PortHandler* m_portHandler;
		dynamixel::PacketHandler* packetHandler;

        	bool CheckError();
};
#endif
