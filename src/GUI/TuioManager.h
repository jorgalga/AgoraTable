#pragma once

#include "ofMain.h"


#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class TuioManager
{
    public:

        TuioManager();
         ~TuioManager();

         update();

    protected:

        ofxOscReceiver receiver;
        int current_msg_string;

};
