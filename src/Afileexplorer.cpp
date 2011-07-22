/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Afileexplorer.cpp
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/11/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Afileexplorer.h"

Afileexplorer::Afileexplorer()
{
	//Layout/Geometry
	offDown = 12;
	h = 14;
	w = 160;
	
	//Graphical Elements
	TitleText = "File Explorer";
	Title = NULL;
	
	//here make the frame so its behind...
	frame = new Arect(w+2, h+offDown+2);
	frame->position.set(-1,-1,0);
	addChild(frame);
	
	//here make the frame so its behind...
	button = new Arect(h, h);
	button->color.set255(100);
	button->position.set(0,12,0);
	addChild(button);
	
	FilePath = new Atextbox();
	FilePath->color.set(1);
	FilePath->setFont("Arial", 10);
	FilePath->makeTexture( "file_path" );
	FilePath->position.set(h+2,offDown,0);
	addChild(FilePath);
	
	makeTitle();
}

////////////////////////////////////////////////////////////////////////
// Layout Functions !g!
///////////////////////////////////////////////////////////////////////

void Afileexplorer::makeTitle()
{
	if( Title != NULL) removeChild(Title); //? sort of a hack
	
	Title = new Atextbox();
	Title->color.set(1);
	Title->setFont("Arial", 10);
	Title->makeTexture( TitleText );
	Title->position.set(0,-1,0);
	addChild(Title);
}

void Afileexplorer::makeTitle(std::string T)
{
	TitleText = T;
	makeTitle();
}

float Afileexplorer::getHeight()
{
	return h + offDown;
}

////////////////////////////////////////////////////////////////////////
// Event Functions !g!
///////////////////////////////////////////////////////////////////////

bool Afileexplorer::pointInside(Vec3f P){
	return button->pointInside(P-button->position);
}

bool Afileexplorer::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT )
	{
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint ))
		{
			//! Not threaded...
			try {
				std::string p = getOpenFilePath( CMN->rootResourcePath );
				if( ! p.empty() ) { // an empty string means the user canceled
					FilePath->makeTexture( p );
				}
			}
			catch( ... ) {
				console() << "Afileexplorer experienced an event error" << std::endl;
				return false;
			}
			return true;
		}
	}
	return false;
}
