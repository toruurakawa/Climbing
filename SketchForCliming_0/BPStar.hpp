//
//  BPStar.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/8/15.
//
//

#pragma once

#include "ofMain.h"

class BPStar {
    ofVec2f pos;
    int magnitude;
    
public:
    void setPosition(float x, float y) {
        setPosition(ofVec2f(x, y));
    }
    
    void setPosition(ofVec2f _pos) {
        pos = _pos;
    }
    
    ofVec2f getPosition() {
        return pos;
    }
    
    void setMagnitude(int _magnitude){
        magnitude = _magnitude;
    }
    
    int getMagnitude(){
        return magnitude;
    }
    
    void draw() {
        ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofFill();
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofCircle(0, 0, magnitude);
        ofPopMatrix();
        ofPopStyle();
    }
};