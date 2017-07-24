#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "ZigbController.h"
#include "../util/dynamixel_sdk.h"

#define DEVICENAME_DEFAULT "/dev/ttyUSB0"

class SerialHandler {

    public:
        
        /**
         * Constructs a ZigbController and
         * Dynamixel PortHandler to control robot
         */
        SerialHandler();
        virtual ~SerialHandler();

        /**
         * Opens the zigb port connection
         * Returns 0 if connection was established
         * -1 if connection failed
         */
        int OpenZigbPort();
        
        /**
         * Opens the dynamixel portHandler connection
         * Returns 0 if connection was established
         * -1 if connection failed
         */
        int OpenDynamixelPort();

        ZigbController* GetZigbController();
        dynamixel::PortHandler* GetDynamixelPortHandler();

    private:

        ZigbController* zigb;
        dynamixel::PortHandler* portHandler;

};
#endif
