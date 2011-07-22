/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Atextentrybox.h
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Atextbox.h"
#include "Arect.h"

//? This one needs come work...

class Atextentrybox : public Aobj
{
public:
	
	Atextentrybox();
	//Boundary Functions
	float getHeight();
	//Title update functions
	void makeTitle();
	void makeTitle(std::string T);
	//Text Update
	void updateText();
	void appendChar(char c);
	void removeChar();
	//Interaction Functions
	bool pointInside(Vec3f P);
	bool handleEvent(Aevent* evt);
	
	//Layout/Geometry
	float offDown;
	//Editable state
	bool editable;
	//Graphical Elements
	std::string TitleText;
	std::string Text;
	Atextbox*	Title;
	Atextbox*	FilePath;
	Arect* frame;
	Arect* button;
	
	//? Could use a string* to update a string...
};