#include "TranspButt.h"

#include "ofMain.h"

#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::touppe

//------------------------------------------
TranspButt::TranspButt(int px, int py, int w, int h)
{
    posx = px;
    posy = py;
    width = w;
    height = h;
    active = true;
}
//------------------------------------------
TranspButt::~TranspButt()
{

}
//------------------------------------------
bool TranspButt::isclicked(int px, int py)
{


    if(active==true)
    {
        if(px >= posx && px <= posx+width)
        {
            if(py >= posy && py <= posy+height )
            {
                return true;
            }
        }
    }
    return false;
}
void TranspButt::setpos(int x,int y)
{
    posx = x;
    posy = y;
}
//------------------------------------------
void TranspButt::setActive()
{
    active=true;
}
//------------------------------------------
void TranspButt::setNoActive()
{
    active=false;
}
//------------------------------------------
bool TranspButt::isActive()
{
    return active;
}
//------------------------------------------
void TranspButt::toString()
{
    cout << "TranspButton in x " << posx << " y " << posy << endl;
}

int TranspButt::getPosy()
{
    return posy;
}
