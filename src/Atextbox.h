/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Atextbox.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once 
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "Aobj.h"

class Atextbox : public Aobj
{
public:
	
	Atextbox();
	//render	
	virtual void render();
	void renderRawGL();
	void renderTexture();
	void renderBackground();
	//set text and texture
	void setText(std::string newText);
	void setFont(std::string fontName_, float fontSize_);
	void makeTexture();
	void makeTexture(std::string newText);
	
	//Text and Textures
	std::string Text;
	ci::TextLayout* layout;
	gl::Texture	texture; //? should we make this a pointer?
	//Look and Feel
	std::string fontName;
	float fontSize;
	Acolor color; //? really should be called textColor
	Acolor backgroundColor;
	float backgroundMargin;
	//toggle texture and background
	bool useTexture;
	bool useBackground;
};