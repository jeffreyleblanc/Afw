/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Abutton.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "cinder/gl/gl.h"
#include "Arect.h"
#include "Atextbox.h"

//? this is a bit of a mess at the moment

//////////////////////////////////////////////////////////////////////////
// Abutton
//////////////////////////////////////////////////////////////////////////

class Abutton : public Aobj //? Needs to be cleaned up
{
public:
	
	Abutton();
	void Abutton_init();
	void update();
	void render();
	int getSTATE();
	bool handleEvent(Aevent* evt);
	
	Acolor oncolor;
	Acolor offcolor;
	int STATE;
	int LASTSTATE;
	Aobj* target;
};

//////////////////////////////////////////////////////////////////////////
// Amsgbutton
//////////////////////////////////////////////////////////////////////////

class Amsgbutton : public Aobj
{
public:
	
	Amsgbutton();
	virtual void attachToAobj(Aobj* obj);
	//Interaction Functions
	bool handleEvent(Aevent* evt);
	//Other Functions
	void makeTitle();
	void makeTitle(std::string T);
	void update();
	
	//Graphical Elements
	std::string TitleText;
	Atextbox*	Title;
	Arect* frame;
	
	//message
	std::string message;
	
	//Aobj hooks
	Aobj* targetAobj;
};

//////////////////////////////////////////////////////////////////////////
// Templates
//////////////////////////////////////////////////////////////////////////

class AbuttonTemplate : public Aobj
{
public:
	
	AbuttonTemplate();
	//Value Functions
	virtual void setTargetValue() {};
	virtual void attachToAobj(Aobj* obj);
	//Interaction Functions
	bool pointInside(Vec3f P);
	bool handleEvent(Aevent* evt);
	//Other Functions
	void makeTitle();
	void makeTitle(std::string T);
	//Handle when deselected
	void deSelect(){
		STATE = 0;
		button->color.set(0.4f, 0.4f, 0.4f);
	};
	
	//Graphical Elements
	std::string TitleText;
	Atextbox*	Title;
	Arect* frame;
	Arect* button;
	
	//Aobj hooks
	int STATE;
	bool sendingMessage;
	Aobj* targetAobj;
};


class AbuttonBool : public AbuttonTemplate
{
public:
	
	AbuttonBool(bool init_bool) : AbuttonTemplate()
	{ currentValue = init_bool; targetValue = NULL; };
	//Value Functions
	void attachToBOOL(bool* target)
	{ targetValue = target; setValue( *targetValue ); };
	bool getValue()
	{ return currentValue; };
	void setValue(bool val)
	{
		currentValue = val;
		if(val) button->color.set(1,1,0);
		else button->color.set(0.4f, 0.4f, 0.4f);
	};
	void toogleValue()
	{ setValue( ! currentValue ); };
	void setTargetValue()
	{
		toogleValue();
		if(targetValue != NULL) *(targetValue) = getValue();
	};
	
	bool currentValue;
	bool* targetValue;
};

class AbuttonInt : public AbuttonTemplate
{
public:
	
	AbuttonInt(int val) : AbuttonTemplate()
	{ currentValue = val; targetValue = NULL; };
	//Value Functions
	void attachToInt(int* target)
	{ targetValue = target; };
	int getValue()
	{ return currentValue; };
	void setValue(int val)
	{ currentValue = val; };
	void setTargetValue()
	{
		if(targetValue != NULL) *(targetValue) = getValue(); //? check on doing this
		button->color.set(1,1,0);
	};
	
	int currentValue;
	int* targetValue;
};

