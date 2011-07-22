/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Axml.cpp
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Axml.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//Declare static variables
Axml* Axml::theInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// Constructor and Instance Handler
//////////////////////////////////////////////////////////////////////////

Axml::Axml()
{}

Axml* Axml::getInstance()
{
	if ( theInstance == NULL )
		theInstance = new Axml();
	return theInstance;
}

//////////////////////////////////////////////////////////////////////////
// serialize non primitives
//////////////////////////////////////////////////////////////////////////

XmlTree Axml::getXmlTree(Vec3f* vec, std::string varName)
{
	XmlTree xml( varName, "");
	xml.setAttribute("class", "Vec3f");
	xml.setAttribute("x", vec->x);
	xml.setAttribute("y", vec->y);
	xml.setAttribute("z", vec->z);
	return xml;
}

XmlTree Axml::getXmlTree(Acolor* color, std::string varName)
{
	XmlTree xml( varName, "");
	xml.setAttribute("class", "Acolor");
	xml.setAttribute("r", color->r);
	xml.setAttribute("g", color->g);
	xml.setAttribute("b", color->b);
	xml.setAttribute("a", color->a);
	return xml;
}

//////////////////////////////////////////////////////////////////////////
// deserialize from XmlTree attributes
//////////////////////////////////////////////////////////////////////////

void Axml::setFromXmlTreeAttribute(Vec3f* vec, XmlTree* xml)
{
	setFromXmlTreeAttribute<float>(&(vec->x), "x", xml);
	setFromXmlTreeAttribute<float>(&(vec->y), "y", xml);
	setFromXmlTreeAttribute<float>(&(vec->z), "z", xml);
}

void Axml::setFromXmlTreeAttribute(Acolor* color, XmlTree* xml)
{
	setFromXmlTreeAttribute<float>(&(color->r), "r", xml);
	setFromXmlTreeAttribute<float>(&(color->g), "g", xml);
	setFromXmlTreeAttribute<float>(&(color->b), "b", xml);
	setFromXmlTreeAttribute<float>(&(color->a), "a", xml);
}

//////////////////////////////////////////////////////////////////////////
// handle AobjRegistry
//////////////////////////////////////////////////////////////////////////

void Axml::clearAobjRegistry()
{
	AobjRegistry.clear(); //? confirm this is working correctly
}

void Axml::addToAobjRegistry(Aobj* obj)
{
	AobjRegistry.push_back(obj);	
}
