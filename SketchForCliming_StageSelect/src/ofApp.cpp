#include "ofApp.h"
#include "BPStarShader.hpp"
ofFbo fbo;
BPStarShader s;
int BPStar::size = 0;
bool showEdges = false;
bool isShot;
float shootingTime;
int counter = 1;

//--------------------------------------------------------------
void ofApp::setup(){
    // Visual settings and others
    ofSetFrameRate(60);
    ofSetFullscreen(true);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    // stars, sky, constellations
    sky.getStars();
    c.setup();
    
    // Quad warp
    int w = ofGetWidth() + 180;
    int h = ofGetHeight() + 20;
    int x = -90;
    int y = -10;
    warper.setSourceRect(ofRectangle(0, 0, w, h));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warper.setTopLeftCornerPosition(ofPoint(x, y));             // this is position of the quad warp corners, centering the image on the screen.
    warper.setTopRightCornerPosition(ofPoint(x + w, y));        // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));      // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h)); // this is position of the quad warp corners, centering the image on the screen.
    warper.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    sky.update();

    c.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0);
    
    // Sky
    sky.draw();
    
    // Constellations
    c.draw();
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofCircle(mouseX, mouseY, 20);
    if (showEdges) {
        ofSetLineWidth(10);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
    
    ofCircle(200, 200, 10);
    fbo.end();
    
    ofVec3f p = ofVec3f(200, 200, 0);
    //======================== get our quad warp matrix.
    ofMatrix4x4 mat = warper.getMatrix();
    p = p * mat;
    
    //======================== use the matrix to transform our fbo.
    glPushMatrix();
    glMultMatrixf(mat.getPtr());
    fbo.draw(0, 0);
    glPopMatrix();
    
    ofNoFill();
    ofCircle(p.x, p.y, 20);
    ofFill();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'q':
            showEdges = true;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'x':
            c.prevConstellation();
            break;
            
        case 'c':
            c.nextConstellation();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
