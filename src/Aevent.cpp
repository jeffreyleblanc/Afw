/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */
/*
 *  Aevent.cpp
 *  v App
 *
 *  Created by Jeffrey LeBlanc on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Aevent.h"

Aevent::Aevent()
{
	Type = NULL_EVENT;
	key = 'a';
	keyCode = 0;
	mousePos.set(0,0,0);
}

void Aevent::reset()
{
	Type = NULL_EVENT;
	key = 'a';
	keyCode = 0;
	mousePos.set(0,0,0);
}

