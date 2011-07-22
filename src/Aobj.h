/*
 *  Created by Jeffrey LeBlanc on 7/13/11.
 *  2011 | Jeffrey LeBlanc LLC | http://www.jeffreyleblanc.org
 *	Afw.0 framework built on Cinder
 */

/*
 *  Aobj.h
 *  Afw0
 *
 *  Created by Jeffrey LeBlanc on 6/24/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "cinder/Camera.h"
#include <stack>
#include "Axml.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Aobj {
public:
	Aobj();
	virtual ~Aobj();
	void setRef();
	//render functions
	virtual void render();
	virtual void renderTree(const Matrix44f &world);
	virtual void debugRender();
	virtual void applyColor(Acolor C);
	//scene geometery
	virtual bool pointInside( Vec3f P );
	virtual bool pointInsideRect( Vec3f P );
	Vec3f globalToLocal( Vec3f P);
	Vec3f localToGlobal( const Vec3f &pt );
	Vec3f unproject(const Vec3f &pt);
	virtual void transform();
	void setRotation( float radians );
	float getRotation();
	//update functions
	virtual void update();
	virtual void updateTree();
	//connections
	virtual void addChild(Aobj* child);
	virtual Aobj* getChild(int index);
	virtual int numChildren();
	virtual void removeChild(Aobj* child);
	virtual void bringChildToFront(Aobj* child);
	//Self Geometry
	virtual float getWidth();
	virtual float getHeight();
	//event handlers
	virtual bool handleEvent(Aevent* evt);
	virtual bool handleEventTree(Aevent* evt);
	virtual bool handleDrag(Aevent* evt);
	//message handlers
	virtual void recieveMessage(Amessage* msg);
	virtual void processMessageInbox();
	virtual void processMessage(Amessage* msg);
	//Serialize
	virtual bool serializable() { return false; };
	virtual XmlTree toXml();
	virtual XmlTree getCoreXml();
	virtual bool toXmlFile(std::string sub_path) { return false; }
	virtual void saveToXmlFile(std::string sub_path){ toXml().write( writeFile( CMN->rootResourcePath+sub_path ) );	}; //? case of non-serializable?
	virtual std::string toXmlString() { toString(toXml()); }; //? case of non-serializable?
	//Deserialize
	virtual bool setFromXmlFile( std::string sub_path) { return false; }
	virtual bool setFromXmlString( std::string xml ) { return false; }
	virtual void setCoreXml(XmlTree* coreXml);
	Aobj* findInXmlRegistry(std::string Ref);
	virtual void linkFromXml(){};
	virtual void linkFromXmlTree();
	
	//Variables //////
	
	static CameraPersp* myCam; //? Not sure what good for yet... maybe localToGlobal etc.
	Axml* XML;
	Autil* CMN;
	static int instanceCount;
	
	//Meta information
	std::string Name;
	std::string Ref; //Unique reference, could be a long...
	
	//Scene Geometry
	Vec3f	position;
	Vec3f	scale;
	Quatf	rotation;
	float	rotationRadians; //! used as a backup reference
	Vec3f	anchor;
	
	//Geometry Records
	Matrix44f	transformMatrix;
	Matrix44f	worldTransformMatrix;
	//bool transformChildren;
		
	//Self Geometry
	float h;
	float w;
	
	//Interaction Utilities
	bool draggable;
	bool grabbed;
	bool useRectBoundaries;
	Vec3f grabPoint;
	Vec3f parentGrabPoint;
	
	//Display Attributes
	float alpha;
	float alphaTree;
	bool visible;
	bool debugRenderOn;
	
	//Aobj connections
	Aobj* parent;
	std::vector<Aobj*> Children;
	
	//Message Inbox
	std::stack<Amessage*> messageInbox;
	
	//serialize system
	XmlTree xmlSave; //! could try a pointer instead
	
};