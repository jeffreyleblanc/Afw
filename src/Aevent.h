/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

#include "Acolor.h"

enum{
	NULL_EVENT,
	MOUSE_DOWN_EVENT,
	MOUSE_PRESS_EVENT,
	MOUSE_CLICK_EVENT,
	MOUSE_UP_EVENT,
	MOUSE_RELEASE_EVENT,
	MOUSE_MOVE_EVENT,
	MOUSE_DRAG_EVENT,
	MOUSE_HOLD_EVENT,
	KEY_PRESS_EVENT,
};

class Aevent
{
public:
	Aevent();
	void reset();
	
	int Type;
	char key;
	int keyCode;
	ci::Vec3f mousePos;
};