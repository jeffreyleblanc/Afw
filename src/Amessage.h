/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Amessage.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Aevent.h"

class Amessage
{
public:
	Amessage();
	Amessage( std::string msg);
	Amessage( std::string msg, int INT);
	Amessage( std::string msg, int INT, Aobj* sender_);

	std::string message;
	float mFloat;
	int mInt;
	bool mBool;
	std::string mString;
	ci::Vec3f mVec3f;
	Acolor mAcolor;
	Aobj* sender;
	//! A future version should include a dictionary
};