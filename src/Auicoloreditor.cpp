/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Auicoloreditor.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Auicoloreditor.h"

void Auicoloreditor::init_AuicolorEditor()
{
	targetColor = NULL;
	
	//Make the Color Sliders;
	
	rSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	rSlider->makeTitle("red");
	addUiElement(rSlider);
	
	gSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	gSlider->makeTitle("green");
	addUiElement(gSlider);
	
	bSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	bSlider->makeTitle("blue");
	addUiElement(bSlider);
	
	aSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	aSlider->makeTitle("alpha");
	addUiElement(aSlider);
}

void Auicoloreditor::attachToColor(Acolor* target)
{
	if(target == NULL)
		return;
	
	targetColor = target;
	rSlider->attachToFLOAT( &(target->r) );
	gSlider->attachToFLOAT( &(target->g) );
	bSlider->attachToFLOAT( &(target->b) );
	aSlider->attachToFLOAT( &(target->a) );
}


