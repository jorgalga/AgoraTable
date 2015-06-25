#pragma once

#include "ofMain.h"


#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class TranspButt{

    public:

        TranspButt(int px, int py,  int w, int h);
        ~TranspButt();

        bool isclicked(int px, int py);

        int getPosy();

        void setpos(int x,int y);
        void setActive();
        void setNoActive();
        bool isActive();

        void toString();

    private:

        int posx;
        int posy;
        int width;
        int height;


        int active;
};
