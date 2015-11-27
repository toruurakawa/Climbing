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
int counter = 0;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    BPStar::starImg.loadImage("particle32.png");
//    ofSetWindowPosition(2000, 0);
    ofSetFullscreen(true);
//    sky.setupFromXml("mySettings.xml");
    sky.setup();
    
//    BPConstellation c;
//    c.loadFromXml("Constellation.xml");
//    constellations.push_back(c);
//    for (auto it = c.getStars()->begin(); it != c.getStars()->end(); it++) {
//        for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
//            if (it->getId() == it2->getId()) {
//                it2->isConstellation = true;
//            }
//        }
//    }
    
    mode = Edge;
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    s.setup();
    s.stars = sky.getStars();
    
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
    
//    (x = 0, y = 0, z = 0)
//    (x = 1404, y = 40, z = 0)
//    (x = 1429, y = 899, z = 0)
//    (x = 6, y = 899, z = 0)
    
    shootingTime = ofGetElapsedTimef();
    isShot = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    sky.update();
    s.update();
    
    for (auto it = constellations.begin(); it != constellations.end(); it++) {
        it->update();
    }
    tempConstellation.update();

    if (isShot && ofGetElapsedTimef() - shootingTime > .75) {
        counter++;
        string settingsStr, constellationStr;
        if (counter % 2 == 0) {
            settingsStr = "mySettings.xml";
            constellationStr = "Constellation.xml";
        } else {
            settingsStr = "mySettings copy.xml";
            constellationStr = "Constellation copy.xml";
        }
        
        isShot = false;
        sky.setupFromXml(settingsStr);
        BPConstellation c;
        c.loadFromXml(constellationStr);
        constellations.clear();
        constellations.push_back(c);
        for (auto it = c.getStars()->begin(); it != c.getStars()->end(); it++) {
            for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
                if (it->getId() == it2->getId()) {
                    it2->isConstellation = true;
                }
            }
        }
        s.setup();
        s.stars = sky.getStars();

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
    for (auto it = constellations.begin(); it != constellations.end(); it++) {
        it->draw();
    }
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
