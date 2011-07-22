/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aradiobuttons.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Aradiobuttons.h"

void AuiIntRadioButtons::processMessage(Amessage* msg)
{
	if(msg->message.compare("ButtonEvent") == 0){
		if(msg->message.compare("ButtonEvent") == 0 && msg->sender == openToggle){
			uiHolder->visible = ! uiHolder->visible;
			return;
		}
		if( msg->mInt = 1)
			if( msg->sender != Curr){
				if(Curr != NULL)
					Curr->deSelect();
				Curr = (AbuttonInt*) msg->sender;
				//send message that something has changed...
				if(AobjTarget != NULL)
					AobjTarget->recieveMessage( new Amessage("IntRadioButtonChange", 0, this) );
			}
	}
}

//? this is definitely confusing...
void AuiIntRadioButtons::setActiveIntButtonByVal(int val)
{
	for(int i=0; i<buttons.size(); i++)
		if( buttons.at(i)->currentValue == val ){
			if(Curr != NULL)
				Curr->deSelect();
			Curr = buttons.at(i);
			Curr->button->color.set(1,1,0);
			//send message that something has changed...
			if(AobjTarget != NULL)
				AobjTarget->recieveMessage( new Amessage("IntRadioButtonChange", 0, this) );
		}
}

void AuiIntRadioButtons::addIntButton(std::string TitleText, int val)
{
	AbuttonInt* tmpB = new AbuttonInt(val);
	tmpB->makeTitle(TitleText);
	tmpB->attachToAobj(this);
	buttons.push_back(tmpB);
	addUiElement(tmpB);
}

void AuiIntRadioButtons::attachToInt(int* val)
{
	IntTarget = val;
	//update all the buttons
	for(int i=0; i<buttons.size(); i++)
		buttons.at(i)->attachToInt(val);
}

float AuiIntRadioButtons::getHeight()
{
	float totalHeight = h;
	for(int i=0; i<buttons.size(); i++)
		totalHeight += buttons.at(i)->getHeight() + margin;
	return totalHeight;
}
