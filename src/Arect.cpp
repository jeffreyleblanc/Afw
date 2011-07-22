/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Arect.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Arect.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Arect::Arect(float w_, float h_)
{
	w = w_;
	h = h_;
	color.set(0,1,1,0.5f);
	useRectBoundaries = true;	
}

void Arect::render()
{
	applyColor(color);
	Rectf rect( 0, 0, w, h );
	gl::drawSolidRect( rect );
}