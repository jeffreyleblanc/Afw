/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Axml.h
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/1/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "cinder/Xml.h"
#include <vector>
#include "Amessage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Axml
{
public:
	
	Axml();
	static Axml* getInstance();
	//serialize non primitives
	XmlTree getXmlTree(Vec3f* vec, std::string varName);
	XmlTree getXmlTree(Acolor* color, std::string varName);
	//deserialize from XmlTree attributes
	template<typename T>
	bool setFromXmlTreeAttribute(T* var, std::string varName, XmlTree* xml){
		if( xml->hasAttribute(varName) ){
			*var = xml->getAttributeValue<T>(varName);
			return true;
		} else return false;		
	};
	void setFromXmlTreeAttribute(Acolor* color, XmlTree* xml);
	void setFromXmlTreeAttribute(Vec3f* vec, XmlTree* xml);
	//deserialize from the children of an XmlTree
	template<typename T>
	bool setFromXmlTreeChild(T* var, std::string varName, XmlTree* xml){
		if( xml->hasChild(varName) ){
			*var = xml->getChild(varName).getValue<T>();
			return true;
		} else return false;		
	};
	//deserialize from the value of an XmlTree
	template<typename T>
	bool setFromXmlTreeValue(T* var, XmlTree* xml){
		*var = xml->getValue<T>();
		return true;
	};
	//handle AobjRegistry
	void clearAobjRegistry();	
	void addToAobjRegistry(Aobj* obj);	
	
	//Aobj Registry
	vector<Aobj*> AobjRegistry;
	
private:
	static Axml* theInstance;
};