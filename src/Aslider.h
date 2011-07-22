/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aslider.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "Atextbox.h"
#include "Arect.h"

class Aslider : public Aobj
{
public:
	
	Aslider(float x_, float y_, float minV_, float maxV_);
	//Value Functions
	void attachToFLOAT(float* target);
	float getValue();
	void setValue(float value);
	void setValueInteraction(Vec3f P);
	void updateValueIndicator();
	void setValueToInterval();
	//Interaction Functions
	bool pointInside(Vec3f P);
	bool handleEvent(Aevent* evt);
	//Other Functions
	void makeTitle();
	void makeTitle(std::string T);
	float getHeight();
	
	//Values
	float currentValue;
	float minValue;
	float maxValue;
	float interval;
	float button_pos;
	//Targets
	int targetType; //! Not being used...
	float* targetFLOAT;
	
	//Layout/Geometry
	float offDown;
	float h;
	float w;
	
	//interaction
	bool clicked; //! this is used to ensure you have to click not just drag
	
	//Graphical Elements
	std::string TitleText;
	Atextbox*	Title;
	Arect* frame;
	Arect* channel;
	Arect* indicator;
	//Colors //! not currently used
	Acolor channelColor;
	Acolor indicatorColor;
	Acolor frameColor;
};