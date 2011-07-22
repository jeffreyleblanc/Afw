/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Acolor.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Acolor.h"

void Acolor::set(float R, float G, float B)
{
	r = R;
	g = G;
	b = B;
	a = 1;
}

void Acolor::set(float R, float G, float B, float A)
{
	r = R;
	g = G;
	b = B;
	a = A;
}


void Acolor::set(float gray)
{
	r = g = b =gray; a=1;
}

void Acolor::set255(float R, float G, float B)
{
	r = R/255.0f;
	g = G/255.0f;
	b = B/255.0f;
	a = 1;
}

void Acolor::set255(float gray)
{
	r = g = b = gray/255.0f;
	a = 1;
}

void Acolor::setRandom()
{
	r = ci::Rand::randFloat(0.0f, 1.0f);
	g = ci::Rand::randFloat(0.0f, 1.0f);
	b = ci::Rand::randFloat(0.0f, 1.0f);
	a = ci::Rand::randFloat(0.0f, 1.0f);
}