/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Acollider.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "physicscore.h"

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// Acollider
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


Acollider::Acollider()
{	
	//global forces
	collisionForceStrength = 0.25f;
	Ke = -0.1f;
	
	//editing hooks
	mEditor = NULL;
	
	//default size
	w = 800;
	h = 600;
	useRectBoundaries = true;
	
	particles = new AparticleContainer();
	springs = new AspringContainer();
	
	addChild(particles);
	addChild(springs);
	bringParticlesForward();
}

//////////////////////////////////////////////////////////////////////////
// Members Functions !g!
//////////////////////////////////////////////////////////////////////////

void Acollider::makeCloud()
{
	for(int i=0; i<10; i++)
		addParticle(Vec3f(Rand::randFloat( w ),Rand::randFloat( h ), 0.0f ));
	
	Aparticle* p1 = particles->at(0);
	Aparticle* p2 = particles->at(1);
	
	Aspring* tmpS = new Aspring(p1, p2);
	addSpring(tmpS);
}

void Acollider::addParticle(Vec3f pos)
{
	Aparticle* tmpP = new Aparticle();
	tmpP->position.set(pos.x,pos.y,0);
	addParticle(tmpP);
}

void Acollider::addParticle(Aparticle* p)
{
	p->COLLIDER = this;
	particles->addParticle(p);	
}

void Acollider::deleteParticle(Aparticle* p)
{
	//remove relevant springs:
	Aspring* tmpS = p->popSpring();
	while( tmpS != NULL){
		deleteSpring(tmpS);
		tmpS = p->popSpring();
	}
	particles->removeChild(p);	
}

void Acollider::addSpring(Aspring* s)
{
	s->COLLIDER = this;
	springs->addChild(s);
}

void Acollider::deleteSpring(Aspring* S)
{
	if(S == NULL) return;
	
	//tell particles to get rid of it
	S->P1->removeSpring(S);
	S->P2->removeSpring(S);
	springs->removeChild(S);	
}

void Acollider::bringParticlesForward()
{
	bringChildToFront(particles);
}

//////////////////////////////////////////////////////////////////////////
// Toggle Functions !g!
////////////////////////////////////////////////////////////////////////

void Acollider::bringSpringsForward()
{
	bringChildToFront(springs);
}

//////////////////////////////////////////////////////////////////////////
// Render Functions !g!
//////////////////////////////////////////////////////////////////////////

void Acollider::render()
{
	applyColor(Acolor(1,1,1,0.2f));
	Rectf rect( 0, 0, w, h );
	gl::drawSolidRect( rect );
}

//////////////////////////////////////////////////////////////////////////
// Update Functions !g!
//////////////////////////////////////////////////////////////////////////

void Acollider::update()
{
	runAttraction();
	runCollisions();
	runBoundary();
}

void Acollider::runBoundary()//? lamely implemented
{
	//Avec f = new Avec();
	//float mag = 10f;
	for(int i=0; i<particles->size(); i++)
	{
		Aparticle* tmpP = particles->at(i);
		//Check horizontal boundary:
		if( tmpP->position.x-tmpP->r < 0){
			tmpP->position.x = tmpP->r;
		}
		else if( tmpP->position.x+tmpP->r > w){
			tmpP->position.x = w-tmpP->r;
		}
		//Check vertical boundary:
		if( tmpP->position.y-tmpP->r < 0){
			tmpP->position.y = tmpP->r;
		}
		else if( tmpP->position.y+tmpP->r > h){
			tmpP->position.y = h-tmpP->r;
		}
	}
}

void Acollider::runCollisions()
{
	int resolvedCount = 0; //used to help measure how efficient sorting is
	for(int i=0; i<particles->size(); i++){
		Aparticle* p1 = particles->at(i);
		for(int j=i+1; j < particles->size(); j++){
			Aparticle* p2 = particles->at(j);
			if(doCollision(p1, p2))
				resolvedCount ++;
		}
	}
}

bool Acollider::doCollision(Aparticle* p1, Aparticle* p2)
{
	//Simple bounds checking to avoid too much calculation
	if(abs(p1->position.x - p2->position.x) > (p1->r+p2->r))
		return false;
	if(abs(p1->position.y - p2->position.y) > (p1->r+p2->r))
		return false;
		
	Vec3f dir = p1->position - p2->position;
	float overlap = (p1->r + p2->r) - dir.length(); //? use squared measure somehow...	
	if(overlap > 0){
		dir.normalize();
		dir *= collisionForceStrength * overlap;			
		p1->addForce( dir );
		p2->addForce( -dir );
	}
	return true;
}


void Acollider::runAttraction()
{
	for(int i=0; i<particles->size(); i++)
		for(int j=i+1; j<particles->size(); j++)
				PureCoulombAttraction(particles->at(i), particles->at(j));
}


bool Acollider::PureCoulombAttraction(Aparticle* p1, Aparticle* p2)
{
	//calculate force
	Vec3f vec = p1->position - p2->position;
	float dist = vec.length();
	vec.normalize();
	vec *= ( Ke / (dist*dist) * p1->r*p2->r); // also Ke*P1->q*P2->q
	
	//add force
	p1->addForce( vec );
	p2->addForce( -vec );
	return true;
}

//////////////////////////////////////////////////////////////////////////
// Event Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Acollider::handleEvent(Aevent* evt)
{	
	if(evt->Type == MOUSE_PRESS_EVENT)
	{		
		Vec3f localPoint = globalToLocal(evt->mousePos);		
		if( pointInside( localPoint )){
			if(mEditor != NULL){
				mEditor->backgroundClicked(localPoint);
			}
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// Xml Functions !g!
//////////////////////////////////////////////////////////////////////////

XmlTree Acollider::toXml()
{ 
	XmlTree xml( "Acollider", "" );
	xml.push_back( getCoreXml() );
	xml.push_back( XmlTree( "collisionForceStrength", toString(collisionForceStrength) ) );
	xml.push_back( XmlTree( "Ke", toString(Ke) ) );
	
	//Serialize Children:
	XmlTree childrenXml("Children","");
	for(int i=0; i<Children.size(); i++)
		if( Children.at(i)->serializable() )
			childrenXml.push_back(Children.at(i)->toXml());
	xml.push_back(childrenXml);

	//Serialize References
	if(particles != NULL) xml.push_back( XmlTree( "particles", particles->Ref ) );
	if(springs != NULL) xml.push_back( XmlTree( "springs", springs->Ref ) );
	
	return xml;
}

void Acollider::setFromXML(XmlTree* xml)
{
	//remove children...
	removeChild(particles);
	removeChild(springs);
	
	//set core
	XmlTree core = xml->getChild( "core" );
	setCoreXml(&core);
	//set the specific attributes:
	XML->setFromXmlTreeChild(&(collisionForceStrength), "collisionForceStrength", xml);
	XML->setFromXmlTreeChild(&(Ke), "Ke", xml);
	
	//generate the Children:
	XmlTree kids = xml->getChild("Children");
	for( XmlTree::Iter child = kids.begin(); child != kids.end(); ++child ){
		if( child->getTag().find("AparticleContainer") == 0)
		{
			AparticleContainer* tmpP = new AparticleContainer();
			tmpP->setFromXml(&*child); //? proper way to cast?
			addChild(tmpP); //! Note we are not: addChild(tmpP);
		}
		else if( child->getTag().find("AspringContainer") == 0)
		{
			AspringContainer* tmpP = new AspringContainer();
			tmpP->setFromXml(&*child); //?proper way to cast?
			addChild(tmpP); //! Note we are not: addChild(tmpP);
		}
	}
	//add self to the registry
	XML->addToAobjRegistry(this);
	
	xmlSave = *xml;
}


void Acollider::linkFromXml()
{	
	std::string link;
	XML->setFromXmlTreeChild(&link, "particles", &xmlSave);
	particles = (AparticleContainer*) findInXmlRegistry(link);
	
	XML->setFromXmlTreeChild(&link, "springs", &xmlSave);
	springs = (AspringContainer*) findInXmlRegistry(link);	
}

bool Acollider::setFromXmlFile( std::string sub_path) //? also make setFromXmlString and setFromXmlURL...
{
	XML->clearAobjRegistry();
	XmlTree Ac;
	try{
		XmlTree doc( loadFile( sub_path ) );
		Ac = doc.getChild( "Acollider" );
	} catch( ... ) {
		console() << "Acollider::setFromXmlFile unable to load: " << sub_path << std::endl;
		return false;
	}	
	setFromXML(&Ac);
	linkFromXmlTree();
	XML->clearAobjRegistry();
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// AcolliderEditor
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

AcolliderEditor::AcolliderEditor() : Auicontainer("Acollider Editor")
{	
	//Preset Pointers
	COLLIDER = NULL;
	caughtParticle = NULL;
	caughtSpring = NULL;
	
	particleEditor = NULL;
	springEditor = NULL;
	
	//Make Attribute Editors
	alphaSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	alphaSlider->interval = 0.01f;
	alphaSlider->makeTitle("alpha");
	addUiElement(alphaSlider);
	
	collideSlider = new Aslider(0.0f, 0.0f, 0.0f, 1.0f);
	collideSlider->interval = 0.01f;
	collideSlider->makeTitle("collide force");
	addUiElement(collideSlider);
	
	KeSlider = new Aslider(0.0f, 0.0f, -1.0f, 1.0f);
	KeSlider->interval = 0.01f;
	KeSlider->makeTitle("Ke");
	addUiElement(KeSlider);
	
	visibleButton = new AbuttonBool(false);
	visibleButton->makeTitle("visible");
	addUiElement(visibleButton);
	
	//Make Edit Option
	options = new AuiIntRadioButtons("edit state");
	options->addIntButton("interact", INTERACT);
	options->addIntButton("add particle", ADD_P);
	options->addIntButton("delete particle", DELETE_P);
	options->addIntButton("link", LINK);
	options->addIntButton("unlink", UNLINK);
	options->addIntButton("edit particle", EDIT_P);
	options->addIntButton("edit spring", EDIT_S);
	addUiElement(options);
	options->AobjTarget = this;
	
	editState = INTERACT;
	options->setActiveIntButtonByVal(editState);
	
	//Make File Saving
	FileNameOut = new Atextentrybox();
	FileNameOut->makeTitle("Enter file name to write out");
	addUiElement(FileNameOut);
	
	SaveFileButton = new Amsgbutton();
	SaveFileButton->message = "SaveFile";
	SaveFileButton->makeTitle("Save To File");
	SaveFileButton->targetAobj = this;
	addUiElement(SaveFileButton);
	
	//Make File Loading
	FilePathIn = new Afileexplorer();
	FilePathIn->makeTitle("Click Button to search for files");
	addUiElement(FilePathIn);
	
	LoadFileButton = new Amsgbutton();
	LoadFileButton->makeTitle("Load From File");
	LoadFileButton->message = "LoadFile";
	LoadFileButton->targetAobj = this;
	addUiElement(LoadFileButton);
	
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Collider registration
////////////////////////////////////////////////////////////////////////////////////////////////

void AcolliderEditor::attachToCollider(Acollider* c)
{
	if(c == NULL) return;
	
	COLLIDER = c;
	alphaSlider->attachToFLOAT( &(COLLIDER->alpha) );
	collideSlider->attachToFLOAT( &(COLLIDER->collisionForceStrength) );
	KeSlider->attachToFLOAT( &(COLLIDER->Ke) );
	visibleButton->attachToBOOL(&(COLLIDER->visible));
	options->attachToInt(&(editState));
}

void AcolliderEditor::detachFromCollider()
{
	COLLIDER = NULL;
	alphaSlider->targetFLOAT = NULL;
	collideSlider->targetFLOAT =  NULL;
	KeSlider->targetFLOAT = NULL;
	visibleButton->targetValue = NULL;
	//? update options as well?
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Aparticle Handling
////////////////////////////////////////////////////////////////////////////////////////////////

void AcolliderEditor::registerParticle(Aparticle* p)
{
	if(editState == EDIT_P || editState == ADD_P){
		if(caughtParticle != NULL) particleEditor->detatchFrom(caughtParticle);
		caughtParticle = p;
		particleEditor->attachTo(p);
	}
	else if(editState == DELETE_P){
		COLLIDER->deleteParticle(p);
		particleEditor->detatchFrom(p);
		caughtParticle = NULL;
	}
	else if(editState == LINK){
		if(caughtParticle == NULL){
			caughtParticle = p;
			caughtParticle->registered = true;
		}else {
			if(p != caughtParticle){
				//Make spring and add to COLLIDER
				Aspring* tmpS = new Aspring(caughtParticle, p );
				COLLIDER->addSpring(tmpS);
				caughtParticle->registered = false;
				caughtParticle = NULL;
			}
		}
	}
}

void AcolliderEditor::deregisterParticle(Aparticle* p)
{
	//? Not used for anything yet
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Aspring Handling
////////////////////////////////////////////////////////////////////////////////////////////////

void AcolliderEditor::registerSpring(Aspring* s)
{
	if(editState == EDIT_S){
		if(caughtSpring != NULL) springEditor->detatchFrom(caughtSpring);
		caughtSpring = s;
		springEditor->attachTo(s);
	}
	if(editState == UNLINK){
		COLLIDER->deleteSpring(s);
		springEditor->detatchFrom(s);
		caughtSpring = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Event Handling
////////////////////////////////////////////////////////////////////////////////////////////////

void AcolliderEditor::backgroundClicked(Vec3f pnt)
{
	if( editState == ADD_P)
		COLLIDER->addParticle(pnt);
}

void AcolliderEditor::resetEditState()
{
	if(caughtParticle != NULL) particleEditor->detatchFrom(caughtParticle);
	if(caughtSpring != NULL) springEditor->detatchFrom(caughtSpring);
	caughtParticle = NULL;
	caughtSpring = NULL;
	//toggle containers as needed:
	if( ( editState == UNLINK || editState == EDIT_S ) && COLLIDER != NULL )
		COLLIDER->bringSpringsForward();
	else if ( COLLIDER != NULL )   
		COLLIDER->bringParticlesForward();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Message Handling
////////////////////////////////////////////////////////////////////////////////////////////////

void AcolliderEditor::processMessage(Amessage* msg)
{	
	if(msg->message.compare("IntRadioButtonChange") == 0){
		resetEditState();
	}
	else if(msg->message.compare("SaveFile") == 0){
		COLLIDER->saveToXmlFile(FileNameOut->Text);
	}
	else if(msg->message.compare("LoadFile") == 0){
		COLLIDER->setFromXmlFile(FilePathIn->FilePath->Text);
	}
};