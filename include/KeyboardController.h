#ifndef KEYBOARDCONTROLLER_H_ 
#define KEYBOARDCONTROLLER_H_

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "Controls.h"

#include "ZigbController.h"

/**
 * Class to control zigb commmands through the console input (W,A,S,D)
 */
class KeyboardController{
    public:
        /**
        * Constructor for KeyboardController 
        *
        * @param zigb pointer to instance of zigbee controller
        */
        KeyboardController(ZigbController* zigb);
    
        /**
        * Deconstructor for KeyboardController
        */
        virtual ~KeyboardController();

        /**
        * Setup STDIN for live input
        */
        void Init();
        
        /**
        * Convert inputted characters to zigbee commands. Runs in a loop
        */
        void RunInput();
        
        /**
        * Turn stdin back into normal input
        */
        void Terminate();


    private:
        ZigbController *zigb;
        struct termios old_tio, new_tio;
        unsigned char c;

};

#endif //KEYBOARDCONTROLLER_H_
