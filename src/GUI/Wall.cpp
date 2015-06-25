#include "Wall.h"

#include "ofMain.h"
#include <ofGstUtils.h>
#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe
#include "DataManager/DataManager.h"
#include "ofxShaderManager.h"
#include "ofxTextView.h"
#include "ofxFboSlider.h"
#include "ofxSlideshowViewer.h"
#include "ofxPBOVideoPlayer.h"
#include "ofxVideoPlayerView.h"
#include "ofGstVideoPlayer.h"
#include "DataManager/Node.h"
#include "DataManager/MediaContent.h"
#include "DataManager/Gesture.h"
#include "GUI/Htmlstring.h"
#include "GUI/TranspButt.h"
Wall::Wall(DataManager* dm):ofxTouchViewRect ()
{
    init = true;
    init2 = true;
    dataman = dm;
    //dataman->loadTestNode();
    ofxShaderManager::GetInstance()->loadShaders("xmls/ShaderSettings.xml");
    p.loadImage( dataman->getPathCategory());
    view_width = 500;
    s = "Deutsch augue tortor dapibus odio, eget scelerisque ante metus ut nunc. Praesent auctor iaculis tortor, in placerat neque ultricies non. Donec faucibus luctus metus. Nullam sed viverra neque. Vivamus at congue lacus, et interdum turpis. Duis pretium fermentum elementum.";
    videoUser1 = new ofxVideoPlayerView();
    videoUser2 = new ofxVideoPlayerView();
    icon_close1.img.loadImage("images/touchview/ico_close.png");
    icon_close1.tp = new TranspButt(0,0,icon_close1.img.getWidth()/2,icon_close1.img.getHeight()/2+yoffset);
    icon_close1.tp->setNoActive();
    icon_close1.videotype = false;
    icon_close2.img.loadImage("images/touchview/ico_close.png");
    icon_close2.tp = new TranspButt(0,0,icon_close2.img.getWidth()/2,icon_close2.img.getHeight()/2+yoffset);
    icon_close2.tp->setNoActive();
    icon_close2.videotype = false;
    loadImageSlider("images/test.jpg");
    loadImageSlider2("images/test.jpg");
    imageSliderUser1->hide();
    imageSliderUser2->hide();
    yoffset = 24;
    yoffset2 = 24;

    textSliderUser1 = NULL;
    textSliderUser2 = NULL;
      //Fonts
    myfont = new ofxFontStash();
    myfont->setup("fonts/Klavika_TTF/Klavika-Light/Klavika-Light.ttf",2.0f);

    myfontbold = new ofxFontStash();
    myfontbold->setup("fonts/Klavika_TTF/Klavika-Medium/Klavika-Medium.ttf",2.0f);

    fbo1 = NULL;
    fbo2a = NULL;
    fbo2b = NULL;
}

Wall::~Wall()
{

}
void Wall::test(int lang_code)
{
    ofEnableAlphaBlending();

    //IMPORTANT: Reset all the temporary structures befor to be reused fo creating again the Viewer
    icoimagesUser1.clear();
    iconFBO auxicon;

    ofImage auximg;
    int imgpy;
    MediaContent* auxmc;

    int distanceLine = 10;
    int margin_right = 30;

    int w = 500;
    int h = 700;
    int fullheight;

    //Vector and pointer
    vector <ofxTextView*> vtext;
    ofxTextView* auxtext;
    ofxTextView* text;
    text = NULL;

    if(textSliderUser1 != NULL){delete textSliderUser1;}
    textSliderUser1 = new ofxFboSlider(ofPoint(500,300),w,h);
//ofxFboSlider* textSlider2 = new ofxFboSlider(ofPoint(1400,200),w,h);

    Gesture* activeGesture1;
    if(init==true)
    {
        init = false;
        activeGesture1 = dataman->getGestureOfNode(6);

    }
    else
    {
        Node* auxNode = dataman->getActiveNode();
        activeGesture1 = auxNode->getCurrGesture();
        activeGesture1->toString();
    }
    //Setting bold color acording with the topic
    ofColor color;
    switch(activeGesture1->getTheme())
    {
        case 1:{color.r = 188 ;color.g = 207 ; color.b = 0;}break;
        case 2:{color.r = 243 ;color.g = 146 ; color.b = 0;}break;
        case 3:{color.r = 255 ;color.g = 205 ; color.b = 28;}break;
        case 4:{color.r = 177 ;color.g = 65 ; color.b = 145;}break;
    }


    //---------------------------------------------------------------------
    //Generating all the strings
    text = new ofxTextView(ofPoint(20, 50));
    text->setFont(myfontbold, 20);
    text->setMultilineWidth(w-margin_right);
    if(dataman->getSessionLangUser1()==1){text->setText(activeGesture1->getName_de());}else{text->setText(activeGesture1->getName_fr());}
    text->setTextColor(color);
    fullheight =  text->getTextHeight() +70;
    vtext.push_back(text);


    //LOADING THE MAIN IMAGE OF THE GESTURE
    if(activeGesture1->getMainimage_path_de().compare("") != 0)
    {
        //cout << "There is a main image to draw" << endl;
        auximg.loadImage(dataman->getDatabaseIP()+activeGesture1->getMainimage_path_de());
        //auximg.loadImage(activeGesture1->getMainimage_path_de());
        int oh = auximg.getHeight();
        int ow = auximg.getWidth();
        auximg.resize(w, w*oh/ow) ; //(w*auximg.getHeight()/ auximg.getWidth())
        //cout << "New height " << w*oh/ow << endl;
        imgpy = fullheight;
        fullheight = fullheight + w*oh/ow + 30;
    }


    //2 - Overview
    /*
    fullheight =  fullheight + distanceLine;
    text = new ofxTextView(ofPoint(20,  fullheight));
    text->setFont(myfont, 22);
    text->setMultilineWidth(w-margin_right);
    text->setTextColor(ofColor(0,0,0));
    text->setText("Overview");

    fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
    vtext.push_back(text);
    */
    if(dataman->getSessionLangUser1()==1){htmlSpliter2(activeGesture1->getOverview_de());}else{htmlSpliter2(activeGesture1->getOverview_fr());}

    for(int i = 0; i < paragraph.size(); i++)
    {
        if(paragraph[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " ;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }

    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser1()==1)
    {
        if(activeGesture1->getSizevecOverview_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture1->getSizevecOverview_de() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecOverview_de(j))
                {

                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecOverview_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + auxicon.img.getWidth()/2+ 14;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);

            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
       if(activeGesture1->getSizevecOverview_fr() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture1->getSizevecOverview_fr() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecOverview_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false; }break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecOverview_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + auxicon.img.getWidth()/2+ 14;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }

    paragraph.clear();


    //3 - Details
    /*
    fullheight =  fullheight + distanceLine;
    text = new ofxTextView(ofPoint(20,  fullheight));
    text->setFont(myfont, 22);
    text->setMultilineWidth(w-margin_right);
    text->setTextColor(ofColor(0,0,0));
    text->setText("Details");
    fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
    vtext.push_back(text);
    */
    if(dataman->getSessionLangUser1()==1){htmlSpliter2(activeGesture1->getDetails_de());}else{htmlSpliter2(activeGesture1->getDetails_fr());}
    for(int i = 0; i < paragraph.size(); i++)
    {
        s += paragraph[i]->getText();
        if(paragraph[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph[i]->getText());

            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph[i]->getText());

            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
     if(dataman->getSessionLangUser1()==1)
     {
        if(activeGesture1->getSizevecDetails_de() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture1->getSizevecDetails_de() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecDetails_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecDetails_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
     }
     else
     {
        if(activeGesture1->getSizevecDetails_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture1->getSizevecDetails_fr() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecDetails_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                cout << "Details loop : case : " << activeGesture1->getTypeByIndexFromvecDetails_fr(j);
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecDetails_fr(j);
                cout << auxicon.pathcontent << endl;
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
     }
     paragraph.clear();
    //4 - Products
    //if((dataman->getSessionLangUser1()==1&&activeGesture1->getProducts_de()!="")||(dataman->getSessionLangUser1()==2 && activeGesture1->getProducts_fr()!=""))

        fullheight =  fullheight + distanceLine;
        text = new ofxTextView(ofPoint(20,  fullheight));
        text->setFont(myfont, 22);
        text->setMultilineWidth(w-margin_right);
        text->setTextColor(ofColor(0,0,0));
        if(dataman->getSessionLangUser1()==1){
            if(activeGesture1->getProducts_de().compare("")==0){text->setText(" ");}else{text->setText("Produkt");}
        }else{
            if(activeGesture1->getProducts_fr().compare("")==0){text->setText(" ");}else{text->setText("Produit");}
        }
        fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
        vtext.push_back(text);


    if(dataman->getSessionLangUser1()==1){htmlSpliter2(activeGesture1->getProducts_de());}else{htmlSpliter2(activeGesture1->getProducts_fr());}
    for(int i = 0; i < paragraph.size(); i++)
    {
        s += paragraph[i]->getText();
        if(paragraph[i]->isBold())
        {
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
            if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser1()==1)
    {
        if(activeGesture1->getSizevecProducts_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture1->getSizevecProducts_de() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecProducts_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecProducts_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2 ;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
        if(activeGesture1->getSizevecProducts_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture1->getSizevecProducts_fr() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecProducts_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecProducts_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2 ;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    paragraph.clear();
    //5 - Provider
    //if((dataman->getSessionLangUser1()==1&&activeGesture1->getProvider_de()!="")||(dataman->getSessionLangUser1()==2 && activeGesture1->getProvider_fr()!=""))

        fullheight =  fullheight + distanceLine;
        text = new ofxTextView(ofPoint(20,  fullheight));
        text->setFont(myfont, 22);
        text->setMultilineWidth(w-margin_right);
        text->setTextColor(ofColor(0,0,0));
        if(dataman->getSessionLangUser1()==1){
            if(activeGesture1->getProvider_de().compare("")==0){text->setText(" ");}else{text->setText("Anbieter");}
        }
        else{
            if(activeGesture1->getProvider_fr().compare("")==0){text->setText(" ");}else{text->setText("Fournisseur");}
        }
        fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
        vtext.push_back(text);

    if(dataman->getSessionLangUser1()==1){htmlSpliter2(activeGesture1->getProvider_de());} else {htmlSpliter2(activeGesture1->getProvider_fr());}
    for(int i = 0; i < paragraph.size(); i++)
    {
        s += paragraph[i]->getText();
        if(paragraph[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser1()==1)
    {
        if(activeGesture1->getSizevecProvider_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture1->getSizevecProvider_de() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecProvider_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecProvider_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 +40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
        if(activeGesture1->getSizevecProvider_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture1->getSizevecProvider_fr() ; j++)
            {
                switch(activeGesture1->getTypeByIndexFromvecProvider_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture1->getPathByIndexFromvecProvider_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser1.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 +40;
            //if(auxicon.tp != NULL){delete auxicon.tp; }
            size1 = fullheight;
        }
    }
    paragraph.clear();

    //Mappping All the data into a Fbo

    fbo1 = new ofFbo();
    fbo1->allocate(w,fullheight +40,GL_RGBA);
    fbo1->begin();
        ofClear(255,255,255,255);
        //ofSetColor(255,255,255,255);
        for(int i= 0 ; i  < vtext.size();i++)
        {
            vtext[i]->draw();
            if(i == 0)
            {
                auximg.draw(0,  imgpy, auximg.getWidth(), auximg.getHeight());
            }
            //Locating Icon images stored in icoimagesUser1FBO inside the FBO

            for(int j=0; j < icoimagesUser1.size() ; j++)
            {
                if(i == icoimagesUser1[j].index)
                {
                   icoimagesUser1[j].img.draw(icoimagesUser1[j].posx, icoimagesUser1[j].posy, 50,50);
                }
            }
        }
    fbo1->end();
    //End fbo Mapping
    textSliderUser1->setFbo(fbo1);
    if(fbo1->getHeight() > h)
    {
        textSliderUser1->setSize(w,h);
        textSliderUser1->setShowBottomGradient(true);
        textSliderUser1->setGradientHeight(75);
        size1 = fbo1->getHeight();
        dataman->Slider1LastPos = 0;
    }
    else
    {
        textSliderUser1->setSize(w,fbo1->getHeight());
        textSliderUser1->desactivate();
        textSliderUser1->setShowBottomGradient(false);
        size1 = fbo1->getHeight();
    }
    addChild(textSliderUser1);
    icon_close1.tp->setNoActive();
    delete text;text = NULL;
}
//---------------------------------------------------------------
void Wall::test2(int lang)
{
    //IMPORTANT: Reset all the temporary structures befor to be reused fo creating again the Viewer
    icoimagesUser2.clear();
    icon_close2.tp->setNoActive();

    iconFBO auxicon;
    ofImage auximg;
    MediaContent* auxmc;
    int imgpy = 0;
    int distanceLine = 10;
    int margin_right = 30;
    int w = 500;
    int h = 700;
    int fullheight;
    //Vector and pointer
    vector <ofxTextView*> vtext;
    ofxTextView* auxtext;
    ofxTextView* text;
    text = NULL;
    //Fonts
    /*
    ofxFontStash* myfont = new ofxFontStash();
    myfont->setup("fonts/Klavika_TTF/Klavika-Light/Klavika-Light.ttf",2.0f);
    ofxFontStash* myfontbold = new ofxFontStash();
    myfontbold->setup("fonts/Klavika_TTF/Klavika-Medium/Klavika-Medium.ttf",2.0f);
    */

    if(textSliderUser2 != NULL){delete textSliderUser2;}
    textSliderUser2 = new ofxFboSlider(ofPoint(1000,300),w,h);


    Gesture* activeGesture2;

    if(init2 ==true)
    {
        init2 = false;
        activeGesture2 = dataman->getGestureOfNode(6);
    }
    else
    {
        Node* auxNode = dataman->getActiveNode2();
        activeGesture2 = auxNode->getCurrGesture();
        activeGesture2->toString();
    }
    //Setting bold color acording with the topic
    ofColor color;
    switch(activeGesture2->getTheme())
    {
        case 1:{color.r = 188 ;color.g = 207 ; color.b = 0;}break;
        case 2:{color.r = 243 ;color.g = 146 ; color.b = 0;}break;
        case 3:{color.r = 255 ;color.g = 205 ; color.b = 28;}break;
        case 4:{color.r = 177 ;color.g = 65 ; color.b = 145;}break;
    }
    //---------------------------------------------------------------------
    //Generating all the strings

    text = new ofxTextView(ofPoint(20, 50));
    text->setFont(myfontbold, 20);
    text->setMultilineWidth(w-margin_right);
    if(dataman->getSessionLangUser2()==1){text->setText(activeGesture2->getName_de());}else{text->setText(activeGesture2->getName_fr());}
    text->setTextColor(color);
    fullheight =  text->getTextHeight() +70;
    vtext.push_back(text);

    //LOADING THE MAIN IMAGE OF THE GESTURE
    if(activeGesture2->getMainimage_path_de().compare("") != 0)
    {
        auximg.loadImage(dataman->getDatabaseIP()+activeGesture2->getMainimage_path_de());
        int oh = auximg.getHeight();
        int ow = auximg.getWidth();
        auximg.resize(w, w*oh/ow) ;
        imgpy = fullheight;
        fullheight = fullheight + w*oh/ow + 30;
    }

    //2 - Overview
    if(dataman->getSessionLangUser2()==1){htmlSpliter2U2(activeGesture2->getOverview_de());}else{htmlSpliter2U2(activeGesture2->getOverview_fr());}

    for(int i = 0; i < paragraph2.size(); i++)
    {
        if(paragraph2[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " ;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser2()==1)
    {
        if(activeGesture2->getSizevecOverview_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture2->getSizevecOverview_de() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecOverview_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false; }break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecOverview_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + auxicon.img.getWidth()/2+ 14;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
       if(activeGesture2->getSizevecOverview_fr() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture2->getSizevecOverview_fr() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecOverview_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false; }break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecOverview_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + auxicon.img.getWidth()/2+ 14;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    paragraph2.clear();
    //3 - Details
    if(dataman->getSessionLangUser2()==1){htmlSpliter2U2(activeGesture2->getDetails_de());}else{htmlSpliter2U2(activeGesture2->getDetails_fr());}
    for(int i = 0; i < paragraph2.size(); i++)
    {
        if(paragraph2[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
     if(dataman->getSessionLangUser2()==1)
     {
        if(activeGesture2->getSizevecDetails_de() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture2->getSizevecDetails_de() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecDetails_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecDetails_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
     }
     else
     {
        if(activeGesture2->getSizevecDetails_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture2->getSizevecDetails_fr() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecDetails_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                cout << "Details loop : case : " << activeGesture2->getTypeByIndexFromvecDetails_fr(j);
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecDetails_fr(j);
                cout << auxicon.pathcontent << endl;
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
     }
     paragraph2.clear();
     //4 - Products

    fullheight =  fullheight + distanceLine;
    text = new ofxTextView(ofPoint(20,  fullheight));
    text->setFont(myfont, 22);
    text->setMultilineWidth(w-margin_right);
    text->setTextColor(ofColor(0,0,0));
    if(dataman->getSessionLangUser2()==1){
        if(activeGesture2->getProducts_de().compare("")!=0){
            text->setText("Produkt");
        }
        else{
            text->setText("");
        }
    }
    if(dataman->getSessionLangUser2()==2){
         if(activeGesture2->getProducts_fr().compare("")!=0){
             text->setText("Produit");
         }
         else{
             text->setText("");
         }
    }
    fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
    vtext.push_back(text);


    if(dataman->getSessionLangUser2()==1){htmlSpliter2U2(activeGesture2->getProducts_de());}else{htmlSpliter2U2(activeGesture2->getProducts_fr());}
    for(int i = 0; i < paragraph.size(); i++)
    {
        if(paragraph2[i]->isBold())
        {
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser2()==1)
    {
        if(activeGesture2->getSizevecProducts_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture2->getSizevecProducts_de() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecProducts_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecProducts_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2 ;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
        if(activeGesture2->getSizevecProducts_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture2->getSizevecProducts_fr() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecProducts_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");   auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png"); auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png"); auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecProducts_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2 ;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 + 40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    paragraph2.clear();
    //5 - Provider
    fullheight =  fullheight + distanceLine;
    text = new ofxTextView(ofPoint(20,  fullheight));
    text->setFont(myfont, 22);
    text->setMultilineWidth(w-margin_right);
    text->setTextColor(ofColor(0,0,0));
    if(dataman->getSessionLangUser2()==1){
        if(activeGesture2->getProvider_de().compare("")!=0){
            text->setText("Anbieter");
        }
        else{
             text->setText("");
        }
    }
    if(dataman->getSessionLangUser2()==2){
        if(activeGesture2->getProvider_fr().compare("")!=0){
            text->setText("Fournisseur");
        }
        else{
            text->setText("");
        }
    }
    fullheight =  fullheight + text->getTextHeight() + distanceLine+15;
    vtext.push_back(text);

    if(dataman->getSessionLangUser2()==1){htmlSpliter2U2(activeGesture2->getProvider_de());} else {htmlSpliter2U2(activeGesture2->getProvider_fr());}
    for(int i = 0; i < paragraph.size(); i++)
    {
        if(paragraph2[i]->isBold())
        {
            //cout << "is bold" << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 20);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(color);
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
        else
        {
            //cout << "is not bold: " << endl;
            text = new ofxTextView(ofPoint(20,  fullheight));
            text->setFont(myfont, 16);
            text->setMultilineWidth(w-margin_right);
            text->setTextColor(ofColor(0,0,0));
            text->setText(paragraph2[i]->getText());
            fullheight =  fullheight + text->getTextHeight() + distanceLine;
            vtext.push_back(text);
        }
    }
    //Media Content Assigned to the paragraph
    if(dataman->getSessionLangUser2()==1)
    {
        if(activeGesture2->getSizevecProvider_de() > 0)
        {
            int fullwidth = 20;
            for(int j = 0; j < activeGesture2->getSizevecProvider_de() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecProvider_de(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecProvider_de(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 +40;
             if(auxicon.tp != NULL){delete auxicon.tp; }
        }
    }
    else
    {
        if(activeGesture2->getSizevecProvider_fr() > 0)
        {
            int fullwidth=20;
            for(int j = 0; j < activeGesture2->getSizevecProvider_fr() ; j++)
            {
                switch(activeGesture2->getTypeByIndexFromvecProvider_fr(j))
                {
                    case 1:{auxicon.img.loadImage("images/touchview/ico_pdf.png");  auxicon.videotype = false;}break;
                    case 2:{auxicon.img.loadImage("images/touchview/ico_video.png");auxicon.videotype = true; }break;
                    case 3:{auxicon.img.loadImage("images/touchview/ico_image.png");auxicon.videotype = false;}break;
                }
                auxicon.index = vtext.size();
                auxicon.pathcontent = activeGesture2->getPathByIndexFromvecProvider_fr(j);
                auxicon.posx = fullwidth;
                auxicon.posy = fullheight + 20;
                auxicon.tp = new TranspButt(0,0, auxicon.img.getWidth()/2,auxicon.img.getHeight()/2);
                fullwidth = fullwidth + 14 + auxicon.img.getWidth()/2;
                //fullheight =  fullheight + 20 + auxicon.img.getHeight()/2;
                if(fullwidth+auxicon.img.getWidth()/2 >= w)
                {
                    fullwidth = 20; fullheight = fullheight + auxicon.img.getWidth()/2 + 14;
                }
                icoimagesUser2.push_back(auxicon);
            }
            fullheight = fullheight + auxicon.img.getWidth()/2 +40;
             if(auxicon.tp != NULL){delete auxicon.tp; }

        }
    }
    paragraph2.clear();

    //Mappping All the data into a Fbo
    if(fbo2a != NULL){delete fbo2a;}
    fbo2a = new ofFbo();
    fbo2a->allocate(w,fullheight +40,GL_RGBA);
    fbo2a->begin();



        ofClear(255,255,255,255);
        //ofSetColor(255,255,255,255);
        for(int i= 0 ; i  < vtext.size();i++)
        {
            vtext[i]->draw();
            if(i == 0)
            {
                auximg.draw(0,  imgpy, auximg.getWidth(), auximg.getHeight());
            }
            //Locating Icon images stored in icoimagesUser1FBO inside the FBO

            for(int j=0; j < icoimagesUser2.size() ; j++)
            {
                if(i == icoimagesUser2[j].index)
                {
                   icoimagesUser2[j].img.draw(icoimagesUser2[j].posx, icoimagesUser2[j].posy, 50,50);
                }
            }
        }
    fbo2a->end();
    auximg.clear();
    //if(fbo2b != NULL){delete fbo2b;}
    fbo2b = new ofFbo();
    fbo2b->allocate(w,fullheight +40,GL_RGBA);
    fbo2b->begin();
        ofPushMatrix();
        ofTranslate(fbo2a->getWidth()/2 , + fbo2a->getHeight()/2 );
        ofRotateZ(180);
        ofPushMatrix();
        ofTranslate(-fbo2a->getWidth()/2,  - fbo2a->getHeight()/2);
        ofClear(255,255,255,255);
        fbo2a->draw(0,0);
        ofPopMatrix();
        ofPopMatrix();
    fbo2b->end();

    //End fbo Mapping
    textSliderUser2->setFbo(fbo2b);
    if(fbo2b->getHeight() > h) {
        textSliderUser2->setSize(w,h);
        textSliderUser2->setGradientHeight(75);
        textSliderUser2->setShowBottomGradient(true);
        setRelativePosTextSliderUser2((fbo2b->getHeight()-h)*-1);
        dataman->Slider2LastPos = (fbo2b->getHeight()-h)*-1;
    }
    else{
        textSliderUser2->setSize(w,fbo2b->getHeight());
        textSliderUser2->desactivate();
        textSliderUser2->setShowBottomGradient(false);
    }
    addChild(textSliderUser2);
    size2 = fbo2b->getHeight();
    //Flipping positon relatives of the buttons
    for(int i=0; i<icoimagesUser2.size(); i++)
    {
        icoimagesUser2[i].posx = w - (icoimagesUser2[i].posx + icoimagesUser2[i].img.getWidth()/2);
        icoimagesUser2[i].posy = fbo2b->getHeight() - (icoimagesUser2[i].posy + icoimagesUser2[i].img.getHeight()/2);

        cout << "posx_"<< icoimagesUser2[i].posx << " posy_"<< icoimagesUser2[i].posy <<endl;
    }
    icon_close2.tp->setNoActive();


    //delete text;text = NULL;
}
//---------------------------------------------------------------
void Wall::loadImageSlider(string path)
{
    ofImage img;
    img.loadImage(path);
    int w = 500;
    int h = 700;
    icon_close1.tp->setActive();
    int oh = img.getHeight();
    int ow = img.getWidth();
    img.resize(w, w*oh/ow);
    imageSliderUser1 = new ofxFboSlider(ofPoint(0,0),w,w*oh/ow);
    ofFbo* fbo = new ofFbo();
    fbo->allocate(w,w*oh/ow,GL_RGBA);
    fbo->begin();
        ofClear(255,255,255,255);
        img.draw(0,0,w,w*oh/ow);
        icon_close1.img.draw(w-icon_close1.img.getWidth()/2,0,icon_close1.img.getWidth()/2.0,icon_close1.img.getHeight()/2.0);
    fbo->end();

    imageSliderUser1->setFbo(fbo);
    if(fbo->getHeight() > h)
    {
        imageSliderUser1->setShowBottomGradient(true);
        imageSliderUser1->setSize(w,h);
        imageSliderUser1->setGradientHeight(75);
        sizeimgsld1 = fbo->getHeight();
    }
    else
    {
        imageSliderUser1->setSize(w,fbo->getHeight());
        imageSliderUser1->desactivate();
        imageSliderUser1->setShowBottomGradient(false);
        sizeimgsld1 = fbo->getHeight();
    }
    addChild(imageSliderUser1);
}
//---------------------------------------------------------------
void Wall::loadImageSlider2(string path)
{
    ofImage img;
    img.loadImage(path);
    int w = 500;
    int h = 700;
    icon_close2.tp->setActive();

    int oh = img.getHeight();
    int ow = img.getWidth();
    img.resize(w, w*oh/ow);

    imageSliderUser2 = new ofxFboSlider(ofPoint(1920,0),w,w*oh/ow);
    ofFbo* fbo = new ofFbo();
    fbo->allocate(w,w*oh/ow,GL_RGBA);

    fbo->begin();
        ofClear(255,255,255,255);
        img.draw(0,0,w,w*oh/ow);
    fbo->end();

    ofFbo* fbo2 = new ofFbo();
    fbo2->allocate(w,w*oh/ow,GL_RGBA);
    fbo2->begin();
        ofPushMatrix();
        ofTranslate(fbo->getWidth()/2 , + fbo->getHeight()/2 );
        ofRotateZ(180);
        ofPushMatrix();
        ofTranslate(-fbo->getWidth()/2,  - fbo->getHeight()/2);
        ofClear(255,255,255,255);
        fbo->draw(0,0);
        ofPopMatrix();
        ofPopMatrix();
    fbo2->end();

    imageSliderUser2->setFbo(fbo2);
    if(fbo2->getHeight()>h){
        imageSliderUser2->setSize(w,h);
        setRelativePosImageSliderUser2((fbo2->getHeight()-h)*-1);
        dataman->SliderImage2LastPos = (fbo2->getHeight()-h)*-1;
        imageSliderUser2->setGradientHeight(75);
        imageSliderUser2->setShowBottomGradient(true);
        sizeimgsld2 = fbo2->getHeight();
    }
    else{
        imageSliderUser2->setSize(w,fbo2->getHeight());
        imageSliderUser2->desactivate();
        imageSliderUser2->setShowBottomGradient(false);
        sizeimgsld2 = fbo2->getHeight();
    }
    addChild(imageSliderUser2);
}

//---------------------------------------------------------------
void Wall::update()
{
    videoUser1->update();
    videoUser2->update();

    Node* aux;
    TranspButt* auxtb;
    aux = dataman->getActiveNode();

    Node* aux2;
    TranspButt* auxtb2;
    aux2 = dataman->getActiveNode2();

    if(aux2 == NULL)
    {
        videoUser2->stop();
        imageSliderUser2->hide();
        textSliderUser2->hide();
    }
    else{
        //Update position of Window
        if(size2 <= 700)
        {
            yoffset2 = -610 + (700-size2);
        }
        else
        {
             yoffset2 = -610;

        }
        textSliderUser2->setAbsPosition(aux2->getPosx()- (view_width+10),aux2->getPosy() +yoffset2);
        int voffset;if(imageSliderUser2->getHeight() > 700){voffset =700;}else{voffset = imageSliderUser2->getHeight();}
        imageSliderUser2->setAbsPosition(aux2->getPosx() - (imageSliderUser2->getWidth()+10),aux2->getPosy() - voffset + 90 );
        videoUser2->setAbsPosition(aux2->getPosx()- (view_width+10),aux2->getPosy() - videoUser2->getHeight()+90);
        //UpdatePosition of Buttons
        TranspButt* tb;
        for(int i=0; i < icoimagesUser2.size() ; i++)
        {
            tb = icoimagesUser2[i].tp;
            tb->setpos(aux2->getPosx()- view_width+10 + icoimagesUser2[i].posx , aux2->getPosy() + yoffset2 + icoimagesUser2[i].posy  + textSliderUser2->getYSliderPositionRelative());// + textSliderUser2->getYSliderPositionRelative()
            if(tb->getPosy() > (aux2->getPosy()+yoffset2)  && tb->getPosy() < aux2->getPosy()+90){
                if(!icon_close2.tp->isActive()){tb->setActive();}
            }
            else{
                tb->setNoActive();
            }
        }
        if(icon_close2.videotype == true)
        {
            icon_close2.tp->setpos(aux2->getPosx() - (view_width + 10),aux2->getPosy()+90- icon_close2.img.getHeight()/2);
        }
        else{
            icon_close2.tp->setpos(aux2->getPosx() - (imageSliderUser2->getWidth()+10), aux2->getPosy()+90- icon_close2.img.getHeight()/2);
        }

        if(dataman->getTriggeredNode2())
        {
            dataman->setNotTriggeredNode2();
            aux2->toString();
            icon_close2.videotype = false;
            videoUser2->stop();
            removeChild(textSliderUser2);
            removeChild(imageSliderUser2);
            test2(1);
        }
    }
    if(aux == NULL)
    {
        //cout << "no activeNode" << endl;
        videoUser1->stop();
        imageSliderUser1->hide();
        textSliderUser1->hide();
    }
    else
    {
        //Update positions of the buttons
        TranspButt* tb;
        for(int i=0; i < icoimagesUser1.size() ; i++)
        {
            tb = icoimagesUser1[i].tp;

            tb->setpos(aux->getPosx()+120+icoimagesUser1[i].posx,aux->getPosy()+icoimagesUser1[i].posy + textSliderUser1->getYSliderPositionRelative() + yoffset);

            if(tb->getPosy() > aux->getPosy() && tb->getPosy() < aux->getPosy()+700)
            {
                if(!icon_close1.tp->isActive()){tb->setActive();}
            }
            else
            {
                tb->setNoActive();
            }
        }
        //icon_close1.tp->setpos( aux->getPosx() + 120+  (videoUser1->getWidth() - icon_close1.img.getWidth()/2.0 )  ,aux->getPosy());

        if(icon_close1.videotype == true)
        {
                icon_close1.tp->setpos( aux->getPosx() + 120+  (videoUser1->getWidth() - icon_close1.img.getWidth()/2.0 )  ,aux->getPosy()+yoffset);
        }
        else
        {
                icon_close1.tp->setpos(aux->getPosx() + 120 + ( view_width - icon_close1.img.getWidth()/2.0), aux->getPosy()+yoffset);
        }


        icon_close1.posx = aux->getPosx() + 120 +  (videoUser1->getWidth() - icon_close1.img.getWidth()/2.0 );
        icon_close1.posy = aux->getPosy() + yoffset;

        if(dataman->getTriggeredNode()==true)//swaping the content with the new one
        {
            dataman->setNotTriggeredNode();
            aux->toString();
            icon_close1.videotype = false;
            videoUser1->stop();
            removeChild(textSliderUser1);
            removeChild(imageSliderUser1);
            test(1);
        }
        //m_children[0]->unhide();
        textSliderUser1->setAbsPosition(aux->getPosx()+120,aux->getPosy()+yoffset);
        imageSliderUser1->setAbsPosition(aux->getPosx()+120,aux->getPosy()+yoffset);

        videoUser1->setAbsPosition(aux->getPosx()+120,aux->getPosy()+yoffset);
    }

}
//-------------------------------------------------------------------------
void Wall::swapContent()
{

}

//-------------------------------------------------------------------------
void Wall::draw()
{
    ofNoFill();
    ofSetColor(255,255,255,255);
    //Drawing the background
    drawBackground();

    dataman->drawBgnodes();

    //Drawing all the nodes
    drawNodes();

    ofxTouchView::draw();


    //Video Drawing
    if(!videoUser1->isVideoPlaying()){videoUser1->draw();}
    ofPoint p =  videoUser2->getAbsPosition();
    if(!videoUser2->isVideoPlaying()){
        //cout << p.x << " " <<p.y << endl;
        videoUser2->draw();
    }
    //Buttons Drawing
    if(dataman->getActiveNode() != NULL){
        if(icon_close1.videotype == true){
            if(icon_close1.tp ->isActive())
            {
                icon_close1.img.draw(icon_close1.posx,icon_close1.posy,icon_close1.img.getWidth()/2,icon_close1.img.getHeight()/2);
            }
        }
    }
    if(dataman->getActiveNode2() != NULL){
        if(icon_close2.tp->isActive()){
            if(icon_close2.videotype ==true){
                icon_close2.img.draw(dataman->getActiveNode2()->getPosx() - (view_width + 10),dataman->getActiveNode2()->getPosy()+90- icon_close2.img.getHeight()/2,icon_close2.img.getHeight()/2,icon_close2.img.getHeight()/2);
            }
            else{
                icon_close2.img.draw(dataman->getActiveNode2()->getPosx() - (imageSliderUser2->getWidth()+10), dataman->getActiveNode2()->getPosy()+90- icon_close2.img.getHeight()/2,icon_close2.img.getHeight()/2,icon_close2.img.getHeight()/2);
            }
        }
    }
}

//-------------------------------------------------------------------------
void Wall::drawBackground()
{
    //ofLoadImage(p, dataman->getPathCategory());

    //p.allocate(1920, 1080, OF_IMAGE_COLOR);
    p.draw(0,0,1920,1080);

}


//-------------------------------------------------------------------------
void Wall::drawBezier()
{
/*
    int posxNode;
    int posyNode;

    posxNode = ofGetAppPtr()->mouseX;
    posyNode = ofGetAppPtr()->mouseY;


    //cout << ofGetWindowWidth() << endl;

    float value = sin(ofGetElapsedTimef());
    value = 10 * value;

    float value2 = sin(ofGetElapsedTimef()+200.0);
    value2 = 10* value2;

    output.noFill();
    output.setLineWidth(3.0f);
    ofSetColor(255,255,255,125);
    ofEnableAlphaBlending();
    //output.setColor(255,255,255);
    output.bezier(ofGetWindowWidth()/16, ofGetWindowHeight() - ofGetWindowHeight()/9,
                  ofGetWindowWidth()/16 + 100 +value, ofGetWindowHeight() - ofGetWindowHeight()/9,
                  value2, posyNode,
                  posxNode, posyNode);

*/
}

//-------------------------------------------------------------------------
void Wall::drawNodes()
{
       dataman->drawNodes();
}


//--------------------------------------------------------------
void Wall::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void Wall::mouseDragged(int x, int y, int button)
{
   //if(!m_usemouse) return;
    ofxTouchEvent e(x,y);
    ofxTouchView::mouseDragMaster(e);
}

//--------------------------------------------------------------
void Wall::mousePressed(int x, int y, int button)
{
    ofxTouchEvent e(x,y);
    //std::cout << "mouse pressed e: " << e.m_x << " " << e.m_y << std::endl;
    ofxTouchView::mouseDownMaster(e);
}

//--------------------------------------------------------------
void Wall::mouseReleased(int x, int y, int button)
{
    //if(!m_usemouse) return;
    ofxTouchEvent e(x,y);
    ofxTouchView::mouseUpMaster(e);

    TranspButt* tb;
    int py;
    bool clic1 = false;
    bool clic2 = false;
    for(int i=0; i < icoimagesUser1.size() ; i++)
    {
        tb = icoimagesUser1[i].tp;
        if(tb->isclicked(x,y))
        {
            clic1 = true;
            tb->toString();
            py = textSliderUser1->getYSliderPositionRelative();
            //cout << "Relative FBO position " << py<< endl;

            if(textSliderUser1->isHidden())
            {
                textSliderUser1->unhide();
                imageSliderUser1->hide();
            }
            else
            {
                string s = dataman->getPathSystem();
                s += icoimagesUser1[i].pathcontent;
                removeChild(imageSliderUser1);
                if( icoimagesUser1[i].videotype == true)
                {
                    ofVideoPlayer myPlayer;
                    myPlayer.loadMovie(s); int vw = myPlayer.getWidth();int vh = myPlayer.getHeight();
                    videoUser1->load(s, view_width,view_width*vh/vw);
                    videoUser1->play();
                    videoUser1->loadPlayPauseButton();
                    icon_close1.videotype = true;
                    icon_close1.tp->setActive();
                }
                else
                {
                    loadImageSlider(s);
                    icon_close1.tp->setActive();
                }
                textSliderUser1->hide();
                imageSliderUser1->unhide();
            }
        }
    }
    if(clic1==true){for(int i=0; i < icoimagesUser1.size() ; i++){tb = icoimagesUser1[i].tp;tb->setNoActive();}}
    //Checking the buttons in the second User
    for(int i=0; i < icoimagesUser2.size() ; i++)
    {
         tb = icoimagesUser2[i].tp;
         if(tb->isclicked(x,y))
         {
            cout << "clic" << endl;
            clic2 = true;
            if(textSliderUser2->isHidden()){
                textSliderUser2->unhide();
                imageSliderUser2->hide();
            }
            else{
                removeChild(imageSliderUser2);
                if( icoimagesUser2[i].videotype == true){
                    string s = "/home/fribourg/Desktop/v180";
                    s += icoimagesUser2[i].pathcontent;
                    //s += "/cleverRR.mp4";
                    ofVideoPlayer myPlayer;
                    cout << "[LRV] " << s << cout;
                    myPlayer.loadMovie(s); int vw = myPlayer.getWidth();int vh = myPlayer.getHeight();
                    videoUser2->load(s,view_width,view_width*vh/vw);
                    videoUser2->play();
                    videoUser2->loadPlayPauseButton();
                    icon_close2.videotype = true;
                    icon_close2.tp->setActive();
                }
                else{
                    string s = dataman->getPathSystem();
                    s += icoimagesUser2[i].pathcontent;
                    loadImageSlider2(s);
                    icon_close2.tp->setActive();
                }
                textSliderUser2->hide();
                imageSliderUser2->unhide();
            }
         }
    }
    if(clic2==true){for(int i=0; i < icoimagesUser2.size() ; i++){tb = icoimagesUser2[i].tp;tb->setNoActive();}}


    //Checking close Buttons
    if(icon_close1.tp->isclicked(x,y)){
        if(icon_close1.videotype == true){
            icon_close1.videotype = false;
            videoUser1->stop();
        }
        textSliderUser1->unhide();
        imageSliderUser1->hide();
        icon_close1.tp->setNoActive();
        //Reactivate all the buttons
        for(int i=0; i < icoimagesUser1.size();i++){tb = icoimagesUser1[i].tp;tb->setActive();}
    }
    if(icon_close2.tp->isclicked(x,y)){
        if(icon_close2.videotype == true){
            icon_close2.videotype = false;
            videoUser2->stop();
        }
        textSliderUser2->unhide();
        imageSliderUser2->hide();
        icon_close2.tp->setNoActive();
        //Reactivate all the buttons
        for(int i=0; i < icoimagesUser2.size();i++){tb = icoimagesUser2[i].tp;tb->setActive();}
    }
}

//--------------------------------------------------------------
void Wall::htmlSpliter(string s)
{
    Htmlstring* auxhtml;
    bool readline = false;
    bool bold = false;
    string buffer = "";
    string buffer2 = "";
    int i=0;

    for(int i=0; i < s.length(); i++)
    {
        if(s[i]=='\n' || i == s.length()-1 )
        {
            int j = 0;
            if(buffer[j]=='<' &&  buffer[j+1]=='p' &&  buffer[j+2]=='>' &&  buffer[j+3]=='<')
            {
                if(buffer[j+4]=='b')
                {
                    for(int k = 6 ; k < buffer.length()-8;k++)
                    {
                        buffer2.push_back(buffer[k]);
                    }
                    //cout << buffer2 << endl;
                    buffer2.push_back('\n');
                    auxhtml =  new Htmlstring(buffer2, true);
                    paragraph.push_back(auxhtml);

                    buffer2.clear();
                }
                else
                {
                    auxhtml =  new Htmlstring("\n", false);
                    paragraph.push_back(auxhtml);
                    buffer2.clear();
                }
            }
            else
            {
                 for(int k=3; k < buffer.length()-4 ; k++ )
                 {
                     buffer2.push_back(buffer[k]);
                 }
                 buffer2.push_back('\n');
                 auxhtml =  new Htmlstring(buffer2, false);
                 paragraph.push_back(auxhtml);
                 buffer2.clear();
            }buffer.clear();
        }
        else
        {
            buffer.push_back(s[i]);
        }
    }
}
//--------------------------------------------------------
int Wall::getRelativePosTextSliderUser1(){
    return textSliderUser1->getYSliderPositionRelative();
}
//--------------------------------------------------------
int Wall::getRelativePosTextSliderUser2(){
    return textSliderUser2->getYSliderPositionRelative();
}
//--------------------------------------------------------
int Wall::getRelativePosImageSliderUser1(){
    return imageSliderUser1->getYSliderPositionRelative();
}
//--------------------------------------------------------
int Wall::getRelativePosImageSliderUser2(){
    return imageSliderUser2->getYSliderPositionRelative();
}
//--------------------------------------------------------
void Wall::setRelativePosTextSliderUser1(int vy){
    if(size1 >700){textSliderUser1->setYSliderPositionRelative(vy);}
}
//--------------------------------------------------------
void Wall::setRelativePosTextSliderUser2(int vy){
    if(size2 >700){textSliderUser2->setYSliderPositionRelative(vy);}
}
//--------------------------------------------------------
void Wall::setRelativePosImageSliderUser1(int vy){
    if(sizeimgsld1 > 700){imageSliderUser1->setYSliderPositionRelative(vy);}
}
//--------------------------------------------------------
void Wall::setRelativePosImageSliderUser2(int vy){
    if(sizeimgsld2 > 700){imageSliderUser2->setYSliderPositionRelative(vy);}
}
//--------------------------------------------------------
void Wall::closeVideoPlayer(int user){
    if(user == 1){
        videoUser1->stop();
    }
}
void Wall::removeStuffUser1()
{
    textSliderUser1->hide();
    imageSliderUser1->hide();
    if(icon_close1.videotype == true){
            icon_close1.videotype = false;
            videoUser1->stop();
    }
    icon_close1.tp->setNoActive();
}
void Wall::removeStuffUser2(){
    textSliderUser2->hide();
    imageSliderUser2->hide();
    if(icon_close2.videotype == true){
            icon_close2.videotype = false;
            videoUser2->stop();
    }
    icon_close2.tp->setNoActive();
}
//--------------------------------------------------------
void Wall::htmlSpliter2(string s){
    Htmlstring* auxhtml;
    //Remove all <p></p> and <br /> from the string
    //std::string str ("------HTML spliter------");
    //cout << str << endl;
    std::string open_par_tag ("<p>");
    std::string close_par_tag ("</p>");
    std::string brake_row_tag ("<br />");

    //Removing open_par_tag ("<p>")
    std::size_t found = s.find(open_par_tag);
    std::size_t found2;
    while (found!=std::string::npos)
    {
        s.erase(found, open_par_tag.size());
        found = s.find(open_par_tag);
    }
    //Removing close_par_tag ("</p>")
    found = s.find(close_par_tag);
    while (found!=std::string::npos)
    {
        s.erase(found, close_par_tag.size());
        found = s.find(close_par_tag);
    }
    //Removing brake_row_tag ("<br />")
    found = s.find(brake_row_tag);
    while (found!=std::string::npos)
    {
        s.erase(found, brake_row_tag.size());
        found = s.find(brake_row_tag);
    }
    string linebuffer = "";
    string buffer = "";
    bool openpar = false;

    for(int i=0; i < s.length(); i++)
    {

        if(s[i] == '\n' || i == s.length()-1) //end of line or last position od the string
        {
            openpar = false;
            //cout << linebuffer << endl;

            //We analize the line buffer


                //cout << linebuffer << endl;
                if(linebuffer.size() >= 7) //Minimmun amount of caracters for having a bold element <b></b>
                {
                    //We check if in fact there is any <b> element
                    found = linebuffer.find("<b>");
                    found2 = linebuffer.find("</b>");
                    if(found!=std::string::npos) //We have at least one <b> element into the linebuffer
                    {
                        //cout << "line with a bold" << endl;
                        //Reading paragaph before bold
                        for (int j = 0 ; j < found ; j++)
                        {
                            buffer.push_back(linebuffer[j]);
                        }
                        auxhtml =  new Htmlstring(buffer, false);
                        paragraph.push_back(auxhtml);
                        buffer = "";

                        //Reading bold
                        for (int j = found+3; j < found2 ; j++ )
                        {
                            buffer.push_back(linebuffer[j]);
                        }
                        auxhtml =  new Htmlstring(buffer, true);
                        paragraph.push_back(auxhtml);
                        buffer = "";

                        //Reading paragaph after bold

                        for (int j = found2+4 ; j < linebuffer.size(); j++)
                        {
                             buffer.push_back(linebuffer[j]);
                        }
                        auxhtml =  new Htmlstring(buffer, false);
                        paragraph.push_back(auxhtml);
                        buffer = "";
                    }
                    else
                    {
                        //the line is a paragraph
                        //cout << "paragraph line" << endl;

                        auxhtml =  new Htmlstring(linebuffer, false);
                        paragraph.push_back(auxhtml);
                    }
                }
                else
                {
                    //The line is a paragraph
                    //cout << "paragraph line" << endl;

                    auxhtml =  new Htmlstring(linebuffer, false);
                    paragraph.push_back(auxhtml);
                }

            //Reset thwe buffer line
            linebuffer = "";
        }
        else
        {
            linebuffer += s[i];

        }
    }
}
void Wall::htmlSpliter2U2(string s)
{
    Htmlstring* auxhtml;


    //Remove all <p></p> and <br /> from the string
    //std::string str ("------HTML spliter User2------");
    //cout << str << endl;
    std::string open_par_tag ("<p>");
    std::string close_par_tag ("</p>");
    std::string brake_row_tag ("<br />");

    //Removing open_par_tag ("<p>")
    std::size_t found = s.find(open_par_tag);
    std::size_t found2;
    while (found!=std::string::npos)
    {
        s.erase(found, open_par_tag.size());
        found = s.find(open_par_tag);
    }
    //Removing close_par_tag ("</p>")
    found = s.find(close_par_tag);
    while (found!=std::string::npos)
    {
        s.erase(found, close_par_tag.size());
        found = s.find(close_par_tag);
    }
    //Removing brake_row_tag ("<br />")
    found = s.find(brake_row_tag);
    while (found!=std::string::npos)
    {
        s.erase(found, brake_row_tag.size());
        found = s.find(brake_row_tag);
    }

    string linebuffer = "";
    string buffer = "";
    bool openpar = false;

    for(int i=0; i < s.length(); i++)
    {
        if(s[i] == '\n' || i == s.length()-1) //end of line or last position od the string
        {
            openpar = false;
            //cout << linebuffer << endl;
            //We analize the line buffer
                //cout << linebuffer << endl;
                if(linebuffer.size() >= 7) //Minimmun amount of caracters for having a bold element <b></b>
                {
                    //We check if in fact there is any <b> element
                    found = linebuffer.find("<b>");
                    found2 = linebuffer.find("</b>");
                    if(found!=std::string::npos) //We have at least one <b> element into the linebuffer
                    {
                        //cout << "line with a bold" << endl;
                        //Reading paragaph before bold
                        for (int j = 0 ; j < found ; j++)
                        {
                            buffer.push_back(linebuffer[j]);
                        }
                        //delete auxhtml;
                        auxhtml =  new Htmlstring(buffer, false);
                        paragraph2.push_back(auxhtml);
                        buffer = "";

                        //Reading bold
                        for (int j = found+3; j < found2 ; j++ )
                        {
                            buffer.push_back(linebuffer[j]);
                        }
                        //delete auxhtml;
                        auxhtml =  new Htmlstring(buffer, true);
                        paragraph2.push_back(auxhtml);
                        buffer = "";

                        //Reading paragaph after bold

                        for (int j = found2+4 ; j < linebuffer.size(); j++)
                        {
                             buffer.push_back(linebuffer[j]);
                        }
                        //delete auxhtml;
                        auxhtml =  new Htmlstring(buffer, false);
                        paragraph2.push_back(auxhtml);
                        buffer = "";
                    }
                    else
                    {
                        //the line is a paragraph
                        //cout << "paragraph line" << endl;
                        //delete auxhtml;
                        auxhtml =  new Htmlstring(linebuffer, false);
                        paragraph2.push_back(auxhtml);
                    }
                }
                else
                {
                    //The line is a paragraph
                    //cout << "paragraph line" << endl;
                    //delete auxhtml;
                    auxhtml =  new Htmlstring(linebuffer, false);
                    paragraph2.push_back(auxhtml);
                }
            //Reset thwe buffer line
            linebuffer = "";
        }
        else
        {
            linebuffer += s[i];
        }
    }
}





