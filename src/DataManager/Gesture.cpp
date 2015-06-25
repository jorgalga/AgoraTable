#include "Gesture.h"
#include "DataManager/MediaContent.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

//Constructors

Gesture::Gesture()
{
    id = 1;
    theme = 1;
}
Gesture::Gesture(int i, int t)
{
    id = i;
    theme = t;

    logoincluded = false;
}
Gesture::~Gesture()
{

}

//Methods
//-------------------------------------------------------------------------
int Gesture::getId()
{
    return id;
}
//-------------------------------------------------------------------------
void Gesture::setId(int i)
{
    id = 1;
}

//-------------------------------------------------------------------------
int Gesture::getTheme()
{
    return theme;
}

//-------------------------------------------------------------------------
void Gesture::setName_de(string nde)
{
    name_de = nde;
}
//-------------------------------------------------------------------------
void Gesture::setName_fr(string nfr)
{
    name_fr = nfr;
}

//-------------------------------------------------------------------------
void Gesture::setOverview_de(string ode)
{
    overview_de = ode;
}


//-------------------------------------------------------------------------
void Gesture::setOverview_fr(string nfr)
{
    overview_fr = nfr;
}

//-------------------------------------------------------------------------
void Gesture::setDetails_de(string dde)
{
    details_de = dde;
}
//-------------------------------------------------------------------------
void Gesture::setDetails_fr(string dfr)
{
    details_fr = dfr;
}

//-------------------------------------------------------------------------
void Gesture::setProducts_de(string pde)
{
    products_de = pde;
}

//-------------------------------------------------------------------------
void Gesture::setProducts_fr(string pfr)
{
    products_fr = pfr;
}

//-------------------------------------------------------------------------
void Gesture::setProvider_de(string prde)
{
    provider_de = prde;
}

//-------------------------------------------------------------------------
void Gesture::setProvider_fr(string prfr)
{
    provider_fr = prfr;
}

//-------------------------------------------------------------------------
string Gesture::getName_de()
{
    return name_de;
}

//-------------------------------------------------------------------------
string Gesture::getName_fr()
{
    return name_fr;
}

//-------------------------------------------------------------------------
string Gesture::getOverview_de()
{
    return overview_de;
}

//-------------------------------------------------------------------------
string Gesture::getOverview_fr()
{
    return overview_fr;
}

//-------------------------------------------------------------------------
string Gesture::getDetails_de()
{
    return details_de;
}

//-------------------------------------------------------------------------
string Gesture::getDetails_fr()
{
    return details_fr;
}

//-------------------------------------------------------------------------
string Gesture::getProducts_de()
{
    return products_de;
}
//-------------------------------------------------------------------------
string Gesture::getProducts_fr()
{
    return products_fr;
}

//-------------------------------------------------------------------------
string Gesture::getProvider_de()
{
    return provider_de;
}

//-------------------------------------------------------------------------
string Gesture::getProvider_fr()
{
    return provider_fr;
}


//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecOverview_de(int i)
{
    return vecOverview_de[i];
}

//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecOverview_de(int i)
{
    MediaContent* mc = vecOverview_de[i];
    return mc->getPath();
}

//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecOverview_de(int i)
{
    MediaContent* mc = vecOverview_de[i];
    return mc->getType();
}

//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecDetails_de(int i)
{
    MediaContent* mc;
    if(i < vecDetails_de.size())
    {
        mc = vecDetails_de[i];
        return mc;
    }
}
//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecDetails_de(int i)
{
    MediaContent* mc = vecDetails_de[i];
    return mc->getPath();
}
//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecDetails_de(int i)
{
    MediaContent* mc = vecDetails_de[i];
    return mc->getType();
}
//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecProducts_de(int i)
{
    MediaContent* mc;
    if(i < vecProducts_de.size())
    {
        mc = vecProducts_de[i];
        return mc;
    }
}
//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecProducts_de(int i)
{
    MediaContent* mc = vecProducts_de[i];
    return mc->getPath();
}
//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecProducts_de(int i)
{
    MediaContent* mc = vecProducts_de[i];
    return mc->getType();
}

//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecProvider_de(int i)
{
    MediaContent* mc;
    if(i < vecProvider_de.size())
    {
        mc = vecProvider_de[i];
        return mc;
    }
}
//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecProvider_de(int i)
{
    MediaContent* mc = vecProvider_de[i];
    return mc->getPath();

}

//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecProvider_de(int i)
{
    MediaContent* mc = vecProvider_de[i];
    return mc->getType();

}

//-------------------------------------------------------------------------
int Gesture::getSizevecOverview_de()
{
    return vecOverview_de.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecDetails_de()
{
    return vecDetails_de.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecProducts_de()
{
    return vecProducts_de.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecProvider_de()
{
    return vecProvider_de.size();
}

//-------------------------------------------------------------------------
void Gesture::addTovecOverview_de(MediaContent* mc)
{
    cout << "{{{{{{{path}}}}}}} "<< mc->getPath() <<endl;
    vecOverview_de.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecDetails_de(MediaContent* mc)
{
    vecDetails_de.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecProducts_de(MediaContent* mc)
{
    vecProducts_de.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecProvider_de(MediaContent* mc)
{
    vecProvider_de.push_back(mc);
}
//-------------------------------------------------------------------------
//French media data
//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecOverview_fr(int i)
{
    MediaContent* mc;
    if(i < vecOverview_fr.size())
    {
        mc = vecOverview_fr[i];
        return mc;
    }
}

//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecOverview_fr(int i)
{
    MediaContent* mc = vecOverview_fr[i];
    return mc->getPath();
}

//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecOverview_fr(int i)
{
    MediaContent* mc = vecOverview_fr[i];
    return mc->getType();
}


//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecDetails_fr(int i)
{
    MediaContent* mc;
    if(i < vecDetails_fr.size())
    {
        mc = vecDetails_fr[i];
        return mc;
    }
}
//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecDetails_fr(int i)
{
    MediaContent* mc = vecDetails_fr[i];
    return mc->getPath();
}
//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecDetails_fr(int i)
{
    MediaContent* mc = vecDetails_fr[i];
    return mc->getType();
}

//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecProducts_fr(int i)
{
    MediaContent* mc;
    if(i < vecProducts_fr.size())
    {
        mc = vecProducts_fr[i];
        return mc;
    }
}
//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecProducts_fr(int i)
{
    MediaContent* mc = vecProducts_fr[i];
    return mc->getPath();
}
//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecProducts_fr(int i)
{
    MediaContent* mc = vecProducts_fr[i];
    return mc->getType();
}

//-------------------------------------------------------------------------
MediaContent* Gesture::getFromvecProvider_fr(int i)
{
    MediaContent* mc;
    if(i < vecProvider_fr.size())
    {
        mc = vecProvider_fr[i];
        return mc;
    }
}

//-------------------------------------------------------------------------
string Gesture::getPathByIndexFromvecProvider_fr(int i)
{
    MediaContent* mc = vecProvider_fr[i];
    return mc->getPath();

}

//-------------------------------------------------------------------------
int Gesture::getTypeByIndexFromvecProvider_fr(int i)
{
    MediaContent* mc = vecProvider_fr[i];
    return mc->getType();

}

//-------------------------------------------------------------------------
int Gesture::getSizevecOverview_fr()
{
    return vecOverview_fr.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecDetails_fr()
{
    return vecDetails_fr.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecProducts_fr()
{
    return vecProducts_fr.size();
}

//-------------------------------------------------------------------------
int Gesture::getSizevecProvider_fr()
{
    return vecProvider_fr.size();
}

//-------------------------------------------------------------------------
void Gesture::addTovecOverview_fr(MediaContent* mc)
{

    vecOverview_fr.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecDetails_fr(MediaContent* mc)
{
    vecDetails_fr.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecProducts_fr(MediaContent* mc)
{
    vecProducts_fr.push_back(mc);
}

//-------------------------------------------------------------------------
void Gesture::addTovecProvider_fr(MediaContent* mc)
{
    vecProvider_fr.push_back(mc);
}
//-------------------------------------------------------------------------
void Gesture::setMainimage_path_de(string p)
{
    mainimage_path_de = p;
}

//-------------------------------------------------------------------------
void Gesture::setMainimage_path_fr(string p)
{
    mainimage_path_fr = p;
}

//-------------------------------------------------------------------------
string Gesture::getMainimage_path_de()
{
    return mainimage_path_de;
}

//-------------------------------------------------------------------------
string Gesture::getMainimage_path_fr()
{
    return mainimage_path_fr;
}
//-------------------------------------------------------------------------
void Gesture::toString()
{
    cout << "Gesture ID:" << id << " THEME: " << theme << endl;
}
//-------------------------------------------------------------------------
void Gesture::setCO2Impact(float co2)
{
    co2Impact = co2;
}
//-------------------------------------------------------------------------
float Gesture::getCO2Impact()
{
    return co2Impact;
}

//-------------------------------------------------------------------------
bool Gesture::hasLogoIncluded()
{
    return logoincluded;
}

//-------------------------------------------------------------------------
void Gesture::setLogoIncluded()
{
    logoincluded = true;
}

//-------------------------------------------------------------------------
void Gesture::setLogoPath(string p)
{
    logo_path = p;
}

//-------------------------------------------------------------------------
string Gesture::getLogoPath()
{
    return logo_path;
}







