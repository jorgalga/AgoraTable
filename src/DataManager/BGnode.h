#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class BGnode
{
    public:

        BGnode();
        BGnode(int i, string p, int pxnu, int pynu, int pxu1, int pyu1, int pxu2, int pyu2, int pxbu, int pybu);
        ~BGnode();

        int interpolator(int vi, int vf, float timeinit, float duration);
        void draw(bool u1, bool u2);
        void drawBezier();
        void drawTurnedBezier();

        void setNoUsers();
        bool getNoUsers();

        void setUser1();
        bool getUser1();

        void setUser2();
        bool getUser2();

        void setBothUsers();
        bool getBothUsers();

        void loader();




    private:

        int id;
        int with;
        int height;
        string path;
        ofImage icon;

        int posx;
        int posy;

        int posxinit;
        int posyinit;

        int posxdest;
        int posydest;

        int px_nousers;
        int py_nousers;

        int px_user1;
        int py_user1;

        int px_user2;
        int py_user2;

        int px_bothusers;
        int py_bothusers;

        bool movement;

        bool nousers;
        bool user1;
        bool user2;
        bool bothusers;

        float duration_efect;
        float state_modified_effect;

        ofxVectorGraphics output;

};
