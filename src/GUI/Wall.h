#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

#include "ofxTouchViewRect.h"
#include "ofxSlideshowViewer.h"
#include "ofxPBOVideoPlayer.h"
#include "ofxVideoPlayerView.h"

class DataManager; // We are using this class already implemented in the code
class Htmlstring;
class ofxFboSlider;
class ofxPBOVideoPlayer;
class ofxVideoPlayerView;
class TranspButt;
class  ofxFontStash;

struct iconFBO {
 ofImage img;
 string pathcontent;
 int index;
 int posx;
 int posy;
 bool videotype;
 TranspButt* tp;

};


class Wall: public ofxTouchViewRect{

    public:

        Wall(DataManager* dm);
        ~Wall();

        void update();

        void swapContent();
        void draw();
        void drawBackground();
        void drawBezier();
        void drawNodes();

        void htmlSpliter(string s);
        void htmlSpliter2(string s);
        void htmlSpliter2U2(string s);

        void test(int lang_code); //1 German 2 French
        void test2(int lang_code);

        void loadImageSlider(string path);
        void loadImageSlider2(string path);

        void loadPDFSlider();
        void loadPDFSlider2();

        int getRelativePosTextSliderUser1();
        int getRelativePosTextSliderUser2();
        int getRelativePosImageSliderUser1();
        int getRelativePosImageSliderUser2();
        void setRelativePosTextSliderUser1(int vy);
        void setRelativePosTextSliderUser2(int vy);
        void setRelativePosImageSliderUser1(int vy);
        void setRelativePosImageSliderUser2(int vy);


        void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void closeVideoPlayer(int user);

		void removeStuffUser1();
		void removeStuffUser2();

   private:

        int view_width;

        bool init;
        bool init2;

        int typeBG;
        int yoffset;
        int yoffset2;

        ofImage p;

        DataManager* dataman;

        ofxVectorGraphics output;

        std::string s;

        vector<Htmlstring*> paragraph;
        vector<Htmlstring*> paragraph2;

        ofxFboSlider* textSliderUser1;
        ofxFboSlider* textSliderUser2;

        int size1;
        int size2;
        int sizeimgsld1;
        int sizeimgsld2;

        ofxFboSlider* imageSliderUser1;
        ofxFboSlider* imageSliderUser2;

        ofxFboSlider* pdfSliderUser1;
        ofxFboSlider* pdfSliderUser2;

        iconFBO icon_close1;
        iconFBO icon_close2;

        vector <iconFBO> icoimagesUser1;
        vector <iconFBO> icoimagesUser2;


        ofxVideoPlayerView* videoUser1;
        ofxVideoPlayerView* videoUser2;

        ofxFontStash* myfont;
        ofxFontStash* myfontbold;

        ofFbo* fbo1;
        ofFbo* fbo2a;
        ofFbo* fbo2b;
};
