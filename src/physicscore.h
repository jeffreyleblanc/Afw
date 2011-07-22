/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  physicscore.h
 *  Afw
 *
 *  Created by Jeffrey LeBlanc on 7/3/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Aobj.h"
#include "Auicontainer.h"
#include "Aslider.h"
#include "Auicoloreditor.h"
#include "Aradiobuttons.h"
#include "Atextentrybox.h"
#include "Afileexplorer.h"

//head's up:
class Aparticle;
class AparticleContainer;
class AparticleEditor;
class Aspring;
class AspringContainer;
class AspringEditor;
class AcolliderEditor;

//////////////////////////////////////////////////////////////////////////
// Acollider Family
//////////////////////////////////////////////////////////////////////////

class Acollider : public Aobj
{
public:
	
	Acollider();
	//Make members
	void makeCloud();
	void addParticle(Vec3f pos);
	void addParticle(Aparticle* p);
	void addSpring(Aspring* s);
	void deleteParticle(Aparticle* p);
	void deleteSpring(Aspring* S);
	//toggle containers
	void bringParticlesForward();
	void bringSpringsForward();
	//render
	void render();
	//update + physics
	void update();
	void runBoundary();
	void runCollisions();
	bool doCollision(Aparticle* p1, Aparticle* p2);
	void runAttraction();
	bool PureCoulombAttraction(Aparticle* p1, Aparticle* p2);
	//events
	bool handleEvent(Aevent* evt);
	//xml
	bool serializable() { return true; };
	XmlTree toXml();
	void setFromXML(XmlTree* xml);
	bool setFromXmlFile( std::string sub_path);
	void linkFromXml();
	
	//global forces
	float collisionForceStrength;
	float Ke;
	//containers
	AparticleContainer* particles; //? this didn't work if not a pointer? must def go above?
	AspringContainer* springs;
	//editing hooks
	AcolliderEditor* mEditor;
};


class AcolliderEditor : public Auicontainer
{
public:
	
	enum{
		INTERACT,
		ADD_P,
		DELETE_P,
		LINK,
		UNLINK,
		EDIT_P,
		EDIT_S,
	};
	
	AcolliderEditor();
	//Collider registration
	void attachToCollider(Acollider* c);
	void detachFromCollider();
	//Aparticle Handling
	void registerParticle(Aparticle* p);
	void deregisterParticle(Aparticle* p);
	//Aspring Handling
	void registerSpring(Aspring* s);
	//Event Handling
	void backgroundClicked(Vec3f pnt);
	void resetEditState();
	//Message Handling
	void processMessage(Amessage* msg);
	
	//links to sub editors:
	AparticleEditor* particleEditor;
	AspringEditor* springEditor;
	
	//links to things in collider
	Acollider* COLLIDER;
	Aparticle* caughtParticle;
	Aspring* caughtSpring;
	
	//Self UI elements
	Aslider* alphaSlider;
	Aslider* KeSlider;
	Aslider* collideSlider;	
	AbuttonBool* visibleButton;
	//Editing Options
	AuiIntRadioButtons* options;
	//Save File UI
	Atextentrybox* FileNameOut;
	Amsgbutton* SaveFileButton;
	//Load File UI
	Afileexplorer* FilePathIn;
	Amsgbutton* LoadFileButton;

	
	//Current Editor State
	int editState;
};


//////////////////////////////////////////////////////////////////////////
// Aparticle Family
//////////////////////////////////////////////////////////////////////////

class Aparticle : public Aobj
{
public:
	
	Aparticle();
	//spring connections
	void addSpring(Aspring* S);
	void removeSpring(Aspring* S);
	Aspring* popSpring();
	//render
	void render();
	//update
	void update();
	void updateMotion();
	void addForce(Vec3f f);
	//boundary
	bool pointInside(Vec3f P);
	//event
	bool handleEvent(Aevent* evt);
	//xml
	bool serializable() { return true; };
	XmlTree toXml();
	void setFromXml(XmlTree* xml);
	void linkFromXml();
	
	//parent collider
	Acollider* COLLIDER;
	//attributes
	float r;
	float m;
	Acolor color;
	//forces
	Vec3f vel;
	Vec3f acc;
	Vec3f force;
	//interaction
	bool grabbed;
	bool registered;
	//spring connections
	std::vector<Aspring*> springs;
};

class AparticleEditor : public Auicontainer
{
public:
	
	AparticleEditor();
	void attachTo(Aparticle* p);
	void detatchFrom(Aparticle* p);
	
	Aparticle* focus;
	Aslider* radius_Slider;
	Auicoloreditor* color_Editor;
};

class AparticleContainer : public Aobj
{
public:
	AparticleContainer() {};
	void addParticle(Aparticle* p){ addChild((Aobj*) p); };
	Aparticle* getParticle(int index) {return (Aparticle*) getChild(index);};
	int numParticles(){ return numChildren(); };
	//mimic a vector
	int size() { return numChildren(); };
	Aparticle* at(int index){return (Aparticle*) getChild(index);};
	
	//serialize...
	bool serializable() { return true; };
	XmlTree toXml()
	{ 
		XmlTree p( "AparticleContainer", "" );
		p.push_back( getCoreXml() );
		//children
		XmlTree childrenXml("Children","");
		for(int i=0; i<Children.size(); i++)
			if( Children.at(i)->serializable() )
				childrenXml.push_back(Children.at(i)->toXml());
		p.push_back(childrenXml);
		return p;
	};
	
	void setFromXml(XmlTree* xml)
	{
		//set core
		XmlTree core = xml->getChild( "core" );
		setCoreXml(&core);
		//generate the Children:
		XmlTree kids = xml->getChild("Children");
		for( XmlTree::Iter child = kids.begin(); child != kids.end(); ++child ){
			if( child->getTag().find("Aparticle") == 0)
			{
				Aparticle* tmpP = new Aparticle();
				tmpP->setFromXml(&*child); //? proper way to cast?
				addParticle(tmpP); //! Note we are not: addChild(tmpP);
			}
		}
		//add self to the registry
		XML->addToAobjRegistry(this);
	};
	
};


//////////////////////////////////////////////////////////////////////////
// Aspring Family
//////////////////////////////////////////////////////////////////////////

class Aspring : public Aobj
{
public:
	
	Aspring();
	Aspring(Aparticle* p1, Aparticle* p2);
	void tellParticles();
	//render
	void render();
	void renderSpring();
	//update
	void update();
	void updateSpringDistance();
	void updateMatrices();
	//Event Handling
	bool pointInside( Vec3f P);
	bool handleEvent(Aevent* evt);
	//xml
	bool serializable() { return true; };
	XmlTree toXml();
	void setFromXml(XmlTree* xml);
	void linkFromXml();
	
	Acollider* COLLIDER;
	Aparticle* P1;
	Aparticle* P2;
	//attributes
	float d;
	float currD;
	float k;
	//interaction
	bool registered;
};

class AspringEditor : public Auicontainer
{
public:
	
	AspringEditor();
	void attachTo(Aspring* s);
	void detatchFrom(Aspring* s);
	
	Aspring* focus;
	Aslider* d_slide;
	Aslider* k_slide;
};


class AspringContainer : public Aobj
{
public:
	AspringContainer() {};
	void addSpring(Aspring* p){ addChild((Aobj*) p); };
	Aspring* getSpring(int index) {return (Aspring*) getChild(index);};
	int numSprings(){ return numChildren(); };
	//mimic a vector
	int size() { return numChildren(); };
	Aspring* at(int index){return (Aspring*) getChild(index);};
	
	//serialize...
	bool serializable() { return true; };
	XmlTree toXml()
	{ 
		XmlTree p( "AspringContainer", "" );
		p.push_back( getCoreXml() );
		//children
		XmlTree childrenXml("Children","");
		for(int i=0; i<Children.size(); i++)
			if( Children.at(i)->serializable() )
				childrenXml.push_back(Children.at(i)->toXml());
		p.push_back(childrenXml);
		return p;
	};
	
	void setFromXml(XmlTree* xml)
	{
		//set core
		XmlTree core = xml->getChild( "core" );
		setCoreXml(&core);
		//generate the Children:
		XmlTree kids = xml->getChild("Children");
		for( XmlTree::Iter child = kids.begin(); child != kids.end(); ++child ){
			if( child->getTag().find("Aspring") == 0)
			 {
				 console() << "making a spring" << std::endl;
				 Aspring* tmpP = new Aspring();
				 tmpP->setFromXml(&*child); //?proper way to cast?
				 addSpring(tmpP); //! Note we are not: addChild(tmpP);
			}
		}
		//add self to the registry
		XML->addToAobjRegistry(this);
	};
};

