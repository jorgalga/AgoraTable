#include "DataManager.h"
#include "Node.h"
#include "BGnode.h"
#include "Gesture.h"
#include "MediaContent.h"

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <sstream>
#include <locale>         // std::locale, std::touppe
#include <cmath>


//Constructor
DataManager::DataManager()
{
    category = 0;

    for(int i=0; i < 40 ; i++)
    {
        season_user1[i]=0;
        season_user2[i]=0;
    }

    activeNode = NULL;
    activeNode2 = NULL;

    triggedNode = false;
    triggedNode2 = false;

    indexInterNode = 0;
    indexInterNode2 = 10 ;

    user1_idtablet = "";
    user2_idtablet = "";

    interactiveNode = NULL;
    interactiveNode2 = NULL;

    totalCO2User1 = 0;
    totalCO2User2 = 0;

    MobilityCO2User1= 0;
    HabitatCO2User1= 0;
    EnergyCO2User1= 0;
    ConsumptionCO2User1= 0;

    MobilityCO2User2= 0;
    HabitatCO2User2= 0;
    EnergyCO2User2= 0;
    ConsumptionCO2User2= 0;

    user1_idsession = "";
    user2_idsession = "";
    state =4;
    resetInterNode1Time = -1.0;
    resetInterNode2Time =  -1.0;
    durationMovement = 1.0;
}
//--------------------------------------
DataManager::~DataManager()
{
}
//
void DataManager::update()
{

    //restore position Interactive Node 1
    if(ofGetElapsedTimef() <= resetInterNode1Time+durationMovement)
    {
        int px = interpolator(posx_inode1,340,resetInterNode1Time,durationMovement);
        int py = interpolator(posy_inode1,80,resetInterNode1Time,durationMovement);
        animatedNode1->move(posx_inode1+px,posy_inode1+py);
        //cout << "-----------------------" << endl;
        //cout << "x_" << px<< " y_"<< py<< endl;
    }
    //restore position Interactive Node 2
    if(ofGetElapsedTimef() <= resetInterNode2Time+durationMovement)
    {
        int px = interpolator(posx_inode2,1920-440,resetInterNode2Time,durationMovement);
        int py = interpolator(posy_inode2,1080-160,resetInterNode2Time,durationMovement);
        animatedNode2->move(posx_inode2+px,posy_inode2+py);

    }
}
//-------------------------------------------------------------------------
int DataManager::getCategory()
{
    return category;
}
//-------------------------------------------------------------------------
int DataManager::getUser1Cat()
{
    return user1_category;
}
//-------------------------------------------------------------------------
int DataManager::getUser2Cat()
{
    return user2_category;
}
//-------------------------------------------------------------------------
void DataManager::setUser1Cat(int c)
{
    user1_category = c;
}
//-------------------------------------------------------------------------
void DataManager::setUser2Cat(int c)
{
    user2_category = c;
}

//-------------------------------------------------------------------------
void DataManager::setCategory(string str)
{
     if (str.compare("Mobilitat") == 0)  {category=1;}
     if (str.compare("Habitat") == 0)    {category=2;}
     if (str.compare("Energy") == 0)     {category=3;}
     if (str.compare("Consumption") == 0){category=4;}

     user1_category = category;
     user2_category = category;

}
//-------------------------------------------------------------------------
void DataManager::setGestureToNodes()
{
    Node* auxnode;
    Gesture* auxgest;
    //Setting of the first ten nodes
    int gestindex;
    if( user1_category==1){gestindex=0;}
    if( user1_category==2){gestindex=10;}
    if( user1_category==3){gestindex=20;}
    if( user1_category==4){gestindex=30;}

    for(int i=0; i < 10; i++)
    {
        auxnode = vecNodes[i];

        //vecNodes[i]->toString();
        auxgest = vecGestures[i+gestindex];
        //auxgest->toString();

        auxnode->setCurrGesture(auxgest);
    }

}

//-------------------------------------------------------------------------
string DataManager::getPathCategory()
{
    return pathCategory;
}

//-------------------------------------------------------------------------
int DataManager::getNumNodes()
{
    return vecNodes.size();
}

//-------------------------------------------------------------------------
void DataManager::drawNodes()
{
    //cout << vecNodes.size() << endl;
    Node* aux;

    for(int i = 0; i<vecNodes.size(); i++)
    {
        aux = vecNodes[i];

        //Nodes User 2
        if(aux->isTurned())
        {
            if(i != indexInterNode2)
            {
                //aux->draw(season_user1_lang);
                aux->drawTurned(2, user2_idsession);
            }
        }
        //Nodes User 1
        else
        {
            if(i != indexInterNode)
            {
                //aux->draw(season_user1_lang);
                aux->draw(2, user1_idsession);
            }
        }
    }
    //Interactive Node User 1
    aux = vecNodes[indexInterNode];
    aux->draw(season_user1_lang, user1_idsession);
    //Interactive Node user 2
    aux = vecNodes[indexInterNode2];
    aux->drawTurned(season_user2_lang, user2_idsession);

}

//-------------------------------------------------------------------------
void DataManager::drawBgnodes()
{
    BGnode* aux;
    for (int i=0 ; i < vecBGnodes.size() ; i++)
    {
        aux = vecBGnodes[i];

        if(season_user1[i]== 1 && season_user2[i]==1  )
        {
            if(i <10){//theme 1 Node
                if(user1_category == 1 && user2_category == 1){aux->draw(false,false);}
                else if(user1_category != 1 && user2_category == 1){aux->draw(true, false);}
                else if(user1_category == 1 && user2_category != 1){aux->draw(false,true);}
                else if(user1_category != 1 && user2_category != 1){aux->draw(true, true);}
            }
            else if(i >= 10 && i < 20)
            {
                if(user1_category == 2 && user2_category == 2){aux->draw(false,false);}
                else if(user1_category != 2 && user2_category == 2){aux->draw(true, false);}
                else if(user1_category == 2 && user2_category != 2){aux->draw(false,true);}
                else if(user1_category != 2 && user2_category != 2){aux->draw(true, true);}
            }
            else if(i >= 20 && i < 30)
            {
                if(user1_category == 3 && user2_category == 3){aux->draw(false,false);}
                else if(user1_category != 3 && user2_category == 3){aux->draw(true, false);}
                else if(user1_category == 3 && user2_category != 3){aux->draw(false,true);}
                else if(user1_category != 3 && user2_category != 3){aux->draw(true, true);}
            }
            else if(i >= 30)
            {
                if(user1_category == 4 && user2_category == 4){aux->draw(false,false);}
                else if(user1_category != 4 && user2_category == 4){aux->draw(true, false);}
                else if(user1_category == 4 && user2_category != 4){aux->draw(false,true);}
                else if(user1_category != 4 && user2_category != 4){aux->draw(true, true);}
            }
        }
        if(season_user1[i]== 0 && season_user2[i]==1  ){
            if(i <10)
            {
                if(user2_category == 1){aux->draw(false, false);}else{ aux->draw(false, true); }
            }
            else if(i >= 10 && i < 20)
            {
                if(user2_category == 2){aux->draw(false, false);}else{ aux->draw(false, true); }
            }
            else if(i >= 20 && i < 30)
            {
                if(user2_category == 3){aux->draw(false, false);}else{ aux->draw(false, true); }
            }
            else if(i >= 30)
            {
                if(user2_category == 4){aux->draw(false, false);}else{ aux->draw(false, true); }
            }
        }
        if(season_user1[i]== 1 && season_user2[i]==0  )
        {
            if(i <10)
            {
                if(user1_category == 1){aux->draw(false, false);}else{ aux->draw(true, false); }
            }
            else if(i >= 10 && i < 20)
            {
                if(user1_category == 2){aux->draw(false, false);}else{ aux->draw(true, false); }
            }
            else if(i >= 20 && i < 30)
            {
                if(user1_category == 3){aux->draw(false, false);}else{ aux->draw(true, false); }
            }
            else if(i >= 30)
            {
                if(user1_category == 4){aux->draw(false, false);}else{ aux->draw(true, false); }
            }
        }
        if(season_user1[i]== 0 && season_user2[i]==0  )
        {
            aux->draw(false, false);
        }
    }
}
void DataManager::emptyseasonuser1()
{
    for (int i=0; i < 40; i ++)
    {
        season_user1[i] =0;
    }
}
void DataManager::emptyseasonuser2()
{
    for (int i=0; i < 40; i ++)
    {
        season_user2[i] =0;
    }
}
//-------------------------------------------------------------------------
void DataManager::lockInteractiveNode(int px, int py)
{
    Node* aux;
    int deletepos;
    deletepos = -1;
    for(int i = 0; i<vecNodes.size() ; i++)
    {
        aux = vecNodes[i];
        if(aux->checkClicked(px, py) == true)
        {
            if(!aux->isTurned())
            {
                interactiveNode = aux;
                if(indexInterNode != i){triggedNode = true;}
                indexInterNode = i;
            }
            else
            {
                interactiveNode2 = aux;
                if(indexInterNode2 != i){triggedNode2 = true;}
                indexInterNode2 = i;
            }
        }
    }
    /*
    if(deletepos != -1)
    {
        vecNodes.erase(vecNodes.begin() + deletepos);
        vecNodes.push_back(interactiveNode);
    }
    */
}

//-------------------------------------------------------------------------
void DataManager::moveInteractiveNode(int px, int py)
{
    if(interactiveNode == NULL)
    {
        cout << "Null pointer" << endl;
    }
    else
    {
        if(interactiveNode->checkClicked(px,py))
        {
            interactiveNode->move(px,py);
        }
    }
}
//-------------------------------------------------------------------------
void DataManager::moveInteractiveNode2(int px, int py)
{
    if(interactiveNode2 == NULL)
    {
        cout << "Null pointer" << endl;
    }
    else
    {
        if(interactiveNode2->checkClicked(px,py))
        {
            interactiveNode2->move(px,py);
        }
    }
}


//-------------------------------------------------------------------------
bool DataManager::checkNodeClicked(int px, int py)
{
    bool clicked = false;
    bool turned;

    Node* aux;
    int index_clicked;
    index_clicked = -1; // Not an index possible in the vector



    for(int i = 0; i<vecNodes.size() ; i++)
    {
        aux = vecNodes[i];

        //If the node is clicked we save the index of the node in order of clossing the other Nodes which are possible to be opened.
        if(aux->checkClicked(px, py) == true)
        {
                if(aux->isTurned())
                {
                    turned = true;

                    index_clicked = i;
                    if(aux->isActive())
                    {
                        aux->setTimeClosing();
                        activeNode2 = NULL;
                    }
                    else
                    {
                        aux->setTimeOpening();
                        activeNode2 = aux;
                        triggedNode2 = true;
                    }
                    clicked = true;

                }
                else
                {
                    turned = false;
                    index_clicked = i;
                    if(aux->isActive())
                    {
                        aux->setTimeClosing();
                        activeNode = NULL;
                    }
                    else
                    {
                        aux->setTimeOpening();
                        activeNode = aux;
                        triggedNode = true;
                    }
                    clicked = true;
                }
        }
    }
    //closing the other possible opened

    if(index_clicked != -1)//We have one Node Clicked
    {
        for(int i = 0; i<vecNodes.size() ; i++)
        {
            aux = vecNodes[i];
            if(index_clicked != i && aux->isActive() )
            {
                if(turned == false && !aux->isTurned())
                {
                    aux->setTimeClosing();
                }
                if(turned == true && aux->isTurned())
                {
                    aux->setTimeClosing();
                }

            }
        }
    }
    return clicked;
}
bool DataManager::checkInterNodeSelectorClicked(int px, int py)
{
    if(interactiveNode != NULL){interactiveNode->checkCollectClicked(px, py);}
    if(interactiveNode2 != NULL){interactiveNode2->checkCollectClicked(px, py);}

    return  true;
}
//-------------------------------------------------------------------------
void DataManager::loadTestNode()
{
    Node* aux = new Node();

    vecNodes.push_back(aux);
    //vecNodes[0]->toString();
}

//-------------------------------------------------------------------------
void DataManager::launchTestNode()
{
    if(vecNodes[0]->isActive())
    {
        vecNodes[0]->setTimeClosing();
    }
    else
    {
        vecNodes[0]->setTimeOpening();
    }
}

//-------------------------------------------------------------------------
void DataManager::loadSettings()
{

    /*Node* node = new Node();
    vecNodes.push_back(node);
    std::cout << "p " << node << std::endl;
    return;
    */

    ofFile file;
    file.open("settings.xml"); // open a file
    ofBuffer buffer = file.readToBuffer(); // read to a buffer

    ofXml nodeSettings;
    nodeSettings.loadFromBuffer( buffer.getText() ); // now get the buffer as a string and make XML

    int num_main_nodes = 0;

    //Reading the url of the database
    nodeSettings.setTo("databaseIP");
    databaseIP = nodeSettings.getValue();

    //Reading the url of the database
    nodeSettings.setTo("../databaseURL");
    databaseURL = nodeSettings.getValue();
    //cout << nodeSettings.getValue() << endl;
    nodeSettings.setTo("../systempath");
    systemaPath = nodeSettings.getValue(); cout << systemaPath << endl;
    //Setting the node to the categoty node
    nodeSettings.setTo("../category");
    setCategory(nodeSettings.getValue());

    //setting the path of the background
    switch(getCategory())
    {
        case 1: {nodeSettings.setTo("../Mobilitat");   pathCategory = nodeSettings.getValue(); }break;
        case 2: {nodeSettings.setTo("../Habitat");     pathCategory = nodeSettings.getValue(); }break;
        case 3: {nodeSettings.setTo("../Energy");      pathCategory = nodeSettings.getValue(); }break;
        case 4: {nodeSettings.setTo("../Consumption"); pathCategory = nodeSettings.getValue(); }break;
    }

    nodeSettings.setTo("../numNodes");
    num_main_nodes = nodeSettings.getIntValue();
    //cout << num_main_nodes << endl;

    Node* aux;

    int auxpx = 0;
    int auxpy = 0;


    nodeSettings.setTo("../MainNode[0]/posx");
    auxpx = nodeSettings.getIntValue();
    nodeSettings.setTo("../posy");
    auxpy = nodeSettings.getIntValue();

    aux = new Node(auxpx, auxpy, databaseIP, this);
    vecNodes.push_back(aux);

    for(int i=1; i < num_main_nodes ; i++ )
    {
        string str = "../../MainNode[";
        str += intToString(i);
        str += "]/posx";

        nodeSettings.setTo(str);
        auxpx = nodeSettings.getIntValue();

        nodeSettings.setTo("../posy");
        auxpy = nodeSettings.getIntValue();

        aux = new Node(auxpx, auxpy, databaseIP, this);
        //aux->toString();
        if(i >= 10){aux->setTurnedPosition();}
        vecNodes.push_back(aux);
    }



    interactiveNode = vecNodes[0];
}

void DataManager::loadBgNodes()
{


    ofFile file;
    file.open("bgnodes.xml"); // open a file
    ofBuffer buffer = file.readToBuffer(); // read to a buffer

    ofXml nodeSettings;
    nodeSettings.loadFromBuffer( buffer.getText() ); // now get the buffer as a string and make XML

    int num_main_nodes = 40;
    BGnode* aux;

    string pathaux;
    int posx;
    int posy;
    int posxu1;
    int posyu1;
    int posxu2;
    int posyu2;
    int posxbu;
    int posybu;

    nodeSettings.setTo("bgnodes");


    for(int i=0; i < num_main_nodes ; i++)
    {
        nodeSettings.setToChild(i);
        pathaux = "images/bgicons/";
        pathaux += intToString(i+1);
        pathaux += ".png";

        posx = nodeSettings.getIntValue("posx");
        posy = nodeSettings.getIntValue("posy");
        posxu1 = nodeSettings.getIntValue("posxu1");
        posyu1 = nodeSettings.getIntValue("posyu1");
        posxu2 = nodeSettings.getIntValue("posxu2");
        posyu2 = nodeSettings.getIntValue("posyu2");
        posxbu = nodeSettings.getIntValue("posxbu");
        posybu = nodeSettings.getIntValue("posybu");


        aux = new BGnode(i+1,pathaux, posx, posy,  posxu1, posyu1, posxu2, posyu2, posxbu, posybu );
        vecBGnodes.push_back(aux);

        nodeSettings.setToParent(1);

        //cout << pathaux << endl;

    }


}

void DataManager::loadGestures()
{
    Gesture* gestaux;
    MediaContent* mc;


    ofHttpResponse resp = ofLoadURL(databaseURL);

    //ofFile file;
    //file.open("bak_database.xml"); // open a file
    //ofBuffer buffer = file.readToBuffer(); // read to a buffer

    int k=0;


    if(settings.loadFromBuffer(resp.data))
    //if(settings.loadFromBuffer(buffer.getText()))
    {
        settings.pushTag("data");
        settings.pushTag("themes");
        //cout << settings.getNumTags("themes") << endl;

        int nthemes = settings.getNumTags("theme");
        //cout << "Num themes: " << nthemes << endl;

        //iterating first 4 themes
        for (int i= 0; i < nthemes ; i++)
        {
            settings.pushTag("theme", i);
            settings.pushTag("gestures");

            int ngestures = settings.getNumTags("gesture");
            //cout << "Num gestures: " << ngestures << endl;

            for(int j=0; j < ngestures; j++)
            {
                //cout << "Theme: " << i << " Gesture: " << j << endl;
                gestaux = new Gesture(j+1 + (i*10) ,i+1);
                cout << j+1 + (i*10) << endl;


                settings.pushTag("gesture", j);



                if(settings.tagExists("imagepath"))
                {
                    //cout << "There is a main image in the Node "<< settings.getValue("imagepath","") << endl;
                    gestaux->setMainimage_path_de(settings.getValue("imagepath",""));
                }
                if(settings.tagExists("achievedpercent"))
                {
                    float value = settings.getValue("achievedpercent",0.0);
                    gestaux->setCO2Impact(value);

                    CO2gestures[k] = value;
                    cout << "[CO2 Impact] " <<  CO2gestures[k] << endl;
                    k++;
                }
                if(settings.tagExists("providerlogourl"))
                {
                    gestaux->setLogoPath(settings.getValue("providerlogourl",""));
                    gestaux->setLogoIncluded();
                }

                //GERMAN Data loading
                settings.pushTag("gesturecontent",0);

                if(settings.tagExists("name"))
                {
                    settings.pushTag("name");
                    //Saving DATA
                    //cout << " name " << settings.getValue("text","") << endl;
                    gestaux->setName_de(settings.getValue("text",""));

                    if(settings.tagExists("content"))
                    {
                        settings.pushTag("content");

                        //cout << "NAME ---------------------------" << endl;

                        settings.popTag();
                    }

                    settings.popTag();
                }
                if(settings.tagExists("overview"))
                {
                    settings.pushTag("overview");
                    gestaux->setOverview_de(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");

                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");

                            cout << "OVERVIEW CONTENT DE " << j << " " << t << endl;

                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecOverview_de(mc);
                                cout << mc->getPath() << endl;
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecOverview_de(mc);
                                cout << mc->getPath() << endl;
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecOverview_de(mc);
                                cout << mc->getPath() << endl;

                            }

                            settings.popTag();
                        }

                    }
                    settings.popTag();
                }
                if(settings.tagExists("details"))
                {
                    settings.pushTag("details");
                    gestaux->setDetails_de(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        //cout << "DETAILS contents" << k << endl;
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecDetails_de(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecDetails_de(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecDetails_de(mc);
                                cout << mc->getPath() << endl;

                            }



                            settings.popTag();
                        }


                    }
                    settings.popTag();
                }
                if(settings.tagExists("product"))
                {
                    settings.pushTag("product");
                    gestaux->setProducts_de(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecProducts_de(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecProducts_de(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecProducts_de(mc);
                                cout << mc->getPath() << endl;

                            }


                            settings.popTag();
                        }
                    }
                    settings.popTag();
                }
                if(settings.tagExists("provider"))
                {
                    settings.pushTag("provider");
                    gestaux->setProvider_de(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecProvider_de(mc);

                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecProvider_de(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecProvider_de(mc);
                                cout << mc->getPath() << endl;

                            }

                            settings.popTag();
                        }
                    }

                    settings.popTag();
                }

                settings.popTag();

                //FRENCH data loading
                settings.pushTag("gesturecontent",1);

                if(settings.tagExists("name"))
                {
                    settings.pushTag("name");
                    //Saving DATA
                    //cout << " name " << settings.getValue("text","") << endl;
                    gestaux->setName_fr(settings.getValue("text",""));

                    if(settings.tagExists("content"))
                    {
                        settings.pushTag("content");

                        //cout << "NAME ---------------------------" << endl;

                        settings.popTag();
                    }


                    settings.popTag();
                }
                if(settings.tagExists("overview"))
                {
                    settings.pushTag("overview");
                    gestaux->setOverview_fr(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("pathpreview", ""), 1);
                                gestaux->addTovecOverview_fr(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecOverview_fr(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecOverview_fr(mc);
                                cout << mc->getPath() << endl;

                            }



                            settings.popTag();
                        }
                    }
                    settings.popTag();
                }
                if(settings.tagExists("details"))
                {
                    settings.pushTag("details");
                    gestaux->setDetails_fr(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecDetails_fr(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecDetails_fr(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecDetails_fr(mc);
                                cout << mc->getPath() << endl;

                            }
                            settings.popTag();
                        }
                    }
                    settings.popTag();
                }
                if(settings.tagExists("product"))
                {
                    settings.pushTag("product");
                    gestaux->setProducts_fr(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecProducts_fr(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecProducts_fr(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecProducts_fr(mc);
                                cout << mc->getPath() << endl;

                            }

                            settings.popTag();
                        }
                    }
                    settings.popTag();
                }
                if(settings.tagExists("provider"))
                {
                    settings.pushTag("provider");
                    gestaux->setProvider_fr(settings.getValue("text",""));
                    if(settings.tagExists("content"))
                    {
                        int nc = settings.getNumTags("content");
                        for( int k=0 ; k < nc ; k++)
                        {
                            settings.pushTag("content", k);

                            string t = settings.getValue("mediatype", "");
                            if(t.compare("pdf") == 0)
                            {
                                mc = new MediaContent(settings.getValue("previewpath", ""), 1);
                                gestaux->addTovecProvider_fr(mc);
                            }
                            if(t.compare("video") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 2);
                                gestaux->addTovecProvider_fr(mc);
                            }
                            if(t.compare("image") == 0)
                            {
                                mc = new MediaContent(settings.getValue("path", ""), 3);
                                gestaux->addTovecProvider_fr(mc);
                                cout << mc->getPath() << endl;

                            }

                            settings.popTag();
                        }
                    }

                    settings.popTag();
                }

                vecGestures.push_back(gestaux);


                settings.popTag();
                settings.popTag();//Back to Gestures
            }//End Iteration Gestures in a theme
        settings.popTag();//Back to Theme
        settings.popTag();//Back to Themes
        }//End iteration of themes
    }
}

//-------------------------------------------------------------------------
void DataManager::loadSeasonUser(int user, string idtablet)
{
    //ofFile file;
    //file.open("bak_seasson.xml"); // open a file
    //ofBuffer buffer = file.readToBuffer(); // read to a buffer

    ofXml nodeSettings;
    string idsess;

    string res = databaseIP;
    res += "gesturedb/request.php?cmd=getSession&tabletid=";
    res += idtablet;

    //deleting before refilling the data
    if(user == 1)
    {
        for(int i = 0; i < 40; i++){season_user1[i]=0;messages_user1[i]=0;}
    }

    else
    {
        for(int i = 0; i < 40; i++){season_user2[i]=0;messages_user2[i]=0;}
    }


    ofHttpResponse resp = ofLoadURL(res);
    nodeSettings.loadFromBuffer(resp.data);

    //nodeSettings.loadFromBuffer(buffer.getText());


    nodeSettings.setTo("session");

    idsess = nodeSettings.getValue("id");
    string lang = nodeSettings.getValue("languageid");

    nodeSettings.setTo("gestures");
    int numGestures = nodeSettings.getNumChildren();
    //cout << "Num gestures Collected " << numGestures << endl;
    int idgest;

    for(int i=0; i < numGestures ; i++)
    {
        nodeSettings.setToChild(i);

            idgest = nodeSettings.getIntValue("gestureid");
            //cout << "Gesture with ID: " << idgest <<endl;
            if(user == 1){season_user1[idgest-1]=1; }
            if(user == 2){season_user2[idgest-1]=1;}

        nodeSettings.setToParent(1);
    }
    nodeSettings.setToParent(1);
    nodeSettings.setTo("messages");
    int numMessages = nodeSettings.getNumChildren();
    cout << "Number of messages: " << numMessages << endl;
    int idmsg;
    for(int i=0; i < numMessages ; i++)
    {
        nodeSettings.setToChild(i);

            idmsg = nodeSettings.getIntValue("gestureid");
            if(user == 1){messages_user1[idmsg-1]=1; }
            if(user == 2){messages_user2[idmsg-1]=1;}
        nodeSettings.setToParent(1);
    }

    int indexvect = 0;
    Node* aux;
    Gesture* gestaux;
    if(user == 1)
    {
        olduser1_idsession = user1_idsession;
        user1_idsession = idsess;
        user1_idtablet = idtablet;

        setTotalCO2Impact(1);
        setTotalCO2ImpactByTheme(1, 1);
        setTotalCO2ImpactByTheme(1, 2);
        setTotalCO2ImpactByTheme(1, 3);
        setTotalCO2ImpactByTheme(1, 4);

        if(user1_category==1){indexvect = 0;}
        else if(user1_category==2){indexvect = 10;}
        else if(user1_category==3){indexvect = 20;}
        else if(user1_category==4){indexvect = 30;}
        //Setting up those Nodes wich are owned by the user
        //for (int i=indexvect; i < indexvect+10;i++)
        for (int i=0; i < 10; i++)
        {
            aux = vecNodes[i];
            gestaux = vecGestures[i+indexvect];

            if(season_user1[i+indexvect] == 1)
            {
                aux->setOwned();
            }
            else
            {
                aux->setNotOwned();
            }
            if(messages_user1[i+indexvect] == 1)
            {
                aux->setNoInfosenden();
                cout << "NOINFOSENDEN" << endl;
            }
            else
            {
                aux->setInfoSenden();
            }

            aux->setDisplayed();
            aux->setCurrGesture(gestaux);
            gestaux->toString();
            aux->reloadImageByIndex(i%10+indexvect+1);
            aux->setResetPosTime();
            aux->setNoActive();
        }
        if(lang.compare("de") == 0){
            //cout << "German seasson" << endl;
            if(olduser1_idsession.compare(user1_idsession)!=0){season_user1_lang = 1;}
        }
        if(lang.compare("fr") == 0){
            //cout << "German seasson" << endl;
            if(olduser1_idsession.compare(user1_idsession)!=0){season_user1_lang = 2;}
        }
    }
    if(user == 2)
    {
        olduser2_idsession  = user2_idsession;
        user2_idsession = idsess;
        user2_idtablet = idtablet;

        setTotalCO2Impact(2);
        setTotalCO2ImpactByTheme(2, 1);
        setTotalCO2ImpactByTheme(2, 2);
        setTotalCO2ImpactByTheme(2, 3);
        setTotalCO2ImpactByTheme(2, 4);

        if(user2_category==1){indexvect = 0;}
        else if(user2_category==2){indexvect = 10;}
        else if(user2_category==3){indexvect = 20;}
        else if(user2_category==4){indexvect = 30;}

        for (int i=10; i < 20; i++)
        {
            aux = vecNodes[i];
            gestaux = vecGestures[i%10+indexvect];

            if(season_user2[i%10+indexvect] == 1)
            {
                aux->setOwned();
            }
            else
            {
                aux->setNotOwned();
            }
            if(messages_user2[i%10+indexvect] == 1)
            {
                aux->setNoInfosenden();
            }
            else
            {
                aux->setInfoSenden();
            }

            aux->setDisplayed();
            aux->setCurrGesture(gestaux);
            aux->reloadImageByIndex(i%10+indexvect+1);
            aux->setResetPosTime();
            aux->setNoActive();
        }

        if(lang.compare("de") == 0){
            //cout << "German seasson" << endl;
            if(olduser2_idsession.compare(user2_idsession)!=0){season_user2_lang = 1;}
        }
        if(lang.compare("fr") == 0){
            //cout << "German seasson" << endl;
             if(olduser2_idsession.compare(user2_idsession)!=0){season_user2_lang = 2;}
        }
    }
}

Node* DataManager::getInteractiveNode()
{
    return interactiveNode;
}

Node* DataManager::getActiveNode()
{
    return activeNode;
}

Node* DataManager::getInteractiveNode2()
{
    return interactiveNode2;
}

Node* DataManager::getActiveNode2()
{
    return activeNode2;
}
//-------------------------------------------------------------------------
void DataManager::setStateUsers(int su)
{
    state = su;
}

//-------------------------------------------------------------------------
string DataManager::intToString(int pNumber)
{
    ostringstream oOStrStream;
    oOStrStream << pNumber;
    return oOStrStream.str();
}

//-------------------------------------------------------------------------
void DataManager::listNodes()
{
    Node* aux;
    for(int i=0; i< vecNodes.size() ; i++)
    {
        aux = vecNodes[i];
        //aux->toString();
    }
    //cout << "Interactive Node" << endl;
    //interactiveNode->toString();
}
//-------------------------------------------------------------------------
void DataManager::setUsers1()
{
    BGnode* aux;
    for(int i=0; i < vecBGnodes.size(); i++ )
    {
       aux =  vecBGnodes[i];
       aux->setUser1();
    }

}
//-------------------------------------------------------------------------
void DataManager::setUsers2()
{
    BGnode* aux;
    for(int i=0; i < vecBGnodes.size(); i++ )
    {
       aux =  vecBGnodes[i];
       aux->setUser2();
    }

}
//-------------------------------------------------------------------------
void DataManager::setNoUsers()
{
    BGnode* aux;
    for(int i=0; i < vecBGnodes.size(); i++ )
    {
       aux =  vecBGnodes[i];
       aux->setNoUsers();
    }
}
//-------------------------------------------------------------------------
void DataManager::setBothUsers()
{
    BGnode* aux;
    for(int i=0; i < vecBGnodes.size(); i++ )
    {
       aux =  vecBGnodes[i];
       aux->setBothUsers();
    }

}
void DataManager::checkNodesLimitPositions()
{
    cout << "state " << state <<endl;
    if(state == 3)
    {
        if(interactiveNode!= NULL){
            if(interactiveNode->getPosx() > 850 ){
                posx_inode1= interactiveNode->getPosx();
                posy_inode1= interactiveNode->getPosy();
                resetInterNode1Time = ofGetElapsedTimef();
                animatedNode1 = interactiveNode;
            }
        }
        if(interactiveNode2!=NULL){
            if(interactiveNode2->getPosx() < 1920 -950 ){
                posx_inode2= interactiveNode2->getPosx();
                posy_inode2= interactiveNode2->getPosy();
                resetInterNode2Time = ofGetElapsedTimef();
                animatedNode2 = interactiveNode2;
            }
        }
    }
}

//-------------------------------------------------------------------------
void DataManager::setSessionLangUser1(int s)
{
    season_user1_lang = s;
}
//-------------------------------------------------------------------------
void DataManager::setSessionLangUser2(int s)
{
    season_user2_lang = s;
}
//-------------------------------------------------------------------------
int DataManager::getSessionLangUser1()
{
    return season_user1_lang;
}

//-------------------------------------------------------------------------
int DataManager::getSessionLangUser2()
{
    return season_user2_lang;
}

//-------------------------------------------------------------------------
Gesture* DataManager::getGestureOfNode(int i)
{
    Node *aux = vecNodes[i];
    return aux->getCurrGesture();
}
//-------------------------------------------------------------------------
void DataManager::resetSesionUser1()
{
    for(int i=0 ; i < 40 ; i++)
    {
        season_user1[i] = 0;
    }
}
//-------------------------------------------------------------------------
void DataManager::resetSesionUser2()
{
    for(int i=0 ; i < 40 ; i++)
    {
        season_user2[i] = 0;
    }
}
//-------------------------------------------------------------------------
void DataManager::printSesionUser1()
{
    for(int i=0 ; i < 40 ; i++)
    {
        cout << "["<< i+1 << "]"<< season_user1[i] << endl;
    }
}
//-------------------------------------------------------------------------
void DataManager::printSesionUser2()
{
    for(int i=0 ; i < 40 ; i++)
    {
         cout << "["<< i+1 << "]"<< season_user2[i] << endl;
    }
}
//-------------------------------------------------------------------------
void DataManager::setTriggeredNode()
{
    triggedNode = true;
}
//-------------------------------------------------------------------------
void DataManager::setTriggeredNode2()
{
    triggedNode2 = true;
}
//-------------------------------------------------------------------------
void DataManager::setNotTriggeredNode()
{
    triggedNode = false;
}
//-------------------------------------------------------------------------
void DataManager::setNotTriggeredNode2()
{
    triggedNode2 = false;
}
//-------------------------------------------------------------------------
bool DataManager::getTriggeredNode()
{
    return triggedNode;
}
//-------------------------------------------------------------------------
bool DataManager::getTriggeredNode2()
{
    return triggedNode2;
}
//-------------------------------------------------------------------------
string DataManager::getDatabaseIP()
{
    return databaseIP;
}
//-------------------------------------------------------------------------
void DataManager::setDatabaseIP(string s)
{
    databaseIP = s;
}
//-------------------------------------------------------------------------
void DataManager::resetNodesUser1()
{
    activeNode = NULL; // This is importat for hidding the opened Windows

}
//-------------------------------------------------------------------------
void DataManager::notDisplayNodesUser1()
{ Node* aux;
    for (int i=0; i < 10; i++)
    {
        aux = vecNodes[i];
        aux->setNotDisplayed();
    }
}
//-------------------------------------------------------------------------
void DataManager::notDisplayNodesUser2()
{ Node* aux;
    for (int i=10; i < 20; i++)
    {
        aux = vecNodes[i];
        aux->setNotDisplayed();
    }
}
//-------------------------------------------------------------------------
void DataManager::resetNodesUser2()
{
    activeNode2 = NULL; // This is importat for hidding the opened Windows
}

//-------------------------------------------------------------------------
string DataManager::getuser1_idtablet()
{
    return user1_idtablet;
}

//-------------------------------------------------------------------------
string DataManager::getuser2_idtablet()
{
    return user2_idtablet;
}
//-------------------------------------------------------------------------
void DataManager::addGestureToSession(int user, int ngest)
{
    if(user == 1) {season_user1[ngest] = 1; cout << "Added to user 1 Gesture " << ngest << endl; }
    if(user == 2) {season_user2[ngest] = 1; cout << "Added to user 2 Gesture " << ngest << endl;}
}
//-------------------------------------------------------------------------
void DataManager::removeGestureToSession(int user, int ngest)
{
    if(user == 1) {season_user1[ngest] = 0; cout << "Removed from user 1 Gesture " << ngest << endl;}
    if(user == 2) {season_user2[ngest] = 0; cout << "Removed from user 2 Gesture " << ngest << endl;}
}
//-------------------------------------------------------------------------
void DataManager::addMessageToSession(int user, int ngest)
{
    if(user == 1) {messages_user1[ngest] = 1; cout << "Added Message to user 1" << ngest << endl; }
    if(user == 2) {messages_user2[ngest] = 1; cout << "Added Message to user 2 " << ngest << endl;}
}
//-------------------------------------------------------------------------
void DataManager::removeMessageToSession(int user, int ngest)
{
    if(user == 1) {messages_user1[ngest] = 0; cout << "Removed Message to user 1" << ngest << endl; }
    if(user == 2) {messages_user2[ngest] = 0; cout << "Removed Message to user 2 " << ngest << endl;}
}
//-------------------------------------------------------------------------
string DataManager::getPathSystem()
{
    return systemaPath;
}
//-------------------------------------------------------------------------
void DataManager::setTotalCO2Impact(int user)
{
    float res = 0.0;

    if(user == 1)
    {
        for(int i=0; i<40; i++)
        {
            if (season_user1[i] == 1)
            {
                res = res + CO2gestures[i];
            }
        }
        totalCO2User1 = res;
    }
    else
    {
        for(int i=0; i<40; i++)
        {
            if (season_user2[i] == 1)
            {
                res = res + CO2gestures[i];
            }
        }
        totalCO2User2 = res;
    }
}

//-------------------------------------------------------------------------
string DataManager::getTotalCO2Impact(int user)
{
    if(user == 1){return intToString((int)totalCO2User1);}
    if(user == 2){return intToString((int)totalCO2User2);}
}
//-------------------------------------------------------------------------
void DataManager::setTotalCO2ImpactByTheme(int user, int theme)
{
    float res =0.0;
    int index = 0;

    if(theme==1){ index = 0;}
    if(theme==2){ index = 10;}
    if(theme==3){ index = 20;}
    if(theme==4){ index = 30;}

    if(user == 1)
    {
        //cout << "index value "<<  index << endl;
        for(int i = index; i < index+10; i++)
        {
            if(season_user1[i]==1){res = res + CO2gestures[i];}
            //cout << "Value >>> " << res<< endl;
        }
        switch(theme)
        {
            case 1:{MobilityCO2User1 = res; }break;
            case 2:{HabitatCO2User1 = res;}break;
            case 3:{EnergyCO2User1 = res;}break;
            case 4:{ConsumptionCO2User1 = res;}break;
        }
    }
    else
    {
        for(int i = index; i < index+10; i++)
        {
            if(season_user2[i]==1){res = res + CO2gestures[i];}
        }
        switch(theme)
        {
            case 1:{MobilityCO2User2 = res;}break;
            case 2:{HabitatCO2User2 = res;}break;
            case 3:{EnergyCO2User2= res;}break;
            case 4:{ConsumptionCO2User2 = res;}break;
        }
    }
}
//-------------------------------------------------------------------------
string DataManager::getTotalCO2ImpactByTheme(int user, int theme)
{
    if(user == 1)
    {
        switch(theme)
        {
            case 1:{return intToString((int)MobilityCO2User1);   }break;
            case 2:{return intToString((int)HabitatCO2User1);}break;
            case 3:{return intToString((int)EnergyCO2User1);}break;
            case 4:{return intToString((int)ConsumptionCO2User1);}break;
        }
    }
    else
    {
        switch(theme)
        {
            case 1:{return intToString((int)MobilityCO2User2);}break;
            case 2:{return intToString((int)HabitatCO2User2);}break;
            case 3:{return intToString((int)EnergyCO2User2);}break;
            case 4:{return intToString((int)ConsumptionCO2User2);}break;
        }
    }
}
//-------------------------------------------------------------------------
int DataManager::interpolator(int vi, int vf, float timeinit, float duration)
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
