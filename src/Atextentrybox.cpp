/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Atextentrybox.cpp
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Atextentrybox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Atextentrybox::Atextentrybox()
{
	//Layout/Geometry
	offDown = 12;
	h = 14;
	w = 160;
	
	//Graphical Elements
	TitleText = "Text Entry Box";
	Title = NULL;
	
	//here make the frame so its behind...
	frame = new Arect(w+2, h+offDown+2);
	frame->position.set(-1,-1,0);
	addChild(frame);
	
	//here make the frame so its behind...
	button = new Arect(h-2, h-2);
	button->color.set255(100);
	button->position.set(0,12,0);
	addChild(button);
	
	FilePath = new Atextbox();
	FilePath->color.set(1);
	FilePath->setFont("Arial", 10);
	FilePath->position.set(h+2,offDown,0);
	addChild(FilePath);
	
	editable = false;
	
	makeTitle();
}

//////////////////////////////////////////////////////////////////////////
// Title update functions
//////////////////////////////////////////////////////////////////////////

void Atextentrybox::makeTitle()
{
	if( Title != NULL) removeChild(Title); //? sort of a hack
	
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 10);
	Title->makeTexture( TitleText );
	Title->position.set(0,-1,0);
	addChild(Title);
}

void Atextentrybox::makeTitle(std::string T)
{
	TitleText = T;
	makeTitle();
}

//////////////////////////////////////////////////////////////////////////
// Boundary Functions
//////////////////////////////////////////////////////////////////////////

float Atextentrybox::getHeight()
{
	return h + offDown;
}

//////////////////////////////////////////////////////////////////////////
// Text Update
//////////////////////////////////////////////////////////////////////////

void Atextentrybox::updateText(){
	FilePath->setText(Text);
	w = 100; //force width back...
}

void Atextentrybox::appendChar(char c){
	Text += c;
	updateText();
};

void Atextentrybox::removeChar(){
	if(Text.length() > 0)
		Text = Text.substr(0, Text.length()-1);
	updateText();
};


////////////////////////////////////////////////////////////////////////
// Event Functions !g!
///////////////////////////////////////////////////////////////////////

bool Atextentrybox::pointInside(Vec3f P){
	return button->pointInside(P-button->position);
}

bool Atextentrybox::handleEvent(Aevent* evt)
{
	if(evt->Type == KEY_PRESS_EVENT && editable == true)
	{
		if(evt->keyCode == KeyEvent::KEY_BACKSPACE)
			removeChar();
		else
			appendChar(evt->key);
		return true;
	}
	if(evt->Type == MOUSE_PRESS_EVENT )
	{
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint ))
		{
			editable = ! editable;
			//set button color...
			if( editable == true)
				button->color.set(1,1,0);
			else
				button->color.set(0.4f,0.4f,0.4f);
			return true;
		}
	}
	return false;
}