#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "testApp.h"

//========================================================================
int main(int argc, char * argv[] ){

    // create a window
    ofAppGlutWindow window;
    //THIS IS THE IMPORTANT PART:
    window.setGlutDisplayString("rgba alpha double stencil samples>=4");

    if(argc > 1)
    {
        ofSetupOpenGL(&window, 1920,1080, OF_WINDOW);
    }
    else
    {
        ofSetupOpenGL(&window, 1920,1080, OF_FULLSCREEN);
        ofHideCursor();
    }


	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
