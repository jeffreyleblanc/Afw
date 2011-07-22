/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Auicontainer.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Auicontainer.h"


Auicontainer::Auicontainer(std::string TitleText)
{ init_Auicontainer(TitleText, 'V', true); }


Auicontainer::Auicontainer(std::string TitleText, char Or)
{ init_Auicontainer(TitleText, Or, true); }

Auicontainer::Auicontainer(std::string TitleText, char Or, bool startOpen)
{ init_Auicontainer(TitleText, Or, startOpen); }

void Auicontainer::init_Auicontainer(std::string TitleText, char Or, bool startOpen)
{
	uiHolder = new Aobj();
	uiHolder->visible = startOpen;
	addChild(uiHolder);
	
	//make the Text box
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 12);
	Title->makeTexture( TitleText );
		
	w=160;
	if(Title->w > 160)
		w = Title->w;
	h = Title->h;
	
	//here make the frame so its behind...
	frame = new Arect(w+2, h+2);
	frame->position.set(-1,-1,0);
	addChild(frame);
	addChild(Title);
	
	draggable = true;
	useRectBoundaries = true;
	
	openToggle = new Abutton();
	openToggle->position.set(w-10,2,0);
	openToggle->target = this;
	openToggle->w = 8;
	openToggle->h = 8;
	addChild(openToggle);
	
	margin = 4;
	
	setOrientation(Or);
}

void Auicontainer::setOrientation(char oR)
{
	if(oR == 'V' || oR == 'L' || oR == 'R')
		Orientation = oR;
	
	if(Orientation == 'V')
		openPoint.set(0, h+margin, 0);
	else if(Orientation == 'L')
		openPoint.set(-w-margin, 0, 0);
	else if(Orientation == 'R')
		openPoint.set(w+margin, 0, 0);	
}

void Auicontainer::addUiElement(Aobj* uiElement)
{
	uiHolder->addChild(uiElement);
	uiElement->position.set(openPoint);
	openPoint.y += uiElement->getHeight() + margin;
}

void Auicontainer::processMessage(Amessage* msg)
{
	if(msg->message.compare("ButtonEvent") == 0 && msg->sender == openToggle)
		uiHolder->visible = ! uiHolder->visible;
}