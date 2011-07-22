/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aimage.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Aimage.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Aimage::Aimage()
{
	sourcePath = "";	
	useRectBoundaries = true;
}

//////////////////////////////////////////////////////////////////////////
// Loading Functions	
//////////////////////////////////////////////////////////////////////////

bool Aimage::loadFromResource(std::string resourceName_)
{
	sourcePath = resourceName_;
	try {
		imgTexture = gl::Texture( loadImage( loadResource( sourcePath ) ) );
		h = imgTexture.getHeight();
		w = imgTexture.getWidth();
		return true;
	}
	catch( ... ) {
		console() << "Aimage::loadFromResource unable to load: " << sourcePath << std::endl;
		return false;
	}	
}

bool Aimage::loadFromFile(std::string sourcePath_)
{
	sourcePath = sourcePath_;
	try {
		imgTexture = gl::Texture( loadImage( sourcePath ) );
		h = imgTexture.getHeight();
		w = imgTexture.getWidth();
		return true;
	}
	catch( ... ) {
		console() << "Aimage::loadFromFile unable to load: " << sourcePath << std::endl;
		return false;
	}	
}
	
bool Aimage::loadFromURL(std::string sourceURL_)
{
	sourcePath = sourceURL_;
	try {
		Url url( sourcePath );
		imgTexture = gl::Texture( loadImage( loadUrl( url ) ) );
		h = imgTexture.getHeight();
		w = imgTexture.getWidth();
		return true;
	}
	catch( ... ) {
		console() << "Aimage::loadFromURL unable to load: " << sourcePath << std::endl;
		return false;
	}	
}

//////////////////////////////////////////////////////////////////////////
// Size Controls
//////////////////////////////////////////////////////////////////////////

void Aimage::resize(float newW, float newH)
{
	w = newW; h = newH;
}

void Aimage::scale(float percent)
{
	if(imgTexture){
		w = percent * imgTexture.getWidth();
		h = percent * imgTexture.getHeight();
	}
}

void Aimage::setWidth(float newW)
{
	if(imgTexture){
		w = newW;
		h = newW / imgTexture.getAspectRatio();
	}
}

void Aimage::setHeight(float newH)
{
	if(imgTexture){
		w = newH * imgTexture.getAspectRatio();
		h = newH ;
	}
}

void Aimage::render()
{
	if(! imgTexture) return;
	
	//myImage.enableAndBind();
	gl::color(ColorA(1,1,1,alphaTree));
	gl::draw( imgTexture, Rectf(0,0, w, h) );
}