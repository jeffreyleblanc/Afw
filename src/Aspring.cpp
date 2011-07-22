/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aspring.cpp
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/2/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "physicscore.h"

Aspring::Aspring(Aparticle* p1, Aparticle* p2)
{
	COLLIDER = NULL;
	
	P1 = p1;
	P2 = p2;
	d = 50;
	currD = d;
	k = 0.01f;
	
	registered = false;
	
	//tell the springs about their links...
	tellParticles();
}

Aspring::Aspring()
{
	COLLIDER = NULL;
	
	P1 = NULL;
	P2 = NULL;
	d = 50;
	currD = d;
	k = 0.01f;
	
	registered = false;
}

void Aspring::tellParticles() //! note this will have to be called after linking in deserialization!
{
	if(P1 != NULL)
		P1->addSpring(this);
	if(P2 != NULL)
		P2->addSpring(this);
}

//////////////////////////////////////////////////////////////////////////
// Render Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aspring::render() //! Note depends on parent's position matching
{
	if(P1 == NULL || P2 == NULL)
		return;
	
	applyColor(Acolor(0,1,0));
	renderSpring();
	
	if(registered){
		gl::color(ColorA(1, 1, 0, 1));
		Rectf rect( 0, 10, currD+P1->r+P2->r, -10 );
		gl::drawStrokedRect( rect );
	}
}


void Aspring::renderSpring()
{
	//set desired look
	float endunits = 8;
	int numSpikes = ( d + P1->r+P2->r) / 10;
	float Sht = 4;
	//needed variables
	float currPos = ( currD+P1->r+P2->r);
	float unit = -currPos / (2* (endunits + (float) numSpikes));
	
	glBegin(GL_LINE_STRIP);
	//main line
	gl::vertex( Vec3f(currPos,0,0) );
	currPos += endunits*unit;
	gl::vertex( Vec3f(currPos,0,0) );
	
	for(int i=0; i<numSpikes; i++){
		currPos += unit;
		gl::vertex( Vec3f(currPos,Sht,0) );
		currPos += unit;
		if(i != numSpikes-1)
			gl::vertex( Vec3f(currPos,-Sht,0) );
		else
			gl::vertex( Vec3f(currPos,0,0) );
	}
	currPos += endunits*unit;
	gl::vertex( Vec3f(currPos,0,0) );
	
	glEnd();
}


//////////////////////////////////////////////////////////////////////////
// Update Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aspring::update()
{
	updateSpringDistance();
	updateMatrices();
}

void Aspring::updateSpringDistance()
{
	if(P1 == NULL || P2 == NULL)
		return;
	
	Vec3f apart = P1->position - P2->position;
	currD = apart.length() - (P1->r + P2->r);
	if( fabs(currD-d) > 0.01f)
	{
		apart.normalize();
		apart *= k*(currD-d);
		P2->addForce(apart);
		P1->addForce(-apart);
	}
}

void Aspring::updateMatrices()
{
	if(P1 == NULL || P2 == NULL)
		return;
	
	// the spring is positioned so that its position matched P1, and it is rotated to face them
	position = P1->position;
	//get rotation:
	float rot =  atan2( P1->position.y - P2->position.y, P1->position.x - P2->position.x);
	setRotation(PI+rot); //!? Look into why need to add PI
	
}

//////////////////////////////////////////////////////////////////////////
// Event Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Aspring::pointInside( Vec3f P)
{
	float tol = 10;
	if( (float)P.x >= 0 && (float)P.x <= currD)
	{
		if( (float)P.y >= -tol && (float)P.y <= tol)
			return true;
		else return false;
	}
	else return false;
}

bool Aspring::handleEvent(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT)
	{		
		Vec3f localPoint = globalToLocal(evt->mousePos);
		if( pointInside( localPoint )){
			if(COLLIDER->mEditor != NULL)
				COLLIDER->mEditor->registerSpring(this);
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Xml Functions !g!
//////////////////////////////////////////////////////////////////////////

XmlTree Aspring::toXml()
{ 
	XmlTree p( "Aspring", "" );
	p.push_back( getCoreXml() );
	//attributes
	p.push_back( XmlTree( "k", toString(k) ) );
	p.push_back( XmlTree( "d", toString(d) ) );
	//references
	if(P1 != NULL && P2 != NULL){ 
		p.push_back( XmlTree( "P1", P1->Ref ) );
		p.push_back( XmlTree( "P2", P2->Ref ) );
	}
	if(COLLIDER != NULL){ 
		p.push_back( XmlTree( "COLLIDER", COLLIDER->Ref ) );
	}
	//return result
	return p;
}

void Aspring::setFromXml(XmlTree* xml)
{
	XmlTree core = xml->getChild( "core" );
	setCoreXml(&core);
	//set the specific attributes:
	XML->setFromXmlTreeChild(&(k), "k", xml);
	XML->setFromXmlTreeChild(&(d), "d", xml);
	//add self to registry
	XML->addToAobjRegistry(this);
	//save the xml node
	xmlSave = *xml;
}

void Aspring::linkFromXml()
{	
	std::string p1Ref;
	XML->setFromXmlTreeChild(&p1Ref, "P1", &xmlSave);
	P1 = (Aparticle*) findInXmlRegistry(p1Ref);
	
	std::string p2Ref;
	XML->setFromXmlTreeChild(&p2Ref, "P2", &xmlSave);
	P2 = (Aparticle*) findInXmlRegistry(p2Ref);
	
	std::string COLLIDERRef;
	XML->setFromXmlTreeChild(&COLLIDERRef, "COLLIDER", &xmlSave);
	COLLIDER = (Acollider*) findInXmlRegistry(COLLIDERRef);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

AspringEditor::AspringEditor() : Auicontainer("Aspring edit")
{
	focus = NULL;
	
	d_slide = new Aslider(600.0f, 300.0f, 1.0f, 150.0f);
	d_slide->interval = 1.0f;
	d_slide->makeTitle("d");
	addUiElement(d_slide);
	
	k_slide = new Aslider(600.0f, 300.0f, 0.0f, 0.5f);
	k_slide->interval = 0.01f;
	k_slide->makeTitle("k");
	addUiElement(k_slide);	
}

void AspringEditor::attachTo(Aspring* s) //? Deal with NULL in
{
	focus = s;
	s->registered = true;

	d_slide->attachToFLOAT( &(focus->d) );
	k_slide->attachToFLOAT( &(focus->k) );
}

void AspringEditor::detatchFrom(Aspring* s)
{
	if( focus == s && s != NULL){
		
		d_slide->targetFLOAT = NULL ;
		d_slide->targetFLOAT = NULL ;
		focus = NULL;
		s->registered = false;
	}
}




