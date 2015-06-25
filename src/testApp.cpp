#include "testApp.h"
#include "ofxShivaVGRenderer.h"
#include "DataManager/Gesture.h"
#include "ofxOscMessage.h"
#include "ofxOscReceiver.h"


//--------------------------------------------------------------
void testApp::setup(){

    _shivaVGRenderer = ofPtr<ofxShivaVGRenderer>(new ofxShivaVGRenderer);
    ofSetCurrentRenderer(_shivaVGRenderer);
    ofSetFrameRate(100.0f);

    //--------------------------------------------------------------------
	dataManagerInfo = new DataManager();
	dataManagerInfo->loadSettings();
	dataManagerInfo->loadBgNodes();
	dataManagerInfo->loadGestures();
	dataManagerInfo->setGestureToNodes();

	Gesture * auxg;

	auxg = dataManagerInfo->getGestureOfNode(2);
	auxg->toString();

    //cout << dataManagerInfo->getCategory() << endl;
	guiWall = new Wall(dataManagerInfo);
	guiWall->test(1);
	guiWall->test2(1);

	userGui1 = new Infogui(false, dataManagerInfo); // User gui not flipper
    userGui2 = new Infogui(true, dataManagerInfo);

    click_duration = 0.5;

    user1_state = false;
    user2_state = false;


    //serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();

    int baud = 57600;
    serial.setup(0, 57600); //open the first device and talk to it at 57600 baud
    //serial.enumerateDevices();


    receiver.setup(PORT);

    scanBufferA = ofBufferFromFile("SerialBuffer.txt");
    size_oldScanBufferA = scanBufferA.size();

    lockU1 = false;
    lockU2 = false;
}

//--------------------------------------------------------------
void testApp::update(){
    scanBufferA = ofBufferFromFile("SerialBuffer.txt");
    if(size_oldScanBufferA != scanBufferA.size()) {
        cout << "File size changed" << endl;
        string buff;
        string oldbuff;
        //We read the file until thelast one
        while(!scanBufferA.isLastLine()){
            oldbuff = buff;
            buff = scanBufferA.getNextLine();
        }
        if(buff.compare("")==0)
        {
            if(oldbuff[2]=='1'){
                if(oldbuff[3]=='R')//Release Event
                {
                    lockU1=false;
                    userGui1->setNotActivated();
                    dataManagerInfo->notDisplayNodesUser1();
                    guiWall->removeStuffUser1();
                    if(userGui2->isActivated())
                    {
                        dataManagerInfo->setUsers2();
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->setStateUsers(2);
                    }
                    else{
                        dataManagerInfo->setNoUsers();
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->emptyseasonuser2();
                        dataManagerInfo->setStateUsers(4);
                    }
                }
            }
            if(oldbuff[2]=='2'){
                if(oldbuff[3]=='R'){
                    lockU2 = false;
                    userGui2->setNotActivated();
                    dataManagerInfo->notDisplayNodesUser2();
                     guiWall->removeStuffUser2();
                    if(userGui1->isActivated()){
                        dataManagerInfo->setUsers1();
                        dataManagerInfo->emptyseasonuser2();
                        dataManagerInfo->setStateUsers(1);

                    }
                    else{
                        dataManagerInfo->setNoUsers();
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->emptyseasonuser2();
                        dataManagerInfo->setStateUsers(4);
                    }
                }
            }
        }
        if(buff[2]=='1'){
            if(buff[3]=='R')//Release Event
            {
                userGui1->setNotActivated();
                dataManagerInfo->notDisplayNodesUser1();
                if(userGui2->isActivated()){
                    dataManagerInfo->setUsers2();
                    dataManagerInfo->emptyseasonuser1();
                    dataManagerInfo->setStateUsers(2);
                }
                else{
                    dataManagerInfo->setNoUsers();
                    dataManagerInfo->emptyseasonuser1();
                    dataManagerInfo->emptyseasonuser2();
                    dataManagerInfo->setStateUsers(4);
                }
            }
            else{
                if(lockU1==false){
                    lockU1 = true;
                    buff.erase(0,4);
                    cout << "User1 ID Tablet " << buff << endl;
                    userGui1->setActivated();
                    dataManagerInfo->loadSeasonUser(1,buff);
                    if(userGui2->isActivated()){
                        dataManagerInfo->setBothUsers();
                        dataManagerInfo->setStateUsers(3);
                    }
                    else{
                        dataManagerInfo->setUsers1();//For drawing the background
                        dataManagerInfo->setStateUsers(1);
                    }
                }
            }
        }
        if(buff[2]=='2'){
            if(buff[3]=='R'){
                userGui2->setNotActivated();
                dataManagerInfo->notDisplayNodesUser2();
                if(userGui1->isActivated()){
                    dataManagerInfo->setUsers1();
                    dataManagerInfo->emptyseasonuser2();
                    dataManagerInfo->setStateUsers(1);
                }
                else{
                    dataManagerInfo->setNoUsers();
                    dataManagerInfo->emptyseasonuser1();
                    dataManagerInfo->emptyseasonuser2();
                    dataManagerInfo->setStateUsers(4);
                }
            }
            else{
                if(lockU2 == false)
                {
                    lockU2=true;
                    buff.erase(0,4);
                    cout << "User 2 ID Tablet" << buff << endl;
                    userGui2->setActivated();
                    dataManagerInfo->loadSeasonUser(2,buff);
                    if(userGui1->isActivated()){
                        dataManagerInfo->setBothUsers();
                         dataManagerInfo->setStateUsers(3);
                    }
                    else{
                        dataManagerInfo->setUsers2();//For drawing the background
                        dataManagerInfo->setStateUsers(2);
                    }
                }
            }
        }
        size_oldScanBufferA = scanBufferA.size();
    }
    //----------------------------------------------------------
    //Touch frame tracking
    touchFrameListener();
    dataManagerInfo->update();
    //GuiWall Update
    guiWall->update();
    //UserGUI Update
    userGui1->update();
    userGui2->update();
}

//--------------------------------------------------------------
void testApp::draw(){
        guiWall->draw();
        userGui1->draw();
        userGui2->draw();
        /*
        ofSetColor(255,255,255);
        stringstream reportStr;
        reportStr << "Timer " << ofGetElapsedTimef() << "SinTime " << sin(ofGetElapsedTimef());
        ofDrawBitmapString(reportStr.str(), 20, 600);
        */
}
//--------------------------------------------------------------
void testApp::touchFrameListener()
{
    int indexline = 0;
    int nfingers = 0;
    Finger faux;
    Finger faux2;


    while (receiver.hasWaitingMessages())
    {
        ofxOscMessage m;
		receiver.getNextMessage(&m);
		//First Line. Reading ids of the active fingers
		if(indexline==0){
            if(m.getNumArgs()== 2){nfingers=1;}else{nfingers=2;}
            if(nfingers == 1){
                //cout << "ID 1 " << m.getArgAsInt32(1) << endl;
               //cout << "-------------------------" << endl;
                faux.id = m.getArgAsInt32(1);
            }
            else{
                //cout << "ID 1" << m.getArgAsInt32(1) << endl;
                //cout << "ID 2" << m.getArgAsInt32(2) << endl;
                //cout << "-------------------------" << endl;
                faux.id = m.getArgAsInt32(1);
                faux2.id = m.getArgAsInt32(2);
            }
		}
		//cout << "Nfingers " << nfingers << endl;
		//reading positions and Dragging action (Independetnt of the release or press event)
		if(indexline==1 && nfingers == 1){
		    faux.posx = 1920 * m.getArgAsFloat(2);
            faux.posy = 1080 * m.getArgAsFloat(3);
            //cout << "Dragging [x] " << faux.posx << " [y] " << faux.posy << endl;
            mouseDragged(faux.posx, faux.posy,0);
		}
		if(indexline==2 && nfingers == 2){
		    faux2.posx = 1920* m.getArgAsFloat(2);
            faux2.posy = 1080 * m.getArgAsFloat(3);
            mouseDragged(faux2.posx, faux2.posy,0);
		}
		indexline++;
    }
    if(vecFingers.size() == 0){
        //If there is no messages we clear the vecFingersVector
        if(nfingers == 0){vecFingers.clear();}
        if(nfingers == 1){
            faux.time_triggered = ofGetElapsedTimef();
            vecFingers.push_back(faux);
            fingerPressed(faux);
        }
        if(nfingers == 2){
            faux.time_triggered = ofGetElapsedTimef();
            faux2.time_triggered = ofGetElapsedTimef();
            vecFingers.push_back(faux);
            vecFingers.push_back(faux2);
            fingerPressed(faux);
            fingerPressed(faux2);
        }
    }
    if(vecFingers.size() == 1){
        //If there is no messages we clear the vecFingersVector
        if(nfingers == 0){
            //fingerReleased(vecFingers[0]);
            Finger f = vecFingers[0];
            fingerReleased(f);
            vecFingers.clear();
        }
        if(nfingers == 1){
            if(vecFingers[0].id != faux.id){
                vecFingers.clear();
                faux.time_triggered = ofGetElapsedTimef();
                vecFingers.push_back(faux);
                fingerPressed(faux);
            }
            else{
                vecFingers[0].posx = faux.posx;
                vecFingers[0].posy = faux.posy;
                vecFingers[0].speedy = faux.posy - vecFingers[0].posy;
                cout << "Speed Y: " << vecFingers[0].speedy << endl;
            }
        }
        if(nfingers==2){
            //New points are diferent of the old one
            if( vecFingers[0].id != faux.id && vecFingers[0].id != faux2.id){
                fingerReleased(vecFingers[0]);
                vecFingers.clear();
                faux.time_triggered= ofGetElapsedTimef();
                faux2.time_triggered = ofGetElapsedTimef();
                vecFingers.push_back(faux);
                vecFingers.push_back(faux2);
                fingerPressed(faux);
                fingerPressed(faux2);
            }
            else{
                if(vecFingers[0].id != faux.id){
                    faux.time_triggered = ofGetElapsedTimef();
                    vecFingers.push_back(faux);
                    fingerPressed(faux);
                }
                else{
                    faux2.time_triggered = ofGetElapsedTimef();
                    vecFingers.push_back(faux2);
                    fingerPressed(faux2);
                }
            }
        }
    }
    //there are two elements already tracked in the vector
    if(vecFingers.size() == 2){
        //If there is no messages we clear the vecFingersVector
        if(nfingers == 0){
            fingerReleased(vecFingers[0]);
            fingerReleased(vecFingers[1]);
            vecFingers.clear();
        }
        if(nfingers==1){
            if( vecFingers[0].id != faux.id && vecFingers[1].id != faux.id){
                fingerReleased(vecFingers[0]);
                fingerReleased(vecFingers[1]);
                vecFingers.clear();
                faux.time_triggered = ofGetElapsedTimef();
                vecFingers.push_back(faux);
                fingerPressed(faux);
            }
            else{
                if(vecFingers[0].id == faux.id){
                    fingerReleased(vecFingers[1]);
                    vecFingers.erase(vecFingers.begin()+1);
                }
                else{
                    fingerReleased(vecFingers[0]);
                    vecFingers.erase(vecFingers.begin());
                }
            }
        }
        if(nfingers==2){
            if(vecFingers[0].id!=faux.id && vecFingers[0].id!=faux2.id && vecFingers[1].id!=faux.id && vecFingers[1].id!=faux2.id ){
                fingerReleased(vecFingers[0]);
                fingerReleased(vecFingers[1]);
                vecFingers.clear();

                faux.time_triggered = ofGetElapsedTimef();
                vecFingers.push_back(faux);
                fingerPressed(faux);

                faux2.time_triggered = ofGetElapsedTimef();
                vecFingers.push_back(faux2);
                fingerPressed(faux2);
            }
            else{
                if((faux.id != vecFingers[0].id && faux.id != vecFingers[1].id )&&(faux2.id == vecFingers[0].id || faux2.id == vecFingers[1].id ))
                {
                    if(faux2.id != vecFingers[0].id)
                    {
                        vecFingers.erase(vecFingers.begin());
                        faux.time_triggered = ofGetElapsedTimef();
                        vecFingers.push_back(faux);
                        fingerPressed(faux);
                    }
                    else
                    {
                        vecFingers.erase(vecFingers.begin()+1);
                        faux.time_triggered = ofGetElapsedTimef();
                        vecFingers.push_back(faux);
                        fingerPressed(faux);
                    }
                }
                if((faux.id == vecFingers[0].id || faux.id == vecFingers[1].id )&&(faux2.id != vecFingers[0].id && faux2.id != vecFingers[1].id ))
                {
                     if(faux.id != vecFingers[0].id)
                     {
                         vecFingers.erase(vecFingers.begin());
                         faux2.time_triggered = ofGetElapsedTimef();
                         vecFingers.push_back(faux2);
                         fingerPressed(faux2);
                     }
                     else
                     {
                         vecFingers.erase(vecFingers.begin()+1);
                         faux2.time_triggered = ofGetElapsedTimef();
                         vecFingers.push_back(faux2);
                         fingerPressed(faux2);
                     }
                }
            }
        }
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){

		case ' ':
			dataManagerInfo->listNodes();
			break;
		case '8':
			{
			    cout << "User 1 Category " << dataManagerInfo->getUser1Cat() << endl;
			    dataManagerInfo->printSesionUser1();
			}
			break;
		case '9':
			{
			    cout << "User 2 Category " << dataManagerInfo->getUser2Cat() << endl;
			    dataManagerInfo->printSesionUser2();
			}
			break;
        case 'p':
			cout << "Category " << dataManagerInfo->getCategory() <<endl;
			break;

        case '1'://User 1 at the table
            {
                if(userGui1->isActivated()){
                    userGui1->setNotActivated();
                    guiWall->removeStuffUser1();
                    dataManagerInfo->notDisplayNodesUser1();
                    if(userGui2->isActivated()){
                        dataManagerInfo->setUsers2();
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->setStateUsers(2);
                    }
                    else{
                        dataManagerInfo->setNoUsers();
                        dataManagerInfo->setStateUsers(4);
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->emptyseasonuser2();
                    }
                }
                else{
                    userGui1->setActivated();
                    dataManagerInfo->loadSeasonUser(1,"abc");
                    if(userGui2->isActivated()){
                         dataManagerInfo->setBothUsers();
                         dataManagerInfo->setStateUsers(3);
                    }
                    else{
                         dataManagerInfo->setUsers1();//For drawing the background
                         dataManagerInfo->setStateUsers(1);
                    }
                }
            }
			break;
        case '2'://User 2 at the table
			{
			    if(userGui2->isActivated())
                {
                    guiWall->removeStuffUser2();
                    userGui2->setNotActivated();
                    dataManagerInfo->notDisplayNodesUser2();
                    if(userGui1->isActivated())
                    {
                        dataManagerInfo->setUsers1();
                        dataManagerInfo->setStateUsers(1);
                        dataManagerInfo->emptyseasonuser2();
                    }
                    else{
                        dataManagerInfo->setNoUsers();
                        dataManagerInfo->setStateUsers(4);
                        dataManagerInfo->emptyseasonuser1();
                        dataManagerInfo->emptyseasonuser2();
                    }
                }
                else
                {
                    userGui2->setActivated();
                    dataManagerInfo->loadSeasonUser(2,"abc");
                    if(userGui1->isActivated()){
                         dataManagerInfo->setBothUsers();
                         dataManagerInfo->setStateUsers(3);
                    }
                    else{
                         dataManagerInfo->setUsers2();//For drawing the background
                         dataManagerInfo->setStateUsers(2);
                    }
                }
			}
			break;
        case '3'://Both users at the table
			{
                    //cout << "User 2 " <<endl;
                    //dataManagerInfo->setBothUsers();

			}
			break;
        case '4'://No users at the table
			{
                    //cout << "User 2 " <<endl;
                   // dataManagerInfo->setNoUsers();

			}
			break;
	}
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    dataManagerInfo->moveInteractiveNode(x, y);
    dataManagerInfo->moveInteractiveNode2(x, y);
    if(guiWall != NULL){
        guiWall->mouseDragged(x,y,button);
    }
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    //cout << "Mouse click pressed" << endl;
    cout << "mouseX: " << x << "-- mouseY :" << y << endl;
    guiWall->setRelativePosTextSliderUser1(dataManagerInfo->Slider1LastPos);
    guiWall->setRelativePosTextSliderUser2(dataManagerInfo->Slider2LastPos);
    guiWall->setRelativePosImageSliderUser1(dataManagerInfo->SliderImage1LastPos);
    guiWall->setRelativePosImageSliderUser2(dataManagerInfo->SliderImage2LastPos);


    click_time = ofGetElapsedTimef();
    dataManagerInfo->lockInteractiveNode(x, y);
    if(guiWall != NULL)    {
        guiWall->mousePressed(x,y,0);
    }
}
//--------------------------------------------------------------
void testApp::fingerPressed(Finger f){
    //cout << "Finger click pressed gesture >> " << endl;
    //cout << "fingerX: " << f.posx << "-- FignerY :" << f.posy << endl;
    guiWall->setRelativePosTextSliderUser1(dataManagerInfo->Slider1LastPos);
    guiWall->setRelativePosTextSliderUser2(dataManagerInfo->Slider2LastPos);
    guiWall->setRelativePosImageSliderUser1(dataManagerInfo->SliderImage1LastPos);
    guiWall->setRelativePosImageSliderUser2(dataManagerInfo->SliderImage2LastPos);

    click_time = ofGetElapsedTimef();
    dataManagerInfo->lockInteractiveNode(f.posx, f.posy);
    if(guiWall != NULL){
        guiWall->mousePressed(f.posx,f.posy,0);
    }
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    //cout << "Mouse click released" << endl;
    //cout << "mouseX: " << x << "-- mouseY :" << y << endl;
    if(ofGetElapsedTimef() - click_time <= click_duration){
       dataManagerInfo->checkNodeClicked(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
       dataManagerInfo->checkInterNodeSelectorClicked(x,y);
       userGui1->checkSelectors(x,y);
       userGui2->checkSelectors(x,y);
    }
    else{
        //cout << "Mouse drag released" << endl;
        userGui1->checkSelectors(x,y);
        userGui2->checkSelectors(x,y);
    }
    if(guiWall != NULL){
       guiWall->mouseReleased(x,y,0);

       dataManagerInfo->Slider1LastPos = guiWall->getRelativePosTextSliderUser1();
       dataManagerInfo->Slider2LastPos = guiWall->getRelativePosTextSliderUser2();
       dataManagerInfo->SliderImage1LastPos = guiWall->getRelativePosImageSliderUser1();
       dataManagerInfo->SliderImage1LastPos = guiWall->getRelativePosImageSliderUser2();
    }
    dataManagerInfo->checkNodesLimitPositions();
}
//--------------------------------------------------------------
void testApp::fingerReleased(Finger f){
    cout << "Finger click release gesture >> " << endl;
    cout << "fingerX: " << f.posx << "-- FignerY :" << f.posy << endl;
    if(ofGetElapsedTimef() - f.time_triggered <= click_duration){
        dataManagerInfo->checkNodeClicked(f.posx, f.posy);
        dataManagerInfo->checkInterNodeSelectorClicked(f.posx,f.posy);
        userGui1->checkSelectors(f.posx,f.posy);
        userGui2->checkSelectors(f.posx,f.posy);
    }
    else{
        userGui1->checkSelectors(f.posx,f.posy);
        userGui2->checkSelectors(f.posx,f.posy);
    }
    if(guiWall != NULL){
        guiWall->mouseReleased(f.posx, f.posy, 0);
        dataManagerInfo->Slider1LastPos = guiWall->getRelativePosTextSliderUser1();
        dataManagerInfo->Slider2LastPos = guiWall->getRelativePosTextSliderUser2();
        dataManagerInfo->SliderImage1LastPos = guiWall->getRelativePosImageSliderUser1();
        dataManagerInfo->SliderImage2LastPos = guiWall->getRelativePosImageSliderUser2();
    }
    dataManagerInfo->checkNodesLimitPositions();
}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
string testApp::serialRead(){


}

