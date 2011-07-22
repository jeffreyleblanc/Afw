/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Arect.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 
#include "Aobj.h"

class Arect : public Aobj
{
public:
	
	Arect(float w_, float h_);
	void render();
	
	Acolor color;
};
