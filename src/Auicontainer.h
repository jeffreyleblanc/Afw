/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Auicontainer.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "Atextbox.h"
#include "Abutton.h"
#include "Arect.h"

class Auicontainer : public Aobj
{
public:
	
	Auicontainer(std::string TitleText);
	Auicontainer(std::string TitleText, char Or);
	Auicontainer(std::string TitleText, char Or, bool startOpen);
	void init_Auicontainer(std::string TitleText, char Or, bool startOpen);
	void addUiElement(Aobj* uiElement);
	void processMessage(Amessage* msg);
	void setOrientation(char oR);
	
	Aobj* uiHolder;
	Atextbox* Title;
	Abutton* openToggle;
	
	Arect* frame;
	
	Vec3f openPoint;
	float margin;
	
	char Orientation; //'V', 'L' or 'R' //? Should enum
};


