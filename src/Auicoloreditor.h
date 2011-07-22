/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Auicoloreditor.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Auicontainer.h"
#include "Aslider.h"

class Auicoloreditor : public Auicontainer
{
public:

	Auicoloreditor(std::string TitleText) : Auicontainer(TitleText)
		{ init_AuicolorEditor(); };
	Auicoloreditor(std::string TitleText, char Or) : Auicontainer(TitleText, Or)
		{ init_AuicolorEditor(); };
	Auicoloreditor(std::string TitleText, char Or, bool startOpen) : Auicontainer(TitleText, Or, startOpen)
		{ init_AuicolorEditor(); };
	
	void init_AuicolorEditor();
	virtual void attachToColor(Acolor* target);
	
	Aslider* rSlider;
	Aslider* gSlider;
	Aslider* bSlider;
	Aslider* aSlider;
	
	Acolor* targetColor;
	Acolor mirrorColor; //? Not currently used
};
