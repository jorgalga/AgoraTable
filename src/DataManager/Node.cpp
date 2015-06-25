#include "Node.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

#include "DataManager/DataManager.h"
#include "DataManager/Gesture.h"
#include "ofxFontStash.h"
#include "GUI/TranspButt.h"
#include "ofxTextView.h"
//Constructor

Node::Node():ofxTouchViewRect(ofPoint(0,0),0,0)
{
    testNode = true;

    active = false;
    turnedposition = false;
    ownedbyuser = false;


    open_node_duration = 0;
    close_node_time = -1.0;

    open_node_duration = 1.0;
    close_node_duration = 1.0;

    posx = 400;
    posy = 200;

    //iconnotselected.loadImage(getNotSelectedImagePath());
    //iconselected.loadImage(getSelectedImagePath());
}

Node::Node(int px, int py, string ip, DataManager* dm):ofxTouchViewRect(ofPoint(0,0),0,0)
{
    infosenden = true;
    datam = dm;
    testNode = true;
    active = false;
    turnedposition = false;
    ownedbyuser = false;
    clickable = false;
    displayed = false;

    dbip = ip;

    open_node_duration = 0;
    close_node_time = -1.0;

    open_node_duration = 1.0;
    close_node_duration = 1.0;

    duration = 1.0;
    resetpostime = -1.0;

    posx = px;
    posy = py;

    posxinit = px;
    posyinit = py;

    width_main_buttom = 100;
    height_main_button = 100;

    width_win = 350;
    height_win = 500;

    currGesture = new Gesture();
    iconnotselected.loadImage(getNotSelectedImagePath());
    iconselected.loadImage(getSelectedImagePath());

    insidering.loadImage("images/inside_ring.png");
    outsidering.loadImage("images/outside_ring.png");
    ToggleGesture.loadImage("images/node/check-icon.png");
    ToggleInfo.loadImage("images/node/check-info.png");

    iconShadowLogo_M.loadImage("images/node/Mobilitaet_fenster.png");
    iconShadowLogo_W.loadImage("images/node/Wohnen_fenster.png");
    iconShadowLogo_E.loadImage("images/node/Energie_fenster.png");
    iconShadowLogo_K.loadImage("images/node/Konsum_fenster.png");

    iconShadowNoLogo_M.loadImage("images/node/Mobilitaet_fenster_no_logo.png");
    iconShadowNoLogo_W.loadImage("images/node/Wohnen_fenster_no_logo.png");
    iconShadowNoLogo_E.loadImage("images/node/Energie_fenster_no_logo.png");
    iconShadowNoLogo_K.loadImage("images/node/Konsum_fenster_no_logo.png");

    collectbutton_M.loadImage("images/node/Mobilitaet_button.png");
    collectbutton_W.loadImage("images/node/Wohnen_button.png");
    collectbutton_E.loadImage("images/node/Energie_button.png");
    collectbutton_K.loadImage("images/node/Konsum_fenster_no_logo.png");

    closeimage_M.loadImage("images/node/close_green.png");
    closeimage_W.loadImage("images/node/close_orange.png");
    closeimage_E.loadImage("images/node/close_yellow.png");
    closeimage_K.loadImage("images/node/close_purple.png");

    insideangle = 0;
    outsideangle = 0;
    degres = 1.0;

    logomaxwidth = 90;
    logomaxheight = 62 ;

    collectfont = new ofxFontStash();
    collectfont->setup("fonts/Klavika_TTF/Klavika-Medium/Klavika-Medium.ttf",2.0f);


    //posy_collect_button;
    width_collect_button = 90;
    height_collect_button = 32;

    ctext = NULL;
    sitext = NULL;
}

Node::~Node()
{

}

int Node::interpolator(int vi, int vf, float timeinit, float duration)
{
    float animtime = ofGetElapsedTimef() -  timeinit;
    float tmoment = animtime/duration;
    int dist;
    dist = vf-vi;
    float t= animtime;
    float c = dist;



    t /= duration/2;
                if (t < 1) return c/2*t*t ;
                t--;
                return -c/2 * (t*(t-2) - 1) ;


    if (t < 1) return c/2 * std::pow( 2, 10 * (t - 1) ) ;
                t--;
                return c/2 * ( -std::pow( 2, -10 * t) + 2 ) ;
}

//-------------------------------------------------------------------------
void Node::draw(int lang,string ids)
{
    idsession = ids;

    //Updating Node Values
    posx_collect_button = posx+20;
    posy_collect_button = posy+128;
    if(currGesture->hasLogoIncluded())
    {
        posy_collect_button += 58;
    }

    switch(lang)
    {
        case 1:{collect = "HINZUFÜGEN"; decollect = "ENTFERNEN"; infosend= "INFO SENDEN"; infonosend = "KEINE INFO";}break;
        case 2:{collect = "AJOUTER"; decollect = "SUPPRIMER"; infosend= "ENVOYER FICHE"; infonosend = "PAS D'INFO";}break;
    }

    if(displayed == true)
    {

        if(ownedbyuser == true){drawBezier();}

        ofFill();

        if(active ==  false)
        {
            if(ofGetElapsedTimef() < resetpostime + duration)
            {
                //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,interpolator(0,200,resetpostime,duration));
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 1.0;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                if(infosenden==false){ToggleInfo.draw(posx,posy);}
                ofDisableAlphaBlending();
                posx = posxinit;
                posy = posyinit;
            }
            else
            {
                 //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,200);
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 1.0;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();

                    //ToggleGesture.draw(posx, posy);
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                if(infosenden==false){ToggleInfo.draw(posx,posy);}
                ofDisableAlphaBlending();
            }
        }
        else
        {
            if(ofGetElapsedTimef() < resetpostime + duration) //Opening mode - Triggering time
            {
                //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,interpolator(0,200,resetpostime,duration));
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 0.5;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    if(infosenden==false){ToggleInfo.draw(posx,posy);}
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                ofDisableAlphaBlending();
                posx = posxinit;
                posy = posyinit;
            }
            else // Node Active / Window Opened
            {
                 //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,200);

                if(currGesture->hasLogoIncluded())
                {
                    switch(currGesture->getTheme())
                    {
                        case 1:{
                        iconShadowLogo_M.draw(posx+20,posy+18,110,210);
                        collectbutton_M.draw(posx_collect_button ,posy_collect_button,110,140);
                        collectbutton_M.draw(posx_collect_button ,posy_collect_button+62,110,140);

                        }break;
                        case 2:{
                        iconShadowLogo_W.draw(posx+20,posy+18,110,210);
                        collectbutton_W.draw(posx_collect_button ,posy_collect_button,110,140);
                        collectbutton_W.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 3:{
                        iconShadowLogo_E.draw(posx+20,posy+18,110,210);
                        collectbutton_E.draw(posx_collect_button ,posy_collect_button,110,140);
                        collectbutton_E.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 4:{
                        iconShadowLogo_K.draw(posx+20,posy+18,110,210);
                        collectbutton_K.draw(posx_collect_button ,posy_collect_button,110,140);
                        collectbutton_K.draw(posx_collect_button ,posy_collect_button+62,110,140);

                        }break;
                    }
                    iconlogo.loadImage(currGesture->getLogoPath());
                    if(iconlogo.getWidth() >= iconlogo.getHeight()){
                        if(iconlogo.getWidth() > logomaxwidth ){
                            iconlogo.resize(logomaxwidth, logomaxwidth*iconlogo.getHeight()/iconlogo.getWidth());
                        }
                    }
                    else{
                        if(iconlogo.getHeight() > logomaxheight){
                            iconlogo.resize(logomaxheight*iconlogo.getWidth()/iconlogo.getHeight(),logomaxheight);
                        }
                    }
                    ofDisableAlphaBlending();
                    ofSetColor(255,255,255);
                    ofRect(posx+20,posy+104,logomaxwidth, logomaxheight);
                    ofEnableAlphaBlending();
                    iconlogo.draw(posx+20,posy+104);
                    //iconlogo.clear();
                    if(infosenden==false){ToggleInfo.draw(posx,posy);}
                }
                else
                {
                    switch(currGesture->getTheme())
                    {
                        case 1:{
                            iconShadowNoLogo_M.draw(posx+20,posy+18,110,160);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button +62,110,140);
                        }break;
                        case 2:{
                            iconShadowNoLogo_W.draw(posx+20,posy+18,110,160);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 3:{
                            iconShadowNoLogo_E.draw(posx+20,posy+18,110,160);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_E.draw(posx_collect_button  ,posy_collect_button +62,110,140);
                        }break;
                        case 4:{
                            iconShadowNoLogo_K.draw(posx+20,posy+18,110,160);
                            collectbutton_K.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_K.draw(posx_collect_button  ,posy_collect_button +62,110,140);
                        }break;
                    }
                }
                if(ownedbyuser == true)
                {

                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 0.5;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);

                    switch(currGesture->getTheme())
                    {
                        case 1:{closeimage_M.draw(posx-6,posy+64);}break;
                        case 2:{closeimage_W.draw(posx-6,posy+64);}break;
                        case 3:{closeimage_E.draw(posx-6,posy+64);}break;
                        case 4:{closeimage_K.draw(posx-6,posy+64);}break;
                    }

                    if(currGesture->hasLogoIncluded())
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+202));
                    }
                    else
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+150));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(decollect);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext; ctext = NULL;
                    if(infosenden==false){ofEnableAlphaBlending();ToggleInfo.draw(posx,posy);}
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                    switch(currGesture->getTheme())
                    {
                        case 1:{closeimage_M.draw(posx-6,posy+64);}break;
                        case 2:{closeimage_W.draw(posx-6,posy+64);}break;
                        case 3:{closeimage_E.draw(posx-6,posy+64);}break;
                        case 4:{closeimage_K.draw(posx-6,posy+64);}break;
                    }
                    if(currGesture->hasLogoIncluded())
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+202));
                    }
                    else
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+150));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(collect);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext;ctext = NULL;
                    if(infosenden==false){ofEnableAlphaBlending();ToggleInfo.draw(posx,posy);}
                }
                if(infosenden == true)
                {
                    if(currGesture->hasLogoIncluded())
                    {
                        sitext = new ofxTextView(ofPoint(posx+24, posy+264));
                    }
                    else
                    {
                        sitext = new ofxTextView(ofPoint(posx+24, posy+212));
                    }
                    sitext->setFont(collectfont, 12);
                    sitext->setText(infosend);
                    sitext->setTextColor(ofColor(255,255,255,200));
                    sitext->draw();
                    delete sitext;sitext = NULL;
                }
                else
                {
                    if(currGesture->hasLogoIncluded())
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+264));
                    }
                    else
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+212));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(infonosend);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext; ctext = NULL;

                }

                ofDisableAlphaBlending();
            }
            /*
            if(ctext != NULL){delete ctext;}
            if(sitext != NULL){delete sitext;}
            ctext = NULL;
            sitext = NULL;
            */
        }
    }
    else
    {}
}

//-------------------------------------------------------------------------
void Node::drawTurned(int lang,string ids)
{
    idsession = ids;

    //active = false;

    //Updating Node Values
    posx_collect_button = posx+20;
    posy_collect_button = posy+128;
    if(currGesture->hasLogoIncluded())
    {
        posy_collect_button += 58;
    }

    switch(lang)
    {
        case 1:{collect = "HINZUFÜGEN"; decollect = "ENTFERNEN"; infosend= "INFO SENDEN"; infonosend = "KEINE INFO";}break;
        case 2:{collect = "AJOUTER"; decollect = "SUPPRIMER";  infosend= "ENVOYER FICHE"; infonosend = "PAS D'INFO"; }break;
    }

    if(displayed == true)
    {
         if(ownedbyuser == true){drawBezierTurned();}
        ofPushMatrix();
        ofTranslate(posx + 60 ,posy + 60 );
        ofRotateZ(180);
        ofPushMatrix();
        ofTranslate(-posx-  60, -posy - 60);



        ofFill();

        if(active ==  false)
        {
            if(ofGetElapsedTimef() < resetpostime + duration)
            {
                //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,interpolator(0,200,resetpostime,duration));
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 1.0;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                if(infosenden==false){ToggleInfo.draw(posx,posy);}
                ofDisableAlphaBlending();
                posx = posxinit;
                posy = posyinit;
            }
            else
            {
                 //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,200);
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 1.0;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                if(infosenden==false){ToggleInfo.draw(posx,posy);}
                ofDisableAlphaBlending();
            }
        }
        else
        {
            if(ofGetElapsedTimef() < resetpostime + duration) //Opening mode - Triggering time
            {
                //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,interpolator(0,200,resetpostime,duration));
                if(ownedbyuser == true)
                {
                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 0.5;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                }
                if(infosenden==false){ToggleInfo.draw(posx,posy);}
                ofDisableAlphaBlending();
                posx = posxinit;
                posy = posyinit;
            }
            else // Node Active / Window Opened
            {
                 //Drawing main button
                ofEnableAlphaBlending();
                ofSetColor(255,255,255,200);

                if(currGesture->hasLogoIncluded())
                {
                    switch(currGesture->getTheme())
                    {
                        case 1:{
                            iconShadowLogo_M.draw(posx+20,posy+18,110,210);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 2:{
                            iconShadowLogo_W.draw(posx+20,posy+18,110,210);
                            collectbutton_W.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_W.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 3:{
                            iconShadowLogo_E.draw(posx+20,posy+18,110,210);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 4:{
                            iconShadowLogo_K.draw(posx+20,posy+18,110,210);
                            collectbutton_K.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_K.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                    }
                    iconlogo.loadImage(currGesture->getLogoPath());
                    if(iconlogo.getWidth() >= iconlogo.getHeight()){
                        if(iconlogo.getWidth() > logomaxwidth ){
                            iconlogo.resize(logomaxwidth, logomaxwidth*iconlogo.getHeight()/iconlogo.getWidth());
                        }
                    }
                    else{
                        if(iconlogo.getHeight() > logomaxheight){
                            iconlogo.resize(logomaxheight*iconlogo.getWidth()/iconlogo.getHeight(),logomaxheight);
                        }
                    }
                    ofDisableAlphaBlending();
                    ofSetColor(255,255,255);
                    ofRect(posx+20,posy+104,logomaxwidth, logomaxheight);
                    ofEnableAlphaBlending();
                    iconlogo.draw(posx+20,posy+104);
                }
                else
                {
                    switch(currGesture->getTheme())
                    {
                        case 1:{
                            iconShadowNoLogo_M.draw(posx+20,posy+18,110,160);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_M.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 2:{
                            iconShadowNoLogo_W.draw(posx+20,posy+18,110,160);
                            collectbutton_W.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_W.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 3:{
                            iconShadowNoLogo_E.draw(posx+20,posy+18,110,160);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_E.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                        case 4:{
                            iconShadowNoLogo_K.draw(posx+20,posy+18,110,160);
                            collectbutton_K.draw(posx_collect_button ,posy_collect_button,110,140);
                            collectbutton_K.draw(posx_collect_button ,posy_collect_button+62,110,140);
                        }break;
                    }
                }
                if(ownedbyuser == true)
                {

                    iconselected.draw(posx,posy,121,121);
                    insidering.draw(posx-55,posy-55,195,195);

                    degres += 0.5;

                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    insidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();


                    ofPushMatrix();
                    ofTranslate(posx+42, posy+42, 0);
                    ofRotateZ(degres);
                    outsidering.draw(-97.5,-97.5,195,195);
                    ofPopMatrix();
                    //ToggleGesture.draw(posx, posy);
                    switch(currGesture->getTheme())
                    {
                        case 1:{closeimage_M.draw(posx-6,posy+64);}break;
                        case 2:{closeimage_W.draw(posx-6,posy+64);}break;
                        case 3:{closeimage_E.draw(posx-6,posy+64);}break;
                        case 4:{closeimage_K.draw(posx-6,posy+64);}break;
                    }

                    if(currGesture->hasLogoIncluded())
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+202));

                    }
                    else
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+150));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(decollect);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext;
                }
                else
                {
                    iconselected.draw(posx,posy,121,121);
                     switch(currGesture->getTheme())
                    {
                        case 1:{closeimage_M.draw(posx-6,posy+64);}break;
                        case 2:{closeimage_W.draw(posx-6,posy+64);}break;
                        case 3:{closeimage_E.draw(posx-6,posy+64);}break;
                        case 4:{closeimage_K.draw(posx-6,posy+64);}break;
                    }
                    if(currGesture->hasLogoIncluded())
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+202));
                    }
                    else
                    {
                        ctext = new ofxTextView(ofPoint(posx+24, posy+150));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(collect);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext;
                }

                if(infosenden == true)
                {
                    if(currGesture->hasLogoIncluded())
                    {

                        sitext = new ofxTextView(ofPoint(posx+24, posy+264));
                    }
                    else
                    {

                        sitext = new ofxTextView(ofPoint(posx+24, posy+212));
                    }
                    sitext->setFont(collectfont, 12);
                    sitext->setText(infosend);
                    sitext->setTextColor(ofColor(255,255,255,200));
                    sitext->draw();
                    delete sitext;
                }
                else
                {   ofEnableAlphaBlending();
                    ToggleInfo.draw(posx,posy);
                    if(currGesture->hasLogoIncluded())
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+264));
                    }
                    else
                    {

                        ctext = new ofxTextView(ofPoint(posx+24, posy+212));
                    }
                    ctext->setFont(collectfont, 12);
                    ctext->setText(infonosend);
                    ctext->setTextColor(ofColor(255,255,255,200));
                    ctext->draw();
                    delete ctext;
                }
                ofDisableAlphaBlending();
            }
        }
        ofPopMatrix();
        ofPopMatrix();

    }
    else
    {}

}


//-------------------------------------------------------------------------
void Node::drawBezier()
{
    int posxNode;
    int posyNode;

    posxNode = posx;
    posyNode = posy;


    //cout << ofGetWindowWidth() << endl;

    float value = sin(ofGetElapsedTimef());
    value = 20 * value;

    float value2 = sin(ofGetElapsedTimef()+200.0);
    value2 = 20* value2;

    output.noFill();
    output.setLineWidth(3.0f);

    if(ofGetElapsedTimef() < resetpostime + duration) //Opening mode - Triggering time
    {
        ofSetColor(255,255,255,interpolator(0,66,resetpostime, duration));
    }
    else
    {
        ofSetColor(255,255,255,66);
    }

    ofEnableAlphaBlending();

    output.bezier(125, 945,
                  125 + 100 +value, 945,
                  value2, posyNode,
                  posxNode, posyNode);

    ofDisableAlphaBlending();
}

//-------------------------------------------------------------------------
void Node::drawBezierTurned()
{
    int posxNode;
    int posyNode;

    posxNode = posx;
    posyNode = posy;


    //cout << ofGetWindowWidth() << endl;

    float value = sin(ofGetElapsedTimef());
    value = 10 * value;

    float value2 = sin(ofGetElapsedTimef()+200.0);
    value2 = 10* value2;

    output.noFill();
    output.setLineWidth(3.0f);

    if(ofGetElapsedTimef() < resetpostime + duration) //Opening mode - Triggering time
    {
        ofSetColor(255,255,255,interpolator(0,66,resetpostime, duration));
    }
    else
    {
        ofSetColor(255,255,255,66);
    }

    ofEnableAlphaBlending();
    //output.setColor(255,255,255);
    output.bezier(posxNode + width_main_buttom +20, posyNode + height_main_button +20,
                  posxNode + width_main_buttom  + 200 +value, posyNode + height_main_button,
                  ofGetWindowWidth() - ofGetWindowWidth()/16  + value2 , ofGetWindowHeight()/9,
                  ofGetWindowWidth() - ofGetWindowWidth()/16, ofGetWindowHeight()/9);

}
//-------------------------------------------------------------------------
void Node::setTurnedPosition()
{
    turnedposition = true;

}

//-------------------------------------------------------------------------
bool Node::isTurned()
{
    return turnedposition;
}

//-------------------------------------------------------------------------
void Node::setTimeOpening()
{
    open_node_time = ofGetElapsedTimef();

    active = true;
    //cout << "current time" << ofGetElapsedTimef() << endl;

}
//-------------------------------------------------------------------------
void Node::setResetPosTime()
{
    resetpostime =  ofGetElapsedTimef();
}

//-------------------------------------------------------------------------
void Node::setTimeClosing()
{
    close_node_time = ofGetElapsedTimef();
    active = false;
}
//-------------------------------------------------------------------------
void Node::setActive()
{
    active = true;
}

//-------------------------------------------------------------------------
void Node::setNoActive()
{
    active = false;
}

//-------------------------------------------------------------------------
bool Node::isActive()
{
    return active;
}

//-------------------------------------------------------------------------
void Node::setDisplayed()
{
    displayed = true;
    clickable = true;
}

//-------------------------------------------------------------------------
void Node::setNotDisplayed()
{
    displayed = false;
    clickable = false;
}

//-------------------------------------------------------------------------
void Node::setOwned()
{
    ownedbyuser = true;
}
//-------------------------------------------------------------------------
void Node::setNotOwned()
{
    ownedbyuser = false;
}
//-------------------------------------------------------------------------
void Node::setInfoSenden()
{
    infosenden = true;
}
//-------------------------------------------------------------------------
void Node::setNoInfosenden()
{
    infosenden = false;
}
//-------------------------------------------------------------------------
void Node::restorePositionInit()
{
    posx = posxinit;
    posy = posyinit;
}
//-------------------------------------------------------------------------
bool Node::checkClicked(int px, int py)
{
    if(clickable==true)
    {
            if(posx < px && px <= posx + width_main_buttom )
            {
                if(posy < py && py <= posy + height_main_button )
                {
                     return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
    }
    else
    {
        return false;
    }
}

bool Node::checkCollectClicked(int px, int py)
{
    string res = dbip;

    int posx_cb = posx +10;
    int posy_cb = posy -50;
    int offset=0;


    if(clickable == true)
    {
        if(!isTurned())
        {
            //Collect button interaction
            if(posx_collect_button < px && px <= posx_collect_button + width_collect_button)
            {
                if(posy_collect_button < py && py <= posy_collect_button+height_collect_button )
                {
                    //cout << "Clicked Collected" << endl;
                    if(ownedbyuser == true)
                    {
                        setNotOwned();
                        res += "gesturedb/request.php?cmd=removeSessionGesture&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        ofHttpResponse request = ofLoadURL(res);
                        datam->removeGestureToSession(1,currGesture->getId()-1);
                        datam->setTotalCO2Impact(1);
                        datam->setTotalCO2ImpactByTheme(1, 1);
                        datam->setTotalCO2ImpactByTheme(1, 2);
                        datam->setTotalCO2ImpactByTheme(1, 3);
                        datam->setTotalCO2ImpactByTheme(1, 4);
                    }
                    else
                    {
                        setOwned();
                        res += "gesturedb/request.php?cmd=addSessionGesture&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        currGesture->toString();
                        cout << res << endl;
                        ofHttpResponse request = ofLoadURL(res);
                        datam->addGestureToSession(1,currGesture->getId() -1);
                        datam->setTotalCO2Impact(1);
                        datam->setTotalCO2ImpactByTheme(1, 1);
                        datam->setTotalCO2ImpactByTheme(1, 2);
                        datam->setTotalCO2ImpactByTheme(1, 3);
                        datam->setTotalCO2ImpactByTheme(1, 4);
                    }
                    return true;
                }
            }
            //Button Info Senden
            if(posx_collect_button < px && px <= posx_collect_button + width_collect_button)
            {
                if(posy_collect_button+62 < py && py <= posy_collect_button+62+height_collect_button )
                {
                    //cout << "clicked InfoSenden" << endl;
                    if(infosenden == true)
                    {
                        //http://192.168.5.172/gesturedb/request.php?cmd=addSessionMessage&sessionid=1184&gestureid=1

                        setNoInfosenden();

                        res += "gesturedb/request.php?cmd=addSessionMessage&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        ofHttpResponse request = ofLoadURL(res);
                        datam->addMessageToSession(1,currGesture->getId() -1);
                    }
                    else
                    {
                        setInfoSenden();
                        res += "gesturedb/request.php?cmd=removeSessionMessage&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        ofHttpResponse request = ofLoadURL(res);
                        datam->removeMessageToSession(1,currGesture->getId() -1);
                    }
                }
            }
        }
        else
        {
            if(currGesture->hasLogoIncluded()){offset=55;}
            if(posx_cb < px && px <= posx_cb + width_collect_button)
            {
                if(posy_cb -offset < py && py <= posy_cb+height_collect_button -offset )
                {
                    if(ownedbyuser == true)
                    {
                        setNotOwned();

                        res += "gesturedb/request.php?cmd=removeSessionGesture&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());

                        ofHttpResponse request = ofLoadURL(res);

                        //addtoUser2
                        datam->removeGestureToSession(2,currGesture->getId()-1);
                        datam->setTotalCO2Impact(2);
                        datam->setTotalCO2ImpactByTheme(2, 1);
                        datam->setTotalCO2ImpactByTheme(2, 2);
                        datam->setTotalCO2ImpactByTheme(2, 3);
                        datam->setTotalCO2ImpactByTheme(2, 4);
                    }
                    else
                    {
                        setOwned();

                        res += "gesturedb/request.php?cmd=addSessionGesture&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());

                        currGesture->toString();

                        cout << res << endl;

                        ofHttpResponse request = ofLoadURL(res);

                        datam->addGestureToSession(2,currGesture->getId() -1);
                        datam->setTotalCO2Impact(2);
                        datam->setTotalCO2ImpactByTheme(2, 1);
                        datam->setTotalCO2ImpactByTheme(2, 2);
                        datam->setTotalCO2ImpactByTheme(2, 3);
                        datam->setTotalCO2ImpactByTheme(2, 4);
                    }
                    return true;
                }
            }
            if(posx_cb < px && px <= posx_cb + width_collect_button)
            {
                if(posy_cb -62 -offset < py && py <= posy_cb -62 + height_collect_button -offset  )
                {
                    cout << "Send info button clicked" << endl;
                     if(infosenden == true)
                    {
                        //http://192.168.5.172/gesturedb/request.php?cmd=addSessionMessage&sessionid=1184&gestureid=1

                        setNoInfosenden();

                        res = dbip;
                        res += "gesturedb/request.php?cmd=addSessionMessage&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        cout << res << endl;
                        ofHttpResponse request = ofLoadURL(res);
                        datam->addMessageToSession(2,currGesture->getId() -1);
                    }
                    else
                    {
                        setInfoSenden();
                        res = dbip;
                        res += "gesturedb/request.php?cmd=removeSessionMessage&sessionid=";
                        res += idsession;
                        res += "&gestureid=";
                        res += intToString(currGesture->getId());
                        ofHttpResponse request = ofLoadURL(res);
                        datam->removeMessageToSession(2,currGesture->getId() -1);
                    }
                }
            }
        }

    }
    return false;
}


//-------------------------------------------------------------------------
//Move funtion for all the elementes Attached to Node
void Node::move(int pmx, int pmy)
{
    int difx;
    int dify;

    difx = pmx - posx; //cout << "difx " << difx << endl;
    dify = pmy - posy;


    if(isActive())
    {
        posx = pmx - 25;
        posy = pmy - 25;
    }
    else
    {
        posx = pmx - 25;
        posy = pmy - 25;
    }

}


//-------------------------------------------------------------------------
void Node::toString()
{
    cout << "Node in posx: " << posx << " posy: "<< posy << " Activated: " << isActive() << endl;
}


//-------------------------------------------------------------------------
void Node::setCurrGesture(Gesture* gest)
{
    currGesture = gest;
}

Gesture* Node::getCurrGesture()
{
    return currGesture;
}
//-------------------------------------------------------------------------
int Node::getPosx()
{
    return posx;
}
//-------------------------------------------------------------------------
int Node::getPosy()
{
    return posy;
}
void Node::reloadImageByIndex(int i)
{
     string res1 = "images/gesticons_nonselected/";
     res1 += intToString(i);
     res1 += ".png";
     string res2 = "images/gesticons_selected/";
     res2 += intToString(i);
     res2 += ".png";

     //Mobility
     /*
     if(i >= 0 && i < 10)
     {
        res2 += "Mobilitaet_fenster_no_logo.png";
     }//Habitat
     else if(i >= 10 && i <20)
     {
        res2 += "Mobilitaet_fenster_no_logo.png";
     }//Energy
     else if(i >= 20 && i < 30)
     {
        res2 += "Mobilitaet_fenster_no_logo.png";
     }//Consumption
     else if(i >= 30 && i < 40)
     {
        res2 += "Mobilitaet_fenster_no_logo.png";
     }
    */
     cout << res1<< endl;

     iconnotselected.loadImage(res1);
     iconselected.loadImage(res2);
}

//------------------------------------------------------------------------
void Node::reloadGestureImages()
{
    iconnotselected.loadImage(getNotSelectedImagePath());
    iconselected.loadImage(getSelectedImagePath());

    cout << "Reloading Images" << endl;
    currGesture->toString();
}
//------------------------------------------------------------------------
void Node::restoreToPosinit()
{
    posx = posxinit;
    posy = posyinit;
}

//-------------------------------------------------------------------------
string Node::getSelectedImagePath()
{
    string res = "images/gesticons_selected/";
    res += intToString(currGesture->getId());
    res += ".png";

    cout << res << endl;

    return res;
}

//-------------------------------------------------------------------------
string Node::getNotSelectedImagePath()
{
    string res = "images/gesticons_nonselected/";
    res += intToString(currGesture->getId());
    res += ".png";

    return res;
}

//-------------------------------------------------------------------------
string Node::intToString(int pNumber)
{
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}
