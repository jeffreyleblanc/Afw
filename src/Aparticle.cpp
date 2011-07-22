/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aparticle.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "physicscore.h"

Aparticle::Aparticle()
{
	r = Rand::randFloat(10.0f, 20.0f);
	m = 10.0f;
	color.setRandom();
	
	grabbed = false;
	registered = false;
	
	vel.set(0,0,0);
	acc.set(0,0,0);
	force.set(0,0,0);
	
	COLLIDER = NULL;
}

//////////////////////////////////////////////////////////////////////////
// Handle Spring Connections Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aparticle::addSpring(Aspring* S)
{
	springs.push_back(S);		
}

void Aparticle::removeSpring(Aspring* S)
{
	for(int i = springs.size()-1; i>-1; i--)
		if( springs.at(i) == S){
			springs.erase(springs.begin()+i);
			break;
		}		
}

Aspring* Aparticle::popSpring()
{
	Aspring* tmpS = NULL;
	if(springs.size() > 0){
		tmpS = springs.at(0);
		springs.erase(springs.begin());
	}
	return tmpS;
}


//////////////////////////////////////////////////////////////////////////
// Render Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aparticle::render()
{
	applyColor(color);
	gl::drawSolidCircle( Vec2f(0,0), r);
	
	if(registered){
		gl::color(ColorA(0, 1, 0, 1));
		Rectf rect( -r, -r, r, r );
		gl::drawStrokedRect( rect );
	}
}

//////////////////////////////////////////////////////////////////////////
// Update Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aparticle::update()
{
	updateMotion();
}

void Aparticle::updateMotion()
{
	//! put in velocity and/or acc limits
	vel += acc;
	position += vel;
	vel *= 0.99f;
	
	acc.set(0,0,0);
	force.set(0,0,0);
}
void Aparticle::addForce(Vec3f f)
{
	acc += ( f / m );
}

//////////////////////////////////////////////////////////////////////////
// Boundary Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Aparticle::pointInside(Vec3f P){
	if( P.lengthSquared() < r*r )
		return true;
	else return false; 
}

//////////////////////////////////////////////////////////////////////////
// Event Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Aparticle::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT)
	{		
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint )){
			grabbed = true;
			vel.set(0,0,0);
			acc.set(0,0,0);
			if(COLLIDER->mEditor != NULL)
				COLLIDER->mEditor->registerParticle(this);
			return true;
		}
	}
	else if(evt->Type == MOUSE_DRAG_EVENT && grabbed == true)
	{
		position = parent->globalToLocal(evt->mousePos);
		vel.set(0,0,0);
		acc.set(0,0,0);
		return true;
	}
	else if(evt->Type == MOUSE_UP_EVENT && grabbed == true)
	{
		grabbed = false;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Xml Functions !g!
//////////////////////////////////////////////////////////////////////////

XmlTree Aparticle::toXml()
{ 
	XmlTree p( "Aparticle", "" );
	p.push_back( getCoreXml() );
	//attributes
	p.push_back( XML->getXmlTree(&color, "color"));
	p.push_back( XmlTree( "r", toString(r) ) );
	p.push_back( XmlTree( "m", toString(m) ) );
	//references
	if(COLLIDER != NULL){ 
		p.push_back( XmlTree( "COLLIDER", COLLIDER->Ref ) );
	}
	XmlTree Springz( "springs", "");
	for(int i=0; i<springs.size(); i++){
		Springz.push_back( XmlTree( "s", springs.at(i)->Ref ) );
	}
	p.push_back(Springz);
	//return result
	return p;
}

void Aparticle::setFromXml(XmlTree* xml)
{
	XmlTree core = xml->getChild( "core" );
	setCoreXml(&core);
	//set the specific attributes:
	XML->setFromXmlTreeChild(&(r), "r", xml);
	XML->setFromXmlTreeChild(&(m), "m", xml);
	XML->setFromXmlTreeAttribute(&(color), &(xml->getChild("color")));
	//add self to registry
	XML->addToAobjRegistry(this);
	//save the node
	xmlSave = *xml;
}

void Aparticle::linkFromXml()
{	
	std::string COLLIDERRef;
	XML->setFromXmlTreeChild(&COLLIDERRef, "COLLIDER", &xmlSave);
	COLLIDER = (Acollider*) findInXmlRegistry(COLLIDERRef);
	
	//do particles
	XmlTree Springz = xmlSave.getChild("springs");
	for( XmlTree::Iter child = Springz.begin(); child != Springz.end(); ++child ){
		if( child->getTag().find("s") == 0)
		{
			std::string LinkRef;
			XML->setFromXmlTreeValue(&LinkRef, &*child);
			Aspring* temp = (Aspring*) findInXmlRegistry(LinkRef);
			if(temp != NULL )
			   springs.push_back( temp );
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// AparticleEditor
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

AparticleEditor::AparticleEditor() : Auicontainer("Aparticle Editor")
{
	focus = NULL;
	
	radius_Slider = new Aslider(600.0f, 300.0f, 10.0f, 50.0f);
	radius_Slider->interval = 0.01f;
	radius_Slider->makeTitle("radius");
	addUiElement(radius_Slider);
	
	color_Editor = new Auicoloreditor("color", 'L', false);
	addUiElement(color_Editor);	
}

void AparticleEditor::attachTo(Aparticle* p) //? Deal with NULL input
{
	focus = p;
	radius_Slider->attachToFLOAT( &(focus->r) );
	color_Editor->attachToColor( &(focus->color) );
	
	//set registered for it:
	p->registered = true;
}

void AparticleEditor::detatchFrom(Aparticle* p)
{
	if( focus == p && p != NULL){
		radius_Slider->targetFLOAT = NULL ;
		color_Editor->targetColor = NULL ;
		focus = NULL;
		p->registered = false;
	}
}
