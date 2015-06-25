#include "Infogui.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

#include "DataManager/DataManager.h"
#include "ofxFontStash.h"
#include "GUI/TranspButt.h"
#include "ofxTextView.h"

Infogui::Infogui(bool status, DataManager* datam)
{
    turned = status;
    dm = datam;

    text = NULL;

    active = false;

    theme_selected = datam->getCategory();

    reloadThemeIcon = true;

    myfont = new ofxFontStash();
    myfont->setup("fonts/Klavika_TTF/Klavika-Medium/Klavika-Medium.ttf",2.0f);

    myfont2 = new ofxFontStash();
    myfont2->setup("fonts/Klavika_TTF/Klavika-Light/Klavika-Light.ttf",2.0f);

    mainicon.loadImage("images/infogui/Mobilitaet_Icon.png");
    minicube.loadImage("images/infogui/cube.png");

    switch(datam->getCategory())
    {


        case 1:{background.loadImage("images/infogui/Mobilitaet_box.png");}break;
        case 2:{background.loadImage("images/infogui/Wohnen_box.png");}break;
        case 3:{background.loadImage("images/infogui/Energie_box.png");}break;
        case 4:{background.loadImage("images/infogui/Konsum_box.png");}break;

    }


    if(turned == true)
    {
        posx = 1100;
        posy = 0;

        TranspButt* aux = new TranspButt(posx+450,posy + 72 + 28*3, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+450,posy + 72 +28*2, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+450,posy + 72 +28, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+450,posy + 72, 175, 28);
        vec_selectors.push_back(aux);

        selector_de = new TranspButt(posx + 775,posy +20,30,30);
        selector_fr = new TranspButt(posx + 725,posy +20,30,30);



    }
    else
    {
        posx = 10;
        posy = 833;

        TranspButt* aux = new TranspButt(posx+175,posy + 66, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+175,posy + 66 +28, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+175,posy + 66 +28*2, 175, 28);
        vec_selectors.push_back(aux);
        aux = new TranspButt(posx+175,posy + 66 +28*3, 175, 28);
        vec_selectors.push_back(aux);

        selector_de = new TranspButt(posx ,posy+200,30,30);
        selector_fr = new TranspButt(posx +44,posy+200,30,30);
    }
}

Infogui::~Infogui()
{

}

void Infogui::update()
{
    if(reloadThemeIcon == true)
    {
        reloadThemeIcon=false;

        switch(theme_selected)
        {
            case 1:{mainicon.loadImage("images/infogui/Mobilitaet_Icon.png");}break;
            case 2:{mainicon.loadImage("images/infogui/Wohnen_Icon.png");}break;
            case 3:{mainicon.loadImage("images/infogui/Energie_Icon.png");}break;
            case 4:{mainicon.loadImage("images/infogui/Konsum_Icon.png");}break;
        }
    }

}


void Infogui::draw()
{
    if(isActivated() == true)
    {
        if(turned==true)
        {
            ofPushMatrix();
            ofTranslate(posx + background.getWidth()/2 ,posy + background.getHeight()/2 );
            ofRotateZ(180);
            ofPushMatrix();
            ofTranslate(-posx-  background.getWidth()/2, -posy - background.getHeight()/2);
            // draw the image


            int value = 2;
            switch(dm->getSessionLangUser2())
            //switch(value)
            {
                case 1:
                {
                    txt_mobility = "MOBILIÄT";
                    txt_habitat = "WOHNEN";
                    txt_energy = "ENERGIE";
                    txt_consumption = "KONSUM";
                }break;
                case 2:
                {
                    txt_mobility = "MOBILITÉ";
                    txt_habitat = "HABITAT";
                    txt_energy = "ENERGIE";
                    txt_consumption = "CONSOMMATION";
                }break;
            }

            ofEnableAlphaBlending();
            ofSetColor(255,255,255,200);
            background.draw(posx,posy );
            ofDisableAlphaBlending();

            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+175, posy+44));
            text->setFont(myfont, 22);
            text->setText("AGORA");
            text->setTextColor(ofColor(255,255,255,200));
            text->draw();

            ofEnableAlphaBlending();

            ofDisableAlphaBlending();

            switch(theme_selected)
            {
                case 1:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+15,posy-16);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66, 185, 28);
                    minicube.draw(posx+148,posy + 66 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_mobility);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 2:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+25,posy-20);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_habitat);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 3:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+30,posy-22);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28*2, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28*2 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_energy);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 4:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+38,posy-22);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28*3, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28*3 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_consumption);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();


                }break;
                default:{}
            }

            ofEnableAlphaBlending();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+42,posy+100));
            text->setTextColor(ofColor(89,95,163,150));
            text->setFont(myfont, 30);
            //text->setText("68 %");

            text->setText(dm->getTotalCO2Impact(2) + "%   " );
            //text->setText("45 %   " );
            text->draw();
            ofDisableAlphaBlending();

            //SELECTORS DATA

            ofEnableAlphaBlending();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(2,1)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_mobility);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(2,2)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_habitat);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28*2 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(2,3)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28*2 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_energy);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28*3 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(2,4)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28*3 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_consumption);
            text->draw();

            switch(dm->getSessionLangUser2())
            {
                case 1:
                {
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont, 30);
                        text->setText("DE");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx+30,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont2, 30);
                        text->setText(" | ");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx + 44,posy+200));
                        text->setTextColor(ofColor(127,127,127,50));
                        text->setFont(myfont2, 30);
                        text->setText("FR");
                        text->draw();
                        ofDisableAlphaBlending();
                }break;
                case 2:
                {
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx,posy+200));
                        text->setTextColor(ofColor(127,127,127,50));
                        text->setFont(myfont2, 30);
                        text->setText("DE");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx+30,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont2, 30);
                        text->setText(" | ");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx +44,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont, 30);
                        text->setText("FR");
                        text->draw();
                        ofDisableAlphaBlending();
                }
            }

                ofPopMatrix();
            ofPopMatrix();
        }
        else //If the Gui is not turned
        {
            int value = 2;
            switch(dm->getSessionLangUser1())
            //switch(value)
            {
                case 1:
                {
                    txt_mobility = "MOBILIÄT";
                    txt_habitat = "WOHNEN";
                    txt_energy = "ENERGIE";
                    txt_consumption = "KONSUM";
                }break;
                case 2:
                {
                    txt_mobility = "MOBILITÉ";
                    txt_habitat = "HABITAT";
                    txt_energy = "ENERGIE";
                    txt_consumption = "CONSOMMATION";
                }break;
            }

            ofEnableAlphaBlending();
            ofSetColor(255,255,255,200);
            background.draw(posx,posy );
            ofDisableAlphaBlending();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+175, posy+44));
            text->setFont(myfont, 22);
            text->setText("AGORA");
            text->setTextColor(ofColor(255,255,255,200));
            text->draw();

            ofEnableAlphaBlending();

            ofDisableAlphaBlending();

            switch(theme_selected)
            {
                case 1:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+15,posy-16);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66, 185, 28);
                    minicube.draw(posx+148,posy + 66 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_mobility);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 2:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+25,posy-20);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_habitat);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 3:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+30,posy-22);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28*2, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28*2 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_energy);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();



                }break;
                case 4:
                {
                    ofEnableAlphaBlending();
                    mainicon.draw(posx+38,posy-22);
                    ofSetColor(67,191,232,100);
                    ofRect(posx+175,posy + 66 + 28*3, 185, 28);
                    minicube.draw(posx+148,posy + 66 +28*3 +2);
                    ofDisableAlphaBlending();
                    if(text != NULL){delete text;}
                    text = new ofxTextView(ofPoint(posx+100, posy+10));
                    text->setFont(myfont, 30);
                    text->setText(txt_consumption);
                    text->setTextColor(ofColor(255,255,255,200));
                    text->draw();


                }break;
                default:{}
            }

            ofEnableAlphaBlending();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+42,posy+100));
            text->setTextColor(ofColor(89,95,163,150));
            text->setFont(myfont, 30);
            //text->setText("68 %");

            text->setText(dm->getTotalCO2Impact(1) + "%   " );
            //text->setText("45 %   " );
            text->draw();
            ofDisableAlphaBlending();

            //SELECTORS DATA

            ofEnableAlphaBlending();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(1,1)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_mobility);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(1,2)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_habitat);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28*2 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(1,3)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28*2 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_energy);
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+174,posy + 66 +28*3 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(dm->getTotalCO2ImpactByTheme(1,4)+"% ");
            text->draw();
            if(text != NULL){delete text;}
            text = new ofxTextView(ofPoint(posx+220,posy + 66 +28*3 +8));
            text->setTextColor(ofColor(50,50,50,200));
            text->setFont(myfont2, 20);
            text->setText(txt_consumption);
            text->draw();

            switch(dm->getSessionLangUser1())
            {
                case 1:
                {
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont, 30);
                        text->setText("DE");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx+30,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont2, 30);
                        text->setText(" | ");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx + 44,posy+200));
                        text->setTextColor(ofColor(127,127,127,50));
                        text->setFont(myfont2, 30);
                        text->setText("FR");
                        text->draw();
                        ofDisableAlphaBlending();
                }break;
                case 2:
                {
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx,posy+200));
                        text->setTextColor(ofColor(127,127,127,50));
                        text->setFont(myfont2, 30);
                        text->setText("DE");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx+30,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont2, 30);
                        text->setText(" | ");
                        text->draw();
                        if(text != NULL){delete text;}
                        text = new ofxTextView(ofPoint(posx +44,posy+200));
                        text->setTextColor(ofColor(255,255,255,200));
                        text->setFont(myfont, 30);
                        text->setText("FR");
                        text->draw();
                        ofDisableAlphaBlending();
                }
            }
        }
    }
    else
    {

    }

}

void Infogui::checkSelectors(int x, int y)
{
    TranspButt* aux;
    for(int i = 0; i < vec_selectors.size(); i++)
    {
        aux =vec_selectors[i];
        if(aux->isclicked(x,y))
        {
            cout << "Selector clicked" << endl;
            reloadThemeIcon = true;
            theme_selected = i+1;

            if(!turned)
            {
                switch(theme_selected)
                {
                    case 1:{;dm->setUser1Cat(1);dm->loadSeasonUser(1,dm->getuser1_idtablet()); dm->resetNodesUser1();}break;
                    case 2:{;dm->setUser1Cat(2);dm->loadSeasonUser(1,dm->getuser1_idtablet()); dm->resetNodesUser1();}break;
                    case 3:{;dm->setUser1Cat(3);dm->loadSeasonUser(1,dm->getuser1_idtablet()); dm->resetNodesUser1();}break;
                    case 4:{;dm->setUser1Cat(4);dm->loadSeasonUser(1,dm->getuser1_idtablet()); dm->resetNodesUser1();}break;
                }
                return;
            }
            else
            {
                switch(theme_selected)
                {
                    case 1:{dm->setUser2Cat(1);dm->loadSeasonUser(2,dm->getuser2_idtablet()); dm->resetNodesUser2();}break;
                    case 2:{dm->setUser2Cat(2);dm->loadSeasonUser(2,dm->getuser2_idtablet()); dm->resetNodesUser2();}break;
                    case 3:{dm->setUser2Cat(3);dm->loadSeasonUser(2,dm->getuser2_idtablet()); dm->resetNodesUser2();}break;
                    case 4:{dm->setUser2Cat(4);dm->loadSeasonUser(2,dm->getuser2_idtablet()); dm->resetNodesUser2();}break;
                }
                return;
            }
        }
    }

    if(selector_de->isclicked(x,y))
    {
        //User 1 GUI
        if(turned != true)
        {
            cout << "DE selector" << endl;
            dm->setSessionLangUser1(1);
            dm->setTriggeredNode();
        }
        else
        {
            cout << "DE selector" << endl;
            dm->setSessionLangUser2(1);
            dm->setTriggeredNode2();
        }
    }
    if(selector_fr->isclicked(x,y))
    {
        //User 1 GUI
        if(turned != true)
        {
            cout << "Fr selector" << endl;
            dm->setSessionLangUser1(2);
            dm->setTriggeredNode();
        }
        else
        {
            cout << "Fr selector" << endl;
            dm->setSessionLangUser2(2);
            dm->setTriggeredNode2();
        }
    }
}
void Infogui::setInitSeason()
{
    init_season = ofGetElapsedTimef();
    active = true;
}

void Infogui::setActivated()
{
    active = true;
}

void Infogui::setNotActivated()
{
    active = false;
}

bool Infogui::isActivated()
{
    return active;
}
