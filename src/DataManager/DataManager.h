#pragma once

#include "ofMain.h"

#include <iostream>
#include <string>         // std::string
#include <sstream>
#include <locale>         // std::locale, std::touppe
#include "ofxSingleton.h"
#include "ofxXmlSettings.h"

// We are using this classes already implemented in the code
class Node;
class Gesture;
class BGnode;


class DataManager: public ofxSingleton<DataManager>
{

    SINGLETON_ACCESS(DataManager);

	public:

		DataManager();
		~DataManager();
		void update();
		int getCategory();
		void setCategory(string str);
		void setGestureToNodes();
		string getPathCategory();
		int getNumNodes();
		void drawNodes();
		void drawBgnodes();
        void lockInteractiveNode(int px, int py);
        void moveInteractiveNode(int px, int py);
        void moveInteractiveNode2(int px, int py);
		bool checkNodeClicked(int px, int py);
		bool checkInterNodeSelectorClicked(int px, int py);
        void launchTestNode();
		void loadTestNode();
		void loadSettings();
		void loadBgNodes();
		void loadGestures();
		void loadSeasonUser(int user,string idtablet);
        void setUsers1();
        void setUsers2();
        void setNoUsers();
        void setBothUsers();
        void setSessionLangUser1(int s);
        void setSessionLangUser2(int s);
        int getSessionLangUser1();
        int getSessionLangUser2();
        int getUser1Cat();
        int getUser2Cat();
        void setUser1Cat(int c);
        void setUser2Cat(int c);
        void resetSesionUser1();
        void resetSesionUser2();
        void printSesionUser1();
        void printSesionUser2();
        vector <Node*>  getNodes(){ return vecNodes; }
		string intToString(int pNumber);
		void listNodes();
		Node* getInteractiveNode();
		Node* getInteractiveNode2();
		Node* getActiveNode();
		Node* getActiveNode2();
		Gesture* getGestureOfNode(int i);
        void setTriggeredNode();
        void setTriggeredNode2();
		void setNotTriggeredNode();
		void setNotTriggeredNode2();
		bool getTriggeredNode();
		bool getTriggeredNode2();
		string getDatabaseIP();
		void setDatabaseIP(string s);
		string getPathSystem();
		string getTotalCO2Impact(int user);
		void setTotalCO2Impact(int user);
		string getTotalCO2ImpactByTheme(int user, int theme);
		void setTotalCO2ImpactByTheme(int user, int theme);
		void resetNodesUser1();
        void resetNodesUser2();
        string getuser1_idtablet();
        string getuser2_idtablet();
        void addGestureToSession(int user, int ngest);
        void removeGestureToSession(int user, int ngest);
        void addMessageToSession(int user, int ngest);
        void removeMessageToSession(int user, int ngest);
        void notDisplayNodesUser1();
        void notDisplayNodesUser2();
        void emptyseasonuser1();
        void emptyseasonuser2();
        void setStateUsers(int su);
        void checkNodesLimitPositions();
        int interpolator(int vi, int vf, float timeinit, float duration);

        int Slider1LastPos;
        int Slider2LastPos;
        int SliderImage1LastPos;
        int SliderImage2LastPos;

    private:

        int category;

        int posx_inode1;
        int posy_inode1;
        int posx_inode2;
        int posy_inode2;

        string databaseIP;
        string pathCategory;
        string databaseURL;

        string systemaPath;

        vector<BGnode*> vecBGnodes;

        vector <Node*> vecNodes;
        vector <Gesture*> vecGestures;

        float CO2gestures[40];
        float totalCO2User1;
        float totalCO2User2;

        float MobilityCO2User1;
        float HabitatCO2User1;
        float EnergyCO2User1;
        float ConsumptionCO2User1;

        float MobilityCO2User2;
        float HabitatCO2User2;
        float EnergyCO2User2;
        float ConsumptionCO2User2;

        int season_user1[40];
        int season_user2[40];
        int messages_user1[40];
        int messages_user2[40];

        int season_user1_lang; // 1 German 2 French
        int season_user2_lang; // 1 German 2 French

        int user1_category;
        int user2_category;

        string user1_idtablet;
        string user2_idtablet;
        string user1_idsession;
        string user2_idsession;
        string olduser1_idsession;
        string olduser2_idsession;


        bool triggedNode;
        bool triggedNode2;

        int indexInterNode;
        int indexInterNode2;

        Node* interactiveNode; //Node which is being dragged
        Node* interactiveNode2; //Node which is being dragged

        Node* activeNode; //Node which is opened
        Node* activeNode2; //Node which is opened
        Node* animatedNode1;
        Node* animatedNode2;

        int state; // 1-User1 | 2-User2 | 3-Both | 4-Nouser

        double resetInterNode1Time;
        double resetInterNode2Time;
        double durationMovement;

        ofxXmlSettings settings;
};
