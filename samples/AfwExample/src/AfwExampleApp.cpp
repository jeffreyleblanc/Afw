#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Xml.h"

#include "Asystemroot.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class AfwExampleApp : public AppBasic {
public:
	void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
	float				mCameraDistance;
	
	//Note these could be static
	Asystemroot* RUN;
	Aevent* EVENT;
	Autil* CMN;
	
	std::vector<Aobj*> Cs;
};

void AfwExampleApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 768 );
	settings->setFrameRate( 60.0f );
}


void AfwExampleApp::setup()
{
	
	// SETUP CAMERA
	mCameraDistance = 350.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f::zero();
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 5000.0f );
	
	Aobj::myCam = &mCam;
	CMN = Autil::getInstance();
	
	//Enable feature we want
	gl::enableAlphaBlending();
	
	//Create the root Afw instances
	RUN = new Asystemroot();
	EVENT = new Aevent();
	
	//test something about a vector...
	Aobj* c1 = new Aobj();
	Cs.push_back(c1);
	Aobj* c2 = new Aobj();
	Cs.push_back(c2);
	Cs.clear();
	
	console() << c1->alpha << " " << c2->alpha << std::endl;
	
}

//////////////////////////////////////////////////////////////////////////
// Update and Draw Functions !g!
//////////////////////////////////////////////////////////////////////////

void AfwExampleApp::update()
{
	RUN->updateTree();
}

void AfwExampleApp::draw()
{
	gl::clear( ColorA( 0, 0, 0, 1 ) );
	RUN->renderTree( gl::getModelView() );
}

//////////////////////////////////////////////////////////////////////////
// Event Functions !g!
//////////////////////////////////////////////////////////////////////////

void AfwExampleApp::mouseDown( MouseEvent event )
{
	EVENT->Type = MOUSE_PRESS_EVENT;
	EVENT->mousePos.set((float)event.getX(), (float)event.getY(), 0.0f);
	RUN->handleEventTree(EVENT);	
}

void AfwExampleApp::mouseUp( MouseEvent event )
{
	EVENT->Type = MOUSE_UP_EVENT;
	EVENT->mousePos.set((float)event.getX(), (float)event.getY(), 0.0f);
	RUN->handleEventTree(EVENT);	
}

void AfwExampleApp::mouseDrag( MouseEvent event ){
	EVENT->Type = MOUSE_DRAG_EVENT;
	EVENT->mousePos.set((float)event.getX(), (float)event.getY(), 0.0f);
	RUN->handleEventTree(EVENT);	
}

void AfwExampleApp::keyDown( KeyEvent event ) {
    EVENT->Type = KEY_PRESS_EVENT;
	EVENT->key = event.getChar();
	EVENT->keyCode = event.getCode();
	RUN->handleEventTree(EVENT);
}


CINDER_APP_BASIC( AfwExampleApp, RendererGl )
