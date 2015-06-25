#include "MediaContent.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

//---------------------------------------------------
MediaContent::MediaContent ()
{

}

//---------------------------------------------------
MediaContent::MediaContent (string p, int t)
{
    path = p;
    type = t;
}

//---------------------------------------------------
MediaContent::~MediaContent ()
{

}

//---------------------------------------------------
string MediaContent::getPath()
{
    return path;
}

//---------------------------------------------------
int MediaContent::getType()
{
    return type;
}

//---------------------------------------------------
void MediaContent::toString()
{
    switch(type)
    {
        case 1:{cout << "Media Content Type IMAGE" << endl; }
        case 2:{cout << "Media Content Type VIDEO" << endl;}
        case 3:{cout << "Media Content Type PDF" << endl;}
    }
}
