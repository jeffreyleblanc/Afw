/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Autil.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Autil.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// General Functions /////////////////////////////

std::string toInverseBase62(int val)
{
	std::string out = "";
	while( val != 0){
		int shunt = val % 62;
		out += base62alphabet[shunt];
		val /= 62;
	}
	return out;
}

std::string timeBase62()
{
	time_t seconds;
	seconds = time (NULL);
	return toInverseBase62(seconds);
}

// Autil /////////////////////////////

Autil* Autil::theInstance = NULL;

Autil::Autil()
{
	setResourceReference();
};

Autil* Autil::getInstance()
{
	if ( theInstance == NULL )
		theInstance = new Autil();
	return theInstance;
}

//! Note that this is a hack, and may not work on many machines
void Autil::setResourceReference()
{
	rootResourcePath = getAppPath();
	
	int pos = rootResourcePath.length()-1;
	int slashcount = 0;
	
	while( pos > 0 ){
		if( rootResourcePath[pos] == '/'){
			if(slashcount == 3){
				pos++; break;
			}
			slashcount++;
		}
		pos--;
	}
	rootResourcePath = rootResourcePath.substr(0, pos)+"resources/";
}
