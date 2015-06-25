#pragma once

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

class MediaContent;

class Gesture
{
    public:


		Gesture();
		Gesture(int i, int t);
		~Gesture();

		int getId();
		void setId(int i);
		int getTheme();

		void setName_de(string nde);
		void setName_fr(string nfr);

		void setOverview_de(string ode);
		void setOverview_fr(string ofr );

		void setDetails_de(string dde);
		void setDetails_fr(string dfr);

		void setProducts_de(string pde);
        void setProducts_fr(string pfr);

        void setProvider_de(string prde);
        void setProvider_fr(string prfr);


		string getName_de();
		string getName_fr();

		string getOverview_de();
		string getOverview_fr();

		string getDetails_de();
		string getDetails_fr();

		string getProducts_de();
		string getProducts_fr();

		string getProvider_de();
		string getProvider_fr();

        void toString();

        MediaContent* getFromvecOverview_de(int i);     string getPathByIndexFromvecOverview_de(int i);     int getTypeByIndexFromvecOverview_de(int i);
        MediaContent* getFromvecDetails_de(int i);      string getPathByIndexFromvecDetails_de(int i);      int getTypeByIndexFromvecDetails_de(int i);
        MediaContent* getFromvecProducts_de(int i);     string getPathByIndexFromvecProducts_de(int i);     int getTypeByIndexFromvecProducts_de(int i);
        MediaContent* getFromvecProvider_de(int i);     string getPathByIndexFromvecProvider_de(int i);     int getTypeByIndexFromvecProvider_de(int i);

        int getSizevecOverview_de();
        int getSizevecDetails_de();
        int getSizevecProducts_de();
        int getSizevecProvider_de();

        void addTovecOverview_de(MediaContent* mc);
        void addTovecDetails_de(MediaContent* mc);
        void addTovecProducts_de(MediaContent* mc);
        void addTovecProvider_de(MediaContent* mc);


        MediaContent* getFromvecOverview_fr(int i);
        MediaContent* getFromvecDetails_fr(int i);
        MediaContent* getFromvecProducts_fr(int i);
        MediaContent* getFromvecProvider_fr(int i);

        int getSizevecOverview_fr();
        int getSizevecDetails_fr();
        int getSizevecProducts_fr();
        int getSizevecProvider_fr();

        void addTovecOverview_fr(MediaContent* mc);     string getPathByIndexFromvecOverview_fr(int i);     int getTypeByIndexFromvecOverview_fr(int i);
        void addTovecDetails_fr(MediaContent* mc);      string getPathByIndexFromvecDetails_fr(int i);      int getTypeByIndexFromvecDetails_fr(int i);
        void addTovecProducts_fr(MediaContent* mc);     string getPathByIndexFromvecProducts_fr(int i);     int getTypeByIndexFromvecProducts_fr(int i);
        void addTovecProvider_fr(MediaContent* mc);     string getPathByIndexFromvecProvider_fr(int i);     int getTypeByIndexFromvecProvider_fr(int i);

        void setMainimage_path_de(string p);
        void setMainimage_path_fr(string p);

        string getMainimage_path_de();
        string getMainimage_path_fr();

        void setCO2Impact(float co2);
        float getCO2Impact();

        bool hasLogoIncluded();
        void setLogoIncluded();
        void setLogoPath(string p);
        string getLogoPath();

    private:

        int id;
        int theme;

        float co2Impact;

        string mainimage_path_de;
        string mainimage_path_fr;

        string logo_path;
        bool logoincluded;

        vector <MediaContent*> vecOverview_de;
        vector <MediaContent*> vecDetails_de;
        vector <MediaContent*> vecProducts_de;
        vector <MediaContent*> vecProvider_de;

        vector <MediaContent*> vecOverview_fr;
        vector <MediaContent*> vecDetails_fr;
        vector <MediaContent*> vecProducts_fr;
        vector <MediaContent*> vecProvider_fr;


        //data content
        string name_de;
        string name_fr;

        string overview_de;
        string overview_fr;

        string details_de;
        string details_fr;

        string products_de;
        string products_fr;

        string provider_de;
        string provider_fr;
};
