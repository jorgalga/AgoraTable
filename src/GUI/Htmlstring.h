#pragma once

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class Htmlstring{

    public:
        Htmlstring();
        Htmlstring(string t, bool b);
        ~Htmlstring();
        string getText();
        bool isBold();

    private:
        string text;
        bool bold;
};
