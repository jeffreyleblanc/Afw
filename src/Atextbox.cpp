/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Atextbox.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Atextbox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Atextbox::Atextbox()
{
	useRectBoundaries = true;
	
	//Text and Textures
	Text = "";
	layout = NULL;
	
	//Look and Feel
	fontName = "Arial";
	fontSize = 18;
	color.set(1.0f);
	backgroundColor.set(0.5f);
	backgroundMargin = 0;
	
	//toggle texture and background
	useTexture = false;
	useBackground = false;
}

//////////////////////////////////////////////////////////////////////////
// Render Functions !g!
//////////////////////////////////////////////////////////////////////////

void Atextbox::render()
{
	if(useBackground)
		renderBackground();
	
	if(useTexture)
		renderTexture();
	else
		renderRawGL();
}

void Atextbox::renderTexture()
{
	if(! texture) return;
	applyColor(color);
	gl::draw( texture, Rectf(0,0, w, h) );
}

void Atextbox::renderRawGL()
{
	//! Looks Awful
	ColorA tmpC = ColorA(color.r, color.g, color.b, color.a*alphaTree);
	gl::drawString( Text, Vec2f( 0, 0 ), tmpC, Font( fontName, fontSize ) );
}

void Atextbox::renderBackground()
{
	applyColor(backgroundColor);
	Rectf rect( -backgroundMargin, -backgroundMargin, w+2*backgroundMargin, h+2*backgroundMargin );
	gl::drawSolidRect( rect );
}


//////////////////////////////////////////////////////////////////////////
// Set text and texture Functions !g!
//////////////////////////////////////////////////////////////////////////

void Atextbox::makeTexture()
{
	if(layout != NULL)
		delete layout;
	
	layout = new TextLayout();
	layout->setFont( Font( fontName, fontSize ) );
	layout->setColor( color );
	layout->clear(ColorA(CM_RGB, 1.0f,1.0f,1.0f,0.0f));
	layout->addLine( Text );
	Surface8u rendered = layout->render(true);//enables alpha
	texture = gl::Texture( rendered ); //? Memory leak
	
	//get the h and w
	h = texture.getCleanHeight(); 
	w = texture.getCleanWidth();
	
	useTexture = true;
}

void Atextbox::makeTexture(std::string newText)
{
	Text = newText;
	makeTexture();
}

void Atextbox::setText(std::string newText)
{
	Text = newText;
}

void Atextbox::setFont(std::string fontName_, float fontSize_)
{
	fontName = fontName_;
	fontSize = fontSize_;
}