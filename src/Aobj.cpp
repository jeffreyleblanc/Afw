/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aobj.cpp
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//Usefull precedents:
// vView by Young Sang Cho
// http://forum.libcinder.org/topic/simple-scene-graph-system

#include "Aobj.h"

using namespace ci;
using namespace ci::app;
using namespace std;

CameraPersp* Aobj::myCam = NULL;
int Aobj::instanceCount = 0;

Aobj::Aobj()
{
	//Initialize meta information
	parent = NULL;
	visible = true;
	debugRenderOn = false;
	
	alpha = 1.0;
	alphaTree = 1;
	
	h = w = 10;
	draggable = false;
	grabbed = false;
	useRectBoundaries = false;
	
	//Initialize geometry
	position.set( 0, 0, 0 );
	scale.set( 1,1,1 );
	rotation = Quatf::identity();
	rotationRadians = 0;
	anchor.set(0,0,0);
	transformMatrix.setToIdentity();
	worldTransformMatrix.setToIdentity();
	
	XML = Axml::getInstance();
	CMN = Autil::getInstance();
		
	setRef();
}


Aobj::~Aobj()
{	
	for( int i=0; i< Children.size(); i++ ){
		delete Children[i];
	}
	Children.clear();
	
	//? delete any other variables?
}

void Aobj::setRef()
{
	Ref = toString(Aobj::instanceCount)+"#"+timeBase62();
	Aobj::instanceCount++;
}

//////////////////////////////////////////////////////////////////////////
// Render Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aobj::render() {}

void Aobj::debugRender()
{
	gl::color(Color(1,0,0));
	Rectf rect( -2, -2, 2, 2 );
	gl::drawSolidRect( rect );
}

void Aobj::renderTree(const Matrix44f &world)
{
	if( !visible )
		return;
	
	//Handle transforms
	transform();	
	worldTransformMatrix = world * transformMatrix;
	gl::pushModelView();
	gl::multModelView( transformMatrix );
	
	//set alphaTree
	alphaTree = alpha;
	if( parent ) alphaTree *= parent->alphaTree;
	
	render();
	
	for( int i=0; i< Children.size(); i++ ){
		Children[i]->renderTree(worldTransformMatrix);
	}
	
	if(debugRenderOn){
		gl::translate( anchor );
		debugRender(); }
	
	gl::popModelView();
}

void Aobj::applyColor(Acolor C)
{
	gl::color(ColorA(C.r, C.g, C.b, C.a*alphaTree));
}

//////////////////////////////////////////////////////////////////////////
// Geometry Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aobj::setRotation( float radians )
{ 
	rotation.set( Vec3f::zAxis(), radians );
	rotationRadians = radians;
};

float Aobj::getRotation()
{
	return rotationRadians;
}

Vec3f Aobj::globalToLocal( Vec3f pt)
{
	Vec3f p(pt.x, pt.y, pt.z);
	
	// adjust y (0,0 is lowerleft corner in OpenGL)
	Area viewport = gl::getViewport();
	p.y = (viewport.getHeight() - p.y);
	
	// near plane intersection
	p.z = 0.0f;
	Vec3f p0 = unproject(p);
	// far plane intersection
	p.z = 1.0f;
	Vec3f p1 = unproject(p);
	
	// find (x, y) coordinates
	float t = (0.0f - p0.z) / (p1.z - p0.z);
	p.x = (p0.x + t * (p1.x - p0.x));
	p.y = (p0.y + t * (p1.y - p0.y));
	p.z = 0.0f;
	
	return Vec3f(p.x, p.y, p.z);
}

Vec3f Aobj::localToGlobal( const Vec3f &pt )
{
	Matrix44f	projection = gl::getProjection();
	Area		viewport = gl::getViewport();
	
	Matrix44f a = projection * worldTransformMatrix;
	
	Vec4f in;
	in.x = pt.x;
	in.y = pt.y;
	in.z = pt.z;//0.0f;
	in.w = 1.0f;
	
	Vec4f out = a * in;
	if(out.w != 0.0f) out.w = 1.0f / out.w;
	out.x *= out.w;
	out.y *= out.w;
	out.z *= out.w;
	
	Vec3f result;
	result.x = viewport.getX1() + viewport.getWidth() * (out.x + 1.0f) / 2.0f;
	result.y = viewport.getY1() + viewport.getHeight() * (1.0f - (out.y + 1.0f) / 2.0f);
	result.z = 0;//(out.z + 1.0f) / 2.0f;
	
	return result;
}

void Aobj::transform()
{
	transformMatrix.setToIdentity();
	transformMatrix.translate( position );
	transformMatrix *= rotation.toMatrix44();
	transformMatrix.scale( scale );
	transformMatrix.translate( -anchor );
}

Vec3f Aobj::unproject(const Vec3f &pt)
{
	// update viewport and projection matrix
	Matrix44f projection = gl::getProjection();
	Area viewport = gl::getViewport();
	
	// since we don't have GLU, we have to do the calculation ourselves:
	// -find the inverse modelview-projection-matrix
	Matrix44f a = projection * worldTransformMatrix;
	a.invert();
	// -transform normalized coordinates [-1, 1]
	Vec4f in;
	in.x = (pt.x - viewport.getX1())/viewport.getWidth()*2.0f-1.0f;
	in.y = (pt.y - viewport.getY1())/viewport.getHeight()*2.0f-1.0f;
	in.z = 2.0f * pt.z - 1.0f;
	in.w = 1.0f;
	// -objects coordinates
	Vec4f out = a * in;
	if(out.w != 0.0f) out.w = 1.0f / out.w;
	// -calculate output
	Vec3f result;
	result.x = out.x * out.w;
	result.y = out.y * out.w;
	result.z = out.z * out.w;
	
	return result;
}

//////////////////////////////////////////////////////////////////////////
// Update Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aobj::update()
{}

void Aobj::updateTree()
{	
	if( !visible ){
		processMessageInbox(); //! we still process the messages
		return;
	}
	
	update();
	
	for( int i=0; i<Children.size(); i++ ){
		Children[i]->updateTree();
	}
	
	processMessageInbox();	
}

//////////////////////////////////////////////////////////////////////////
// Connection Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aobj::addChild( Aobj* child )
{
	child->parent = this;
	Children.push_back( child );	
}

int Aobj::numChildren(){
	return Children.size();
}

Aobj* Aobj::getChild(int index)
{
	if( index < 0 || index > Children.size()-1 ) return NULL;
	return Children[index];
}

void Aobj::removeChild(Aobj* child)
{
	for( int i=0; i< Children.size(); i++ ){
		if( Children[i] == child ){
			Children.erase( Children.begin()+i );
			//? delete child?
			break;
		}
	}
}

void Aobj::bringChildToFront(Aobj* child){ //? check functionality
	for( int i=0; i< Children.size(); i++ ){
		if( Children[i] == child ){
			Children.erase( Children.begin()+i );
			Children.push_back( child );
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Boundary Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Aobj::pointInside( Vec3f P)
{
	if(useRectBoundaries)
		return pointInsideRect( P );
	else
		return false;
}

bool Aobj::pointInsideRect( Vec3f P ){
	if( (float)P.x >= 0 && (float)P.x <= w)
	{
		if( (float)P.y >= 0 && (float)P.y <= h)
			return true;
		else return false;
	}
	else return false;
}

float  Aobj::getWidth()
{
	return w;
}

float  Aobj::getHeight()
{
	return h;
}

//////////////////////////////////////////////////////////////////////////
// Event Functions !g!
//////////////////////////////////////////////////////////////////////////

bool Aobj::handleEvent(Aevent* evt)
{  
	if(draggable)
		return handleDrag(evt);
	else
		return false;
}

bool Aobj::handleEventTree(Aevent* evt)
{	
	if(visible == false) return false;
	
	for(int i=Children.size()-1; i>-1; i--){
		if( Children[i]->handleEventTree(evt) == true)
		{ return true; }
	}		
	return handleEvent(evt);
}

bool Aobj::handleDrag(Aevent* evt)
{
	if(evt->Type == MOUSE_PRESS_EVENT)
	{		
		Vec3f localPoint = globalToLocal(evt->mousePos);		
		if( pointInside( localPoint )){
			grabbed = true;
			grabPoint.set(localPoint);
			if(parent)
				parentGrabPoint = position - parent->globalToLocal(evt->mousePos);
			return true;
		}
	}
	else if(evt->Type == MOUSE_DRAG_EVENT && grabbed == true)
	{
		position = parent->globalToLocal(evt->mousePos);
		if(parent)
			position += parentGrabPoint;
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
// Message Functions !g!
//////////////////////////////////////////////////////////////////////////

void Aobj::recieveMessage(Amessage* msg)
{
	messageInbox.push(msg);
}

void Aobj::processMessageInbox() //called in updateTree()
{
	while( ! messageInbox.empty() )
	{
		Amessage* tmpMsg = messageInbox.top();
		processMessage(tmpMsg);
		messageInbox.pop(); //? equivilant to: delete tmpMsg; Check if deletion is occuring
	}
}

void Aobj::processMessage(Amessage* msg) {}

//////////////////////////////////////////////////////////////////////////
// Xml Functions !g!
//////////////////////////////////////////////////////////////////////////

XmlTree Aobj::toXml() { return getCoreXml(); }

XmlTree Aobj::getCoreXml()
{
	XmlTree core( "core", "" );
	core.push_back( XmlTree( "Ref", Ref ) );
	core.push_back( XML->getXmlTree(&position, "position"));
	core.push_back( XML->getXmlTree(&scale, "scale"));
	core.push_back( XML->getXmlTree(&anchor, "anchor"));
	core.push_back( XmlTree( "rotation", toString(getRotation()) ) );
	core.push_back( XmlTree( "alpha", toString(alpha) ) );
	if(parent != NULL)
		core.push_back( XmlTree( "parent", parent->Ref ) );
	return core;
}

void Aobj::setCoreXml(XmlTree* coreXml)
{
	XML->setFromXmlTreeAttribute(&position, &(coreXml->getChild("position")) );
	XML->setFromXmlTreeAttribute(&scale, &(coreXml->getChild("scale")) );
	XML->setFromXmlTreeAttribute(&anchor, &(coreXml->getChild("anchor")) );
	XML->setFromXmlTreeAttribute(&position, &(coreXml->getChild("position")) );
	float rot;
	XML->setFromXmlTreeChild(&(rot), "rotation", coreXml);
	setRotation(rot);
	XML->setFromXmlTreeChild(&(alpha), "alpha", coreXml);
	XML->setFromXmlTreeChild(&(Ref), "Ref", coreXml);
	//note we ignore parent Ref...
}

Aobj* Aobj::findInXmlRegistry(std::string ref)
{
	Aobj* returnOBJ = NULL;
	for(int i=0; i < XML->AobjRegistry.size(); i++){
		if( ref.find(XML->AobjRegistry.at(i)->Ref) == 0)
		{ returnOBJ = XML->AobjRegistry.at(i); break; }
	}
	return returnOBJ;
}

void Aobj::linkFromXmlTree(){
	linkFromXml();
	for(int i=0; i<Children.size(); i++)
		if( Children.at(i)->serializable() )
			Children.at(i)->linkFromXmlTree();
}
