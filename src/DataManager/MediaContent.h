#pragma once

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class MediaContent {

    public:

        MediaContent();
        MediaContent(string p, int t);
        ~MediaContent();

        string getPath();
        int getType();
        void toString();

    private:


        string path;
        int type; // 1 PDF image - 2 Video - 3 image
};
