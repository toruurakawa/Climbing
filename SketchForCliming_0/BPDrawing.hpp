//
//  BPDrawing.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/14/15.
//
//

#pragma once

#include "ofMain.h"

class BPDrawing {
    vector< vector<ofVec2f> > ptss;
    vector<ofVec2f> pts;
public:
    void clear() {
        ptss.clear();
        pts.clear();
    }
    
    void addPoint(ofVec2f p) {
        ofVec2f v(p.x, p.y);
        pts.push_back(v);
    }
    
    void endPoint(ofVec2f p) {
        pts.push_back(p);
        ptss.push_back(pts);
        pts.clear();
    }
    
    void addPts(vector<ofVec2f> _pts) {
        ptss.push_back(_pts);
    }
    
    void draw() {
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
    }

    vector< vector<ofVec2f> >* getPoints() {
        return &ptss;
    }
    
};