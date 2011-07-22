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

#include "Aslider.h"

Aslider::Aslider(float x_, float y_, float minValue_, float maxValue_)
{
	position.set(x_, y_, 0.0f);
	
	//Values
	minValue = minValue_;
	maxValue = maxValue_;	
	currentValue = minValue; //Change
	interval = 0; //this means not used
	button_pos = 0.5f;
	//Targets
	//int targetType; //Not being used...
	targetFLOAT = NULL;
	
	//Layout/Geometry
	offDown = 12;
	h = 14;
	w = 160;
	
	//Interaction
	clicked = false;
	
	//Graphical Elements
	TitleText = "";
	Title = NULL;
	
	//here make the frame so its behind...
	frame = new Arect(w+2, h+offDown+2);
	frame->position.set(-1,-1,0);
	addChild(frame);
	
	//here make the frame so its behind...
	channel = new Arect(w, h);
	channel->color.set255(100);
	channel->position.set(0,12,0);
	addChild(channel);
	
	//here make the frame so its behind...
	indicator = new Arect(w, h);
	indicator->color.set255(200,200,0);
	indicator->position.set(0,12,0);
	indicator->w = channel->w*(button_pos);
	addChild(indicator);
}

////////////////////////////////////////////////////////////////////////
// Title and Size Functions !g!
///////////////////////////////////////////////////////////////////////

void Aslider::makeTitle()
{
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 10);
	Title->makeTexture( TitleText );
	Title->position.set(0,-1,0);
	addChild(Title);
}

void Aslider::makeTitle(std::string T)
{
	TitleText = T;
	makeTitle();
}

float Aslider::getHeight()
{
	return h + offDown;
}

////////////////////////////////////////////////////////////////////////
// Value Functions !g!
///////////////////////////////////////////////////////////////////////
 
void Aslider::attachToFLOAT(float* target)
{
	targetFLOAT = target;
	setValue( *target );
}

float Aslider::getValue()
{
	return currentValue;
}

void Aslider::setValue(float value)
{
	currentValue = value;
	//bounds check
	if(currentValue < minValue)
		currentValue = minValue;
	else if(currentValue > maxValue)
		currentValue = maxValue;
	//impose interval
	if(interval > 0)
		setValueToInterval();
	//sync slider
	indicator->w = channel->w * (currentValue - minValue) / (maxValue - minValue);
}

void Aslider::setValueToInterval()
{
	if(! (interval > 0 ) ) return;
	   
	float units = currentValue / interval;
	float fractpart, intpart;
	fractpart = modf (units , &intpart);
	if( fractpart >= 0.5f)
		intpart +=1;
	currentValue = intpart * interval;
}

void Aslider::setValueInteraction(Vec3f P)
{
	float button_pos = ((P.x)/w);
	setValue( minValue + button_pos*(maxValue-minValue) );
}

////////////////////////////////////////////////////////////////////////
// Event Functions !g!
///////////////////////////////////////////////////////////////////////
 
bool Aslider::pointInside(Vec3f P){
	return channel->pointInside(P-channel->position);
}

bool Aslider::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT || ( evt->Type == MOUSE_DRAG_EVENT && clicked == true) )
	{
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint ))
		{
			clicked = true;
			setValueInteraction(localPoint);
			if(targetFLOAT != NULL){
				*(targetFLOAT) = getValue();
			}
			return true;
		}
		clicked = false;
	}
	return false;
}
