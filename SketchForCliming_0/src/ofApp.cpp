#include "ofApp.h"
#include "BPStarShader.hpp"

BPStar starA, starB;
BPNode node;
ofImage BPStar::starImg;
ofFbo fbo;
BPStarShader s;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    BPStar::starImg.loadImage("particle32.png");
    ofSetWindowPosition(2000, 0);
    ofSetFullscreen(true);
    sky.setupFromXml("mySettings.xml");
    
    BPConstellation c;
    c.loadFromXml();
    constellations.push_back(c);
    for (auto it = c.getStars()->begin(); it != c.getStars()->end(); it++) {
        for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
            if (it->getId() == it2->getId()) {
                it2->isConstellation = true;
            }
        }
    }
    
    mode = Edge;
    fbo.allocate(ofGetWidth(), ofGetHeight());
    
    s.setup();
    s.stars = sky.getStars();
}

//--------------------------------------------------------------
void ofApp::update(){
    sky.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofBackground(0);
    
    // Sky
    sky.draw();
    
    // Nodes
    ofSetColor(255);
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        it->draw();
    }
    
    s.draw();
    
    // Drawings
    drawing.draw();
    
    // Constellations
    for (auto it = constellations.begin(); it != constellations.end(); it++) {
        it->draw();
    }
    tempConstellation.draw();
    
    // Others
    string str; 
    switch (mode) {
        case Constellation:
            str = "mode: Drawing";
            break;
        case Edge:
            str = "mode: Edge";
            break;
        default:
            break;
    }
    
    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofVec2f(10, 10));
    
    fbo.end();
    
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case'1':
            s.isDrawingMesh = !s.isDrawingMesh;
            break;
        case '2':
            s.isDrawingShader = !s.isDrawingShader;
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
            tempConstellation.setDrawing(drawing);
            sky.saveToXML();
            tempConstellation.saveToXml();
            break;
        case 'r':
            tempConstellation.clear();
            break;
        case 'x':
            for (auto it = constellations[0].getStars()->begin();
                 it != constellations[0].getStars()->end(); it++) {
                for (auto it2 = sky.getStars()->begin(); it2 != sky.getStars()->end(); it2++) {
                    if (it->getId() == it2->getId()) {
                        it2->shoot();
                    }
                }
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
    if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
        
        drawing.addPoint(ofVec2f(x, y));
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
