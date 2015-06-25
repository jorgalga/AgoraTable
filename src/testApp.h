#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxShivaVGRenderer.h"
#include "ofxXmlSettings.h"

//#include "ofxHttpEvents.h"
#include "ofxXmlSettings.h"

#include <ofURLFileLoader.h>


#include "DataManager/DataManager.h"
#include "DataManager/TuioThread.h"
#include "GUI/Wall.h"
#include "GUI/Infogui.h"
#include "ofxOsc.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file
#define PORT 3333
#define NUM_MSG_STRINGS 20

class Infogui;
class TuioThread;

struct Finger{

    int posx;
    int posy;
    int speedy;
    int id;
    double time_triggered;
    double time_released;
};


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();

		void touchFrameListener();
        void touchFrameManager();


		void draw();

		string serialRead();


		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void fingerPressed(Finger f);
		void mouseReleased(int x, int y, int button);
		void fingerReleased(Finger f);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);




        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif

        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
		bool                mode_video;

		//Agora Table Variables

		//void newResponse(ofxHttpResponse &response);

    private:



        long size_oldScanBufferA;
        long size_oldScanBufferB;
        ofBuffer scanBufferA;
        ofBuffer scanBufferB;

       	ofPtr<ofBaseRenderer> _defaultRenderer;
        ofPtr<ofxShivaVGRenderer> _shivaVGRenderer;

		DataManager *dataManagerInfo;
		Wall *guiWall;

		Infogui* userGui1;
        Infogui* userGui2;

        bool user1_state;
        bool user2_state;


		ofPolyline _polygon;
        ofPath _star;
        ofPath _curvedPath;
        float _shapeSize;


        float click_time;
        float click_duration;

        ofSerial serial;


        //Multitouch Interaction Values
        ofxOscReceiver receiver;
        int current_msg_string;

        vector <Finger> vecFingers;
        bool lockU1;
        bool lockU2;
 };




