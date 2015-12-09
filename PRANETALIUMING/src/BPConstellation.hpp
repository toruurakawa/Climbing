//
//  BPConstellation.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/8/15.
//
//

#pragma once
#include "BPStar.hpp"
#include "BPNode.hpp"
#include "BPDrawing.hpp"

class BPConstellation {
    string filename;
    vector<BPStar> stars;
    vector<BPNode> nodes;
    float alpha;
    BPDrawing drawing;
public:
    bool isShooting;
    
    BPConstellation() {
        alpha = 255;
    }
    
    vector<BPStar>* getStars(){
        return &stars;
    }
    
    void addStar(BPStar s) {
        bool canAdd = true;
        for (auto it = stars.begin(); it != stars.end(); it++) {
            ofVec2f pos = it->getPosition();
            if (s.getPosition() == pos) {
                canAdd = false;
            }
        }
        if (canAdd) {
            stars.push_back(s);
        }
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
        for (auto it = stars.begin(); it != stars.end(); it++) {
            it->update();
        }
        drawing.alpha = alpha;
        if (isShooting) {
            alpha += (0 - alpha) / 10.;
        }
    }
    
    void draw() {
        ofPushStyle();
        // Nodes
        ofSetColor(255, alpha);
        for (auto it = nodes.begin(); it != nodes.end(); it++) {
            it->draw();
        }        
        // Drawing
        drawing.draw();
        ofPopStyle();
    }
    
    void saveToXml(){
        ofXml xml;
        xml.addChild("CONSTELLATION");
        xml.setTo("CONSTELLATION");
        // Stars
        xml.addChild("STARS");
        xml.setTo("STARS");
        for (auto it = stars.begin(); it != stars.end(); it++) {
            ofVec2f p = it->getPosition();
            int m = it->getMagnitude();
            int id = it->getId();
            
            ofXml star;
            star.addChild("STAR");
            star.setTo("STAR");
            star.addChild("POSITION");
            star.setTo("POSITION");
            star.addValue("X", p.x);
            star.addValue("Y", p.y);
            star.setTo("../");
            star.addValue("MAGNITUDE", m);
            star.addValue("ID", id);
            
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
            node.setTo("../");
            xml.addXml(node);
        }
        // Drawing
        xml.setTo("../");
        xml.addChild("DRAWING");
        xml.setTo("DRAWING");
        for (auto it = drawing.getPoints()->begin() ; it != drawing.getPoints()->end(); it++) {
            ofXml stroke;
            stroke.addChild("STROKE");
            stroke.setTo("STROKE");
            for (auto it2 = it->begin(); it2 != it->end(); it2++) {
                ofXml position;
                position.addChild("POSITION");
                position.setTo("POSITION");
                position.addValue("X", it2->x);
                position.addValue("Y", it2->y);
                stroke.addXml(position);
            }
            xml.addXml(stroke);
        }
        xml.save("Constellation.xml");
    }
    
    void loadFromXml(){
        loadFromXml("Constellation.xml");
    }
    
    void loadFromXml(string _filename){
        alpha = 255;
        isShooting = false;
        filename = _filename;
        ofXml loadXml;
        if( loadXml.load(filename) ) {
            // Stars
            stars.clear();
            loadXml.setTo("CONSTELLATION");
            loadXml.setTo("STARS");
            loadXml.setTo("STAR[0]");
            do {
                loadXml.setTo("POSITION");
                float x = loadXml.getValue<float>("X");
                float y = loadXml.getValue<float>("Y");
                loadXml.setToParent();
                int m = loadXml.getValue<int>("MAGNITUDE");
                int id = loadXml.getValue<int>("ID");
                
                BPStar s;
                s.setPosition(x, y);
                s.setMagnitude(0);
                s.setId(id);
                s.isConstellation = true;
                stars.push_back(s);
            }while( loadXml.setToSibling() ); // go to next STAR
            // Nodes
            loadXml.setTo("../../");
            loadXml.setTo("NODES");
            loadXml.setTo("NODE[0]");
            do {
                loadXml.setTo("STARTING");
                float x_s = loadXml.getValue<float>("X");
                float y_s = loadXml.getValue<float>("Y");
                loadXml.setTo("../");
                loadXml.setTo("ENDING");
                float x_e = loadXml.getValue<float>("X");
                float y_e = loadXml.getValue<float>("Y");
                loadXml.setTo("../");
                
                BPNode n;
                BPStar s_s, s_e;
                s_s.setPosition(x_s, y_s);
                n.setStartingStar(s_s);
                s_e.setPosition(x_e, y_e);
                n.setEndStar(s_e);
                nodes.push_back(n);
            }while( loadXml.setToSibling() ); // go to next NODE
            // Drawing
            loadXml.setTo("../../");
            loadXml.setTo("DRAWING");
            loadXml.setTo("STROKE[0]");
            do {
                loadXml.setTo("POSITION[0]");
                vector<ofVec2f> pts;
                do {
                    float x = loadXml.getValue<float>("X");
                    float y = loadXml.getValue<float>("Y");
                    ofVec2f p = ofVec2f(x, y);
                    pts.push_back(p);
                } while (loadXml.setToSibling() ); // go to next POSITION
                drawing.addPts(pts);
                loadXml.setTo("../");
            }while( loadXml.setToSibling() ); // go to next STROKE
        }
    }
    
    string getFilename() {
        return filename;
    }
};