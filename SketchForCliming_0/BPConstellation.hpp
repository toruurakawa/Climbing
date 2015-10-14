//
//  BPConstellation.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/8/15.
//
//

#pragma once
#include "BPStar.hpp"
#include "BPNode.cpp"
#include "BPDrawing.cpp"

class BPConstellation {
    vector<BPStar> stars;
    vector<BPNode> nodes;
    BPDrawing drawing;
    
public:
    void addStar(BPStar s) {
        stars.push_back(s);
    }
    
    void addNode(BPNode n) {
        nodes.push_back(n);
    }
    
    void setDrawing(BPDrawing d) {
        drawing = d;
    }
    
    void clear() {
        stars.clear();
        nodes.clear();
        drawing.clear();
    }
    
    void update() {
        
    }
    
    void draw() {
        // Nodes
        ofSetColor(255);
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            it->draw();
        }        
        // Drawing
        drawing.draw();
    }
};