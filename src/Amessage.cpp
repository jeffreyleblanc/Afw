/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Amessage.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Amessage.h"

Amessage::Amessage()
{
	sender = NULL;
}

Amessage::Amessage(std::string msg)
{
	sender = NULL;
	message = msg;
}

Amessage::Amessage( std::string msg, int INT)
{
	sender = NULL;
	message = msg;
	mInt = INT;
}

Amessage::Amessage( std::string msg, int INT, Aobj* sender_)
{
	sender = sender_;
	message = msg;
	mInt = INT;
}