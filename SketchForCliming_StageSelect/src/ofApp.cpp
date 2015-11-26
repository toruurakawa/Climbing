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
    cs.load();
    s.stars = (*cs.getConstellations())[1].getStars();
    
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
    mode = Edge;
    shootingTime = ofGetElapsedTimef();
    isShot = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    sky.update();

    (*cs.getConstellations())[counter % 2].update();
    tempConstellation.update();
    s.update();

    if (isShot && ofGetElapsedTimef() - shootingTime > 1.) {
        counter++;
        isShot = false;
        cs.reloadAtIndex(counter % 2);
        s.setup();
        s.stars = (*cs.getConstellations())[counter % 2].getStars();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0);
    
    // Sky
    sky.draw();
    
//    // Nodes
//    ofSetColor(255);
//    for (auto it = nodes.begin(); it != nodes.end(); it++) {
//        it->draw();
//    }
    
    // Stars
    s.draw();
    
    // Drawings
    drawing.draw();
    
    // Constellations
    (*cs.getConstellations())[counter % 2].draw();
//    tempConstellation.draw();
    
    // Others
    string str; 
    switch (mode) {
        case Constellation:
            str = "mode: Drawing";
            break;
        case Edge:
            str = "mode: Edge";
            break;
        case Star:
            str = "mode: Star";
            break;
        default:
            break;
    }
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofVec2f(10, 10));
    ofDrawBitmapString(str, ofVec2f(10, 30));
    
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
            tempConstellation.setDrawing(drawing);
            constellations.push_back(tempConstellation);
            drawing.clear();
            nodes.clear();
            selectedStars.clear();
            break;
        case 's':
//            tempConstellation.setDrawing(drawing);
            sky.saveToXML();
            tempConstellation.saveToXml();
            break;
        case 'r':
            tempConstellation.clear();
            constellations.clear();
            break;
        case 'x':
            if ((*cs.getConstellations()).size()) {
                (*cs.getConstellations())[counter % 2].isShooting = true;
                for (auto it = (*cs.getConstellations())[counter % 2].getStars()->begin();
                     it != (*cs.getConstellations())[counter % 2].getStars()->end(); it++) {
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
    if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
        
        drawing.addPoint(ofVec2f(x, y));
    }
    else if (mode == TopLeft) {
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
    if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
        
        drawing.addPoint(ofVec2f(x, y));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (mode == Edge) {
        ofVec2f p = ofVec2f(x, y);
        int max = 15;
        BPStar* selected;
        for (auto it = sky.getStars()->begin(); it != sky.getStars()->end(); it++) {
            float dist = (p - it->getPosition()).length();
            if (dist < max) {
                max = dist;
                selected = sky.getStar(it - sky.getStars()->begin());
            }
        }
        if (max < 10) {
            selectedStars.push_back(*selected);
            tempConstellation.addStar(*selected);
            if (selectedStars.size() == 2) {
                BPNode n;
                n.setStartingStar(selectedStars[0]);
                n.setEndStar(selectedStars[1]);
                nodes.push_back(n);
                tempConstellation.addNode(n);
                selectedStars.clear();
            }
        }
    }
    else if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
        ptss.push_back(pts);
        pts.clear();
        
        drawing.endPoint(ofVec2f(x, y));
    }
    else if (mode == Star) {
        ofVec2f v(x,y);
        float mag = ofRandom(5);
        sky.addStar(v, mag);
    }
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
