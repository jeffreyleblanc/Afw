/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Abutton.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "Abutton.h"

using namespace ci;
using namespace ci::app;
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/// Abutton 
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

Abutton::Abutton()
{	
	target = NULL;
	
	STATE = 0;
	LASTSTATE = STATE;
	
	h = 20; w = 160;
	oncolor.set255(200.0f);
	offcolor.set255(100.0f);
	
	useRectBoundaries = true;
}

int Abutton::getSTATE()
{	return STATE;  }

void Abutton::update(){
	if(STATE != LASTSTATE)
		LASTSTATE = STATE;		
}

void Abutton::render()
{
	if(STATE == 1)
		applyColor(oncolor);
	else
		applyColor(offcolor);

	Rectf rect( 0, 0, w, h );
	gl::drawSolidRect( rect );
}

bool Abutton::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT){
		if( pointInside( globalToLocal(evt->mousePos))){
			STATE = (STATE+1)%2;
			if(target != NULL){
				target->recieveMessage(new Amessage("ButtonEvent", STATE, this) );
			}
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/// Amsgbutton 
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

Amsgbutton::Amsgbutton()
{
	//Layout/Geometry
	h = 14;
	w = 160;
	
	//Graphical Elements
	TitleText = "";
	Title = NULL;
	
	message = "";
	
	//here make the frame so its behind...
	frame = new Arect(w, h);
	frame->position.set(0,0,0);
	addChild(frame);
	
	targetAobj = NULL;
	useRectBoundaries = true;
}

void Amsgbutton::makeTitle()
{
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 10);
	Title->makeTexture( TitleText );
	Title->position.set(h+5,0,0);
	addChild(Title);
}

void Amsgbutton::makeTitle(std::string T)
{
	TitleText = T;
	makeTitle();
}

void Amsgbutton::attachToAobj(Aobj* obj){
	targetAobj = obj;
}

void Amsgbutton::update(){ //animate the button being clicked
	if(alpha < 1)
		alpha += 0.1f;
}

bool Amsgbutton::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT){
		if( pointInside( globalToLocal(evt->mousePos))){
			if(targetAobj != NULL){
				targetAobj->recieveMessage(new Amessage(message, 0, this) );
			}
			alpha = 0;
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
/// AbuttonTemplate 
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

AbuttonTemplate::AbuttonTemplate()
{
	//Layout/Geometry
	h = 14;
	w = 160;
	
	//Graphical Elements
	TitleText = "";
	Title = NULL;
	
	//here make the frame so its behind...
	frame = new Arect(w+2, h+2);
	frame->position.set(-1,-1,0);
	addChild(frame);
	
	//here make the frame so its behind...
	button = new Arect(h-2, h-2);
	button->color.set(0.4f, 0.4f, 0.4f);
	button->position.set(1,1,0);
	addChild(button);
	
	sendingMessage = false;
	targetAobj = NULL;
	STATE = 0; //actually initialize?
}


//Note need to make this conform to other size...
void AbuttonTemplate::makeTitle()
{
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 10);
	Title->makeTexture( TitleText );
	Title->position.set(h+5,0,0);
	addChild(Title);
}

void AbuttonTemplate::makeTitle(std::string T)
{
	TitleText = T;
	makeTitle();
}

void AbuttonTemplate::attachToAobj(Aobj* obj){
	sendingMessage = true;
	targetAobj = obj;
}

////////////////////////////////////////////////////////////////////////
// Event Functions !g!
///////////////////////////////////////////////////////////////////////

bool AbuttonTemplate::pointInside(Vec3f P){
	return button->pointInside(P-button->position);
}

bool AbuttonTemplate::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT )
	{
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint ))
		{
			setTargetValue();
			if(sendingMessage && targetAobj!= NULL){
				STATE = (STATE+1)%2;
				targetAobj->recieveMessage(new Amessage("ButtonEvent", STATE, this) );
			}
			return true;
		}
	}
	return false;
}