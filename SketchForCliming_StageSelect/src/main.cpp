#include "ofMain.h"
#include "ofApp.h"

#ifdef USE_PROGRAMMABLE_GL
#include "ofGLProgrammableRenderer.h"
#endif

//========================================================================
int main( ){
    // say that we're going to *use* the fancy new renderer
//    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
