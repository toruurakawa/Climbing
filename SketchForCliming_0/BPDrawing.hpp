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
        ofSetColor(100, 100, 255, 255);
        ofSetLineWidth(5);
        ofNoFill();
        ofBeginShape();
        for (auto it = pts.begin(); it != pts.end(); it++) {
            ofVertex(it->x, it->y);
        }
        ofEndShape();
        ofMatrix4x4 m;
        float theta = sin(ofGetElapsedTimef()) * M_PI / 64.;
        m.set(cos(theta), -sin(theta), 0, 0,
              sin(theta), cos(theta), 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1);
        ofVec3f sum;
        int size = 0;
        for (int i = 0; i < ptss.size(); i++) {
            for (auto it = ptss[i].begin(); it != ptss[i].end(); it++) {
                ofVec3f p = ofVec3f(it->x, it->y, 0);
                sum += p;
                size++;
            }
        }
        sum = sum / ofVec3f(size);
        for (int i = 0; i < ptss.size(); i++) {
            ofBeginShape();
            for (auto it = ptss[i].begin(); it != ptss[i].end(); it++) {
                ofVec3f p = ofVec3f(it->x, it->y, 0);
                ofVec3f a =  sum;
                p = m * (p - a) + a;
                ofVertex(p.x, p.y);
            }
            ofEndShape();
        }
        ofPopStyle();
    }

    vector< vector<ofVec2f> >* getPoints() {
        return &ptss;
    }
    
};