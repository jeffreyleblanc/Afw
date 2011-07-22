/*
 *  Asystemroot.cpp
 *  AfwBlockTest
 *
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Asystemroot.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Asystemroot::Asystemroot()
{
	//make the Collider
	COLLIDE =  new Acollider();
	COLLIDE->position.set(25,25,0);
	//COLLIDE->makeCloud();
	addChild(COLLIDE);
	//COLLIDE->setFromXmlFile(CMN->rootResourcePath+"text_out.xml");
	
	//Make the collider editor
	COLLIDEEDIT = new AcolliderEditor();
	COLLIDEEDIT->position.set(800,100,0);
	COLLIDEEDIT->attachToCollider(COLLIDE);
	COLLIDE->mEditor = COLLIDEEDIT;
	addChild(COLLIDEEDIT);
	
	//make the particle editor:
	ParticleEditor = new AparticleEditor();
	ParticleEditor->position.set(800,500,0);
	addChild(ParticleEditor);
	COLLIDEEDIT->particleEditor = ParticleEditor;
	
	//make the spring editor:
	SpringEditor = new AspringEditor();
	SpringEditor->position.set(800,600,0);
	addChild(SpringEditor);
	COLLIDEEDIT->springEditor = SpringEditor;
	
	//Add Cinder Logo and my Website...
	
	Aimage* Cinder_Logo =  new Aimage();
	Cinder_Logo->loadFromURL("http://libcinder.org/media/images/logo.png");
	Cinder_Logo->setHeight(50);
	Cinder_Logo->draggable = true;
	Cinder_Logo->position.set(25, 700, 0);
	addChild(Cinder_Logo);
	
	Atextbox* JeffreyLeBlanc =  new Atextbox();
	JeffreyLeBlanc->makeTexture("www.jeffreyleblanc.org");
	JeffreyLeBlanc->draggable = true;
	JeffreyLeBlanc->color.set(0.4f);
	JeffreyLeBlanc->position.set(200, 730, 0);
	addChild(JeffreyLeBlanc);
	
};