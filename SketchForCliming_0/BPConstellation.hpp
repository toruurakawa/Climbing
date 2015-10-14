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
    ofXml xml;
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
    
    void saveToXml(){
        xml.addChild("CONSTELLATION");
        xml.setTo("CONSTELLATION");
        // Stars
        xml.addChild("STARS");
        xml.setTo("STARS");
        for (auto it = stars.begin(); it != stars.end(); it++) {
            ofVec2f p = it->getPosition();
            int m = it->getMagnitude();
            
            ofXml star;
            star.addChild("STAR");
            star.setTo("STAR");
            star.addChild("POSITION");
            star.setTo("POSITION");
            star.addValue("X", p.x);
            star.addValue("Y", p.y);
            star.setTo("../");
            star.addValue("MAGNITUDE", m);
            
            xml.addXml(star);
        }
        // Nodes
        xml.setTo("../");
        xml.addChild("NODES");
        xml.setTo("NODES");
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            ofVec2f p_s = it->getStartingStar().getPosition();
            ofVec2f p_e = it->getEndStar().getPosition();

            ofXml node;
            node.addChild("NODE");
            node.setTo("NODE");
            node.addChild("STARTING");
            node.setTo("STARTING");
            node.addValue("X", p_s.x);
            node.addValue("Y", p_s.y);
            node.setTo("../");
            node.addChild("ENDING");
            node.setTo("ENDING");
            node.addValue("X", p_e.x);
            node.addValue("Y", p_e.y);
            xml.addXml(node);
        }
        xml.save("Constellation.xml");
    }
};