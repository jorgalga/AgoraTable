#include "Htmlstring.h"

Htmlstring::Htmlstring()
{

}
Htmlstring::Htmlstring(string t, bool b)
{
    text = t;
    bold = b;
}
Htmlstring::~Htmlstring()
{

}

string  Htmlstring::getText()
{
    return text;
}

bool  Htmlstring::isBold()
{
    return bold;
}
