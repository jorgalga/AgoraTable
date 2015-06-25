#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"
#include "ofxFontStash.h"


#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class DataManager;
class TranspButt;
class ofxFontStash;
class ofxTextView;

class Infogui
{
    public:

        Infogui(bool status, DataManager* datam);
        ~Infogui();

        void draw();
        void update();
        void setInitSeason();

        void setActivated();
        void setNotActivated();
        bool isActivated();

        void checkSelectors(int x, int y);


    private:

        ofImage background;
        ofImage mainicon;
        ofImage minicube;

        bool reloadThemeIcon;

        int theme_selected;

        int posx;
        int posy;

        int width;
        int height;

        vector<TranspButt*> vec_selectors;

        TranspButt* selector_de;
        TranspButt* selector_fr;



        string title;

        string txt_energy;
        string txt_habitat;
        string txt_mobility;
        string txt_consumption;

        int amount_co2;
        string text_c02saved;

        bool turned;
        bool active;

        float init_season;
        float close_season;
        float duration_fade;

        ofxFontStash* myfont;
        ofxFontStash* myfont2;
        ofxTextView* text;

        DataManager* dm;
};
