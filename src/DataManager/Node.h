#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

#include "ofxTouchViewRect.h"
#include "ofxTextView.h"
#include "ofxFboSlider.h"
#include "ofxFontStash.h"


class Gesture;
class TranspButt;
class ofxFontStash;
class ofxTextView;
class DataManager;

class Node: public ofxTouchViewRect{

    public:

        Node();
        Node(int px, int py, string ip, DataManager* dm);
		~Node();

		int interpolator(int vi, int vf, float timeinit, float duration);

        void draw(int lang, string ids);
        void drawBezier();

        void drawTurned(int lang,string ids);
        void drawBezierTurned();


        void setTurnedPosition();
        bool isTurned();

        void setTimeOpening();
        void setTimeClosing();
        void setResetPosTime();
        void open();

        void setActive();
        void setNoActive();

        bool isActive();
        bool checkClicked(int px, int py);
        bool checkCollectClicked(int px, int py);

        void move(int pmx, int pmy);

        void toString();
        void setCurrGesture(Gesture* gest);
        Gesture* getCurrGesture();

        void setDisplayed();
        void setNotDisplayed();

        void setOwned();
        void setNotOwned();

        void setInfoSenden();
        void setNoInfosenden();

        void restorePositionInit();

        void reloadGestureImages();
        void reloadImageByIndex(int i);

        int getPosx();
        int getPosy();


        void restoreToPosinit();



        string getSelectedImagePath();
        string getNotSelectedImagePath();
        string intToString(int pNumber);

    private:

        DataManager* datam;

        string idsession;
        string dbip;

        int posx;
        int posy;

        int posxinit;
        int posyinit;

        int width_main_buttom;
        int height_main_button;

        int posx_collect_button;
        int posy_collect_button;
        int width_collect_button;
        int height_collect_button;

        int width_win;
        int height_win;

        int logomaxwidth;
        int logomaxheight;

        ofxVectorGraphics output;

        float open_node_time;           // Time of the las click of the node
        float open_node_duration;       // Time defined for the animation opening
        float close_node_time;          // Time of the las click of the node
        float close_node_duration;      // Time defined for the animation closing

        double duration;
        double resetpostime;


        bool testNode;                  // testing purpose - flat square node

        bool turnedposition;
        bool active;                    //Window with the content is opended
        bool dragged;                   //The node its being dragged

        bool ownedbyuser;               //The Gesture of the node is owned by the user
        bool infosenden;
        bool clickable;                 //It can be clicked
        bool displayed;                 //It is dispayed

        Gesture* currGesture;
        ofImage icon;

        ofImage ToggleGesture;
        ofImage ToggleInfo;

        ofImage closeimage;

        ofImage closeimage_M;
        ofImage closeimage_W;
        ofImage closeimage_E;
        ofImage closeimage_K;

        ofImage iconselected;
        ofImage iconnotselected;

        ofImage iconShadowLogo;

        ofImage iconShadowLogo_M;
        ofImage iconShadowLogo_W;
        ofImage iconShadowLogo_E;
        ofImage iconShadowLogo_K;

        ofImage iconShadowNoLogo;

        ofImage iconShadowNoLogo_M;
        ofImage iconShadowNoLogo_W;
        ofImage iconShadowNoLogo_E;
        ofImage iconShadowNoLogo_K;

        ofImage iconlogo;

        ofImage collectbutton;

        ofImage collectbutton_M;
        ofImage collectbutton_W;
        ofImage collectbutton_E;
        ofImage collectbutton_K;

        ofImage insidering;
        ofImage outsidering;

        ofxFontStash* collectfont;
        ofxTextView* ctext;
        ofxTextView* sitext;

        string collect;
        string decollect;
        string infosend;
        string infosendSL;
        string infonosend;

        double insideangle;
        double outsideangle;
        double degres;


};
