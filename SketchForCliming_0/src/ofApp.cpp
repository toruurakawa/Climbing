#include "ofApp.h"

BPStar starA, starB;
BPNode node;

//--------------------------------------------------------------
void ofApp::setup(){
    sky.setupFromXml("mySettings.xml");
//    sky.setup();
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
    drawing.draw();
    
    // Constellations
    for (auto it = constellations.begin(); it != constellations.end(); it++) {
        it->draw();
    }
    
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
        case ' ':
            tempConstellation.setDrawing(drawing);
            constellations.push_back(tempConstellation);
            drawing.clear();
            nodes.clear();
            selectedStars.clear();
            break;
        case 's':
            sky.saveToXML();
            tempConstellation.saveToXml();
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
