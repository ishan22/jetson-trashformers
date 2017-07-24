#include "SerialHandler.h"

SerialHandler::SerialHandler() {
    zigb = new ZigbController();
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME_DEFAULT);

}

SerialHandler::~SerialHandler() {
    zigb->CloseZigbee();
    portHandler->closePort();
}

int SerialHandler::OpenZigbPort() {
    portHandler->closePort();
    return zigb->ConnectZigbee();
}

int SerialHandler::OpenDynamixelPort() {
    zigb->CloseZigbee();
    if(portHandler->openPort()) {
        return 0;
    }
    return -1;
}

ZigbController* SerialHandler::GetZigbController() {
    return zigb;
}

dynamixel::PortHandler* SerialHandler::GetDynamixelPortHandler() {
    return portHandler;
}


