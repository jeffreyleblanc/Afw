/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aimage.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "Abutton.h" //? this is a poor way to handle linking...


class Aimage : public Aobj
{
public:
	Aimage();
	
	virtual void render();
	//Loading Functions	
	bool loadFromResource(std::string resourceName_);
	bool loadFromFile(std::string sourcePath_);
	bool loadFromURL(std::string sourceURL_);
	//Size Control
	void resize(float newW, float newH);
	void scale(float percent);
	void setWidth(float newW);
	void setHeight(float newH);
	
	gl::Texture imgTexture;
	std::string sourcePath;
	//? We should enum sourcePath type
};




