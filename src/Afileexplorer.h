/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Afileexplorer.h
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "Abutton.h"
#include "Atextbox.h"
#include "Arect.h"

class Afileexplorer : public Aobj
{
public:
	
	Afileexplorer();
	//Layout Functions
	void makeTitle();
	void makeTitle(std::string T);
	float getHeight();	
	//Interaction Functions
	bool pointInside(Vec3f P);
	bool handleEvent(Aevent* evt);
		
	//Layout/Geometry
	float offDown;
	
	//Graphical Elements
	std::string TitleText;
	Atextbox*	Title;
	Atextbox*	FilePath;
	Arect* frame;
	Arect* button;
	
	//? Could add a string target
};