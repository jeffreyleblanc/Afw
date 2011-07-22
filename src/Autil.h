/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Autil.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "time.h"

#define PI 3.14159
#define base62alphabet "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

class Aobj;

std::string toInverseBase62(int val);
std::string timeBase62();

class Autil{
public:	
	Autil();
	static Autil* getInstance();
	void setResourceReference();

	std::string rootResourcePath;
private:
	static Autil* theInstance;
};