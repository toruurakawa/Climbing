#include "ofApp.h"

BPStar starA, starB;
BPNode node;

//--------------------------------------------------------------
void ofApp::setup(){
    sky.setup();
    mode = Edge;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // Sky
    sky.draw();
    
    // Nodes
    ofSetColor(255);
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        it->draw();
    }
    
    // Drawings
    ofPushStyle();
    ofSetColor(100, 100, 255, 100);
    ofSetLineWidth(10);
    ofNoFill();
    ofBeginShape();
    for (auto it = pts.begin(); it != pts.end(); it++) {
        ofVertex(it->x, it->y);
    }
    ofEndShape();
    for (int i = 0; i < ptss.size(); i++) {
        ofBeginShape();
        for (auto it = ptss[i].begin(); it != ptss[i].end(); it++) {
            ofVertex(it->x, it->y);
        }
        ofEndShape();
    }
    ofPopStyle();
    
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
    ofDrawBitmapString(str, ofVec2f(10, 10));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'e':
            mode = Edge;
            break;
        case 'c':
            mode = Constellation;
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
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
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
            if (selectedStars.size() == 2) {
                BPNode n;
                n.setStartingStar(selectedStars[0]);
                n.setEndStar(selectedStars[1]);
                nodes.push_back(n);
                selectedStars.clear();
            }
        }
    }
    else if (mode == Constellation) {
        ofVec2f v(x,y);
        pts.push_back(v);
        ptss.push_back(pts);
        pts.clear();
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
