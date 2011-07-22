/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Acolor.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include "Autil.h"

class Acolor : public ci::ColorA
{
public:
	Acolor() : ci::ColorA(1,1,1,1) {};
	Acolor(float x, float y, float z) : ci::ColorA(x, y, z, 1) {};
	Acolor(float x, float y, float z, float a) : ci::ColorA(x, y, z, a) {};
	
	void set(float R, float G, float B);
	void set(float gray);
	void set(float R, float G, float B, float A);
	
	void set255(float R, float G, float B);
	void set255(float gray);
	
	void setRandom();
};