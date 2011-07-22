/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aradiobuttons.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "Auicontainer.h"

class AuiIntRadioButtons : public Auicontainer
{
public:
	
	AuiIntRadioButtons(std::string TitleText) : Auicontainer(TitleText)
	{ Curr=NULL; IntTarget = NULL; };
	AuiIntRadioButtons(std::string TitleText, char Or) : Auicontainer(TitleText, Or)
	{ Curr=NULL; IntTarget = NULL; };
	AuiIntRadioButtons(std::string TitleText, char Or, bool startOpen) : Auicontainer(TitleText, Or, startOpen)
	{ Curr=NULL; IntTarget = NULL; };
	
	void processMessage(Amessage* msg);
	void setActiveIntButtonByVal(int val);
	void addIntButton(std::string TitleText, int val);
	void attachToInt(int* val);
	float getHeight();
	
	AbuttonInt* Curr;
	std::vector<AbuttonInt*> buttons; //redundant but hey...
	// Targets
	int* IntTarget;
	Aobj* AobjTarget;
};
