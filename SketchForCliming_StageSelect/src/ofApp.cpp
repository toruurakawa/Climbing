#include "ofApp.h"
#include "BPStarShader.hpp"

BPStar starA, starB;
BPNode node;
ofImage BPStar::starImg;
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
//    ofSetWindowPosition(2000, 0);
    ofSetFullscreen(true);
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    // stars, sky, constellations
    s.setup();
    sky.getStars();
    nextIndex = currentIndex = 0;
    cs.load();
    s.stars = (*cs.getConstellations())[currentIndex].getStars();
    
    // Quad warp
    int w = ofGetWidth();
    int h = ofGetHeight();
    int x = 0;
    int y = 0;
    warper.setSourceRect(ofRectangle(0, 0, w, h));              // this is the source rectangle which is the size of the image and located at ( 0, 0 )
    warper.setTopLeftCornerPosition(ofPoint(x, y));             // this is position of the quad warp corners, centering the image on the screen.
    warper.setTopRightCornerPosition(ofPoint(x + w, y));        // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));      // this is position of the quad warp corners, centering the image on the screen.
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h)); // this is position of the quad warp corners, centering the image on the screen.
    warper.setup();

    // App specific
    shootingTime = ofGetElapsedTimef();
    isShot = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    sky.update();

    (*cs.getConstellations())[currentIndex].update();
    s.update();

    if (isShot && ofGetElapsedTimef() - shootingTime > 1.) {
        currentIndex = nextIndex;
        isShot = false;
        if (nextIndex < 0) {
            
        }
        cs.reloadAtIndex(currentIndex);
        s.setup();
        s.stars = (*cs.getConstellations())[currentIndex].getStars();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0);
    
    // Sky
    sky.draw();
    
    // Stars
    s.draw();
    
    // Constellations
    (*cs.getConstellations())[currentIndex].draw();
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofCircle(mouseX, mouseY, 20);
    if (showEdges) {
        ofSetLineWidth(10);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
    }
    ofPopStyle();
    
    
    fbo.end();
    
//    fbo.draw(0, 0);
    
    //======================== get our quad warp matrix.
    
    ofMatrix4x4 mat = warper.getMatrix();
    
    //======================== use the matrix to transform our fbo.
    
    glPushMatrix();
    glMultMatrixf(mat.getPtr());
    fbo.draw(0, 0);
    glPopMatrix();

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
//            nextIndex = (currentIndex + 1) % cs.size();r
            nextIndex = (currentIndex - 1);
            if (nextIndex < 0) {
                nextIndex = cs.size() - 1;
            }
            if ((*cs.getConstellations()).size()) {
                (*cs.getConstellations())[currentIndex].isShooting = true;
                for (auto it = (*cs.getConstellations())[currentIndex].getStars()->begin();
                     it != (*cs.getConstellations())[currentIndex].getStars()->end(); it++) {
                    it->shoot();
//                    for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
//                        if (it->getId() == it2->getId()) {
//                            it2->shoot();
//                        }
//                    }

                }
                isShot = true;
                shootingTime = ofGetElapsedTimef();
            }
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

//--------------------------------------------------------------
void ofApp::nextConstellation() {
    
}

//--------------------------------------------------------------
void ofApp::prevConstellation() {
    
}
