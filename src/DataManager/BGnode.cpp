#include "BGnode.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe


//-------------------------------------------------------------------------------
BGnode::BGnode(int i, string p, int pxnu, int pynu, int pxu1, int pyu1, int pxu2, int pyu2, int pxbu, int pybu)
{

    id = i;
    path = p;

    posx = pxnu;
    posy = pynu;

    posxinit = posx;
    posydest = posy;

    px_nousers = pxnu;
    py_nousers = pynu;

    px_user1 =  pxu1;
    py_user1 =  pyu1;

    px_user2 = pxu2;
    py_user2 = pyu2;

    px_bothusers = pxbu;
    py_bothusers = pybu;

    nousers = true;
    user1 = true;
    user2 = true;
    bothusers = false;

    loader();
    duration_efect = 1.0;
    state_modified_effect = -1.0;


}
int BGnode::interpolator(int vi, int vf, float timeinit, float duration)
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

void BGnode::loader()
{
    icon.loadImage(path);
}

//-------------------------------------------------------------------------------
void BGnode::draw(bool u1, bool u2)
{

    if( ofGetElapsedTimef()  <=  state_modified_effect + duration_efect )//interpolation movement
    {

        posx = posxinit + interpolator(posxinit, posxdest, state_modified_effect, duration_efect);
        posy = posyinit + interpolator(posyinit, posydest, state_modified_effect, duration_efect);

        ofEnableAlphaBlending();
        ofSetColor(255,255,255,100);
        icon.draw(posx,posy,43,43);
        ofDisableAlphaBlending();



    }
    else
    {
        ofEnableAlphaBlending();
        ofSetColor(255,255,255,100);
        icon.draw(posx,posy,43,43);
        ofDisableAlphaBlending();
       // ofSetColor(255,255,255,255);

    }


    if(u1 == true  && u2 == true) {drawBezier();drawTurnedBezier();}
    if(u1 == false && u2 == true) {drawTurnedBezier();}
    if(u1 == true  && u2 == false){drawBezier();}


}
//-------------------------------------------------------------------------
void BGnode::drawBezier()
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
    output.setLineWidth(1.0f);

    /*
    if(isActive())
    {
        ofSetColor(0,0,0,50);
    }
    else
    {
        ofSetColor(255,255,255,50);
    }
    */
    ofSetColor(255,255,255,50);

    ofEnableAlphaBlending();

    output.bezier(125, 945,
                  125 + 100 +value, 945-75,
                  value2, posyNode-250,
                  posxNode, posyNode);

    ofDisableAlphaBlending();

}

//-------------------------------------------------------------------------
void BGnode::drawTurnedBezier()
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
    output.setLineWidth(1.0f);


    ofSetColor(255,255,255,50);


    ofEnableAlphaBlending();
    //output.setColor(255,255,255);
    output.bezier(posxNode + 43 , posyNode + 43 ,
                  posxNode + 43  + 200 +value, posyNode + 43 +150,
                  1870 - 100 + value2 , 50 +75,
                  1900, 150);



}

//-------------------------------------------------------------------------------
void BGnode::setNoUsers()
{
    nousers = true;
    user1 = false;
    user2 = false;
    bothusers = false;

    state_modified_effect = ofGetElapsedTimef();


    posxinit = posx;
    posyinit = posy;

    posxdest = px_nousers;
    posydest = py_nousers;

    posx = px_nousers;
    posy = py_nousers;
}


//-------------------------------------------------------------------------------
bool BGnode::getNoUsers()
{
    return nousers;
}


//-------------------------------------------------------------------------------
void BGnode::setUser1()
{
    nousers = false;
    user1 = true;
    user2 = false;
    bothusers = false;
    state_modified_effect = ofGetElapsedTimef();

    posxinit = posx;
    posyinit = posy;

    posxdest = px_user1;
    posydest = py_user1;

    //posx = px_user1;
    //posy = py_user1;

}


//-------------------------------------------------------------------------------
bool BGnode::getUser1()
{
    return user1;
}


//-------------------------------------------------------------------------------
void BGnode::setUser2()
{
    nousers = false;
    user1 = false;
    user2 = true;
    bothusers = false;
    state_modified_effect = ofGetElapsedTimef();

    posxinit = posx;
    posyinit = posy;

    posxdest = px_user2;
    posydest = py_user2;


    //posx = px_user2;
    ///posy = py_user2;
}


//-------------------------------------------------------------------------------
bool BGnode::getUser2()
{
    return user2;
}


//-------------------------------------------------------------------------------
void BGnode::setBothUsers()
{
    nousers = false;
    user1 = false;
    user2 = false;
    bothusers = true;
    state_modified_effect = ofGetElapsedTimef();

    posxinit = posx;
    posyinit = posy;

    posxdest = px_bothusers;
    posydest = py_bothusers;

    posx = px_bothusers;
    posy = py_bothusers;
}


//-------------------------------------------------------------------------------
bool BGnode::getBothUsers()
{
    return user2;
}

