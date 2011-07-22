/*
 *  Asystemroot.h
 *  AfwBlockTest
 *
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Afw.h"

class Asystemroot : public Aobj
{
public:
	Asystemroot();	
	
	Acollider* COLLIDE;
	AcolliderEditor* COLLIDEEDIT;
	AparticleEditor* ParticleEditor;
	AspringEditor* SpringEditor;
	
	
};