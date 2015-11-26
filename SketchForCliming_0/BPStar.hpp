//
//  BPStar.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/8/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxEasingFunc.h"
//#include "BPStarShader.hpp"

class BPStar {
    ofVec2f pos;
    int magnitude;
    int id;
    
public:
    bool isConstellation;
    bool isShootingStar;
    bool isFinished;
    static ofImage starImg;
    float shootingTime;
    static int size;
    
    BPStar() {
        isConstellation = false;
        isShootingStar = false;
        isFinished = false;
        id = size++;
    }

    void setPosition(float x, float y) {
        setPosition(ofVec2f(x, y));
    }
    
    void setPosition(ofVec2f _pos) {
        pos = _pos;
    }
    
    void setId(int n) {
        id = n;
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
    
    int getId(){
        return id;
    }

    
    void draw() {
        if (isShootingStar) {
            if (ofGetElapsedTimef() - shootingTime > .5) {
                return;
            }
        }
        ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofFill();
        ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        if (isConstellation) {
            ofSetColor(255, 255, 0);
        } else {
            ofSetColor(255);
        }
        starImg.draw(0, 0, magnitude * 10, magnitude * 10);
        ofPopMatrix();
        ofPopStyle();
    }
    
    void shoot(){
        shootingTime = ofGetElapsedTimef();
        isShootingStar = true;
    }
    
    void update() {
        if (isShootingStar) {
            pos += ofVec2f(-25 * 1.5, 15 * 1.5);
            magnitude += .3;
            if (pos.x < 0 || pos.y > ofGetHeight()) {
                isFinished = true;
                isShootingStar = false;
                magnitude = 0;
            }
        }
    }
};


