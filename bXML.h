/*
 * bXML.h
 *
 *  Created on: Jan 25, 2016
 *      Author: okasha
 */

#ifndef BXML_INCLUDED
#define BXML_INCLUDED







#ifndef TINYXML_INCLUDED
#include "tinyXML/tinyxml.h"
#endif


 const char * getText(TiXmlElement *elem)
{

    for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        if(text == NULL)
            continue;

        return text->ToText()->Value();
    }
    return NULL;
}

/*

 to get attributes from tags

    for example elem contain XML tag <variable>

    where in the file

    <variable var1="_val_01"/>

   [call] getAttribute(elem,"var1")
   [return] _val_01


  :: where elem is object of type TiXmlElement contain XML Tag <variable>

*/

const char * getAttribute(TiXmlElement *elem,const char *nAtrr)
{
    const char *attr;

    attr = elem->Attribute(nAtrr);
    if(attr != NULL)
    {
        return attr;
    }

    return NULL;
}




#endif /* BXML_H_ */
