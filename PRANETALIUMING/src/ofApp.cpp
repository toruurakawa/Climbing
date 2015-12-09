#include "ofApp.h"
#include "BPStarShader.hpp"

ofFbo fbo;
int BPStar::size = 0;
bool showEdges = false;

#include "Scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetFullscreen(true);

    fbo.allocate(ofGetWidth(), ofGetHeight());
    int w = ofGetWidth();
    int h = ofGetHeight();
    int x = 0;
    int y = 0;
    warper.setSourceRect(ofRectangle(0, 0, w, h));
    warper.setTopLeftCornerPosition(ofPoint(x, y));
    warper.setTopRightCornerPosition(ofPoint(x + w, y));
    warper.setBottomLeftCornerPosition(ofPoint(x, y + h));
    warper.setBottomRightCornerPosition(ofPoint(x + w, y + h));
    warper.setup();
    
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
    sceneManager.addScene(ofPtr<ofxScene>(new TitleScene));
    sceneManager.addScene(ofPtr<ofxScene>(new ThirdScene));
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0.3, 1.5, 0.3);
    
    sceneManager.run();
}

//--------------------------------------------------------------
void ofApp::update(){
    sceneManager.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0);
    sceneManager.draw();
    fbo.end();
    
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
        case '1':
            mode = TopLeft;
            break;
        case '2':
            mode = TopRight;
            break;
        case '3':
            mode = BottomLeft;
            break;
        case '4':
            mode = BottomRight;
            break;
        case 'e':
            mode = Edge;
            break;
        case 'c':
            mode = Constellation;
            break;
        case ' ':
            sceneManager.changeScene();
            tempConstellation.setDrawing(drawing);
            constellations.push_back(tempConstellation);
            drawing.clear();
            nodes.clear();
            selectedStars.clear();
            break;
        case 's':
            tempConstellation.setDrawing(drawing);
            sky.saveToXML();
            tempConstellation.saveToXml();
            break;
        case 'r':
            tempConstellation.clear();
            constellations.clear();
            break;
        case 'x':
            if (constellations.size()) {
                for (auto it = constellations[0].getStars()->begin();
                     it != constellations[0].getStars()->end(); it++) {
                    for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
                        if (it->getId() == it2->getId()) {
                            it2->shoot();
                            constellations[0].isShooting = true;
                        }
                    }
                }
            }
            break;
        case 'p':
            mode = Star;
            break;
        case 'l':
            sky.setupFromXml("mySettings.xml");
            break;
        case 'q':
            showEdges = false;
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
    if (mode == TopLeft) {
        warper.setTopLeftCornerPosition(ofPoint(x, y));
    }
    else if (mode == TopRight) {
        warper.setTopRightCornerPosition(ofPoint(x, y));
    }
    else if (mode == BottomLeft) {
        warper.setBottomLeftCornerPosition(ofPoint(x, y));
    }
    else if (mode == BottomRight) {
        warper.setBottomRightCornerPosition(ofPoint(x, y));
    }
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
