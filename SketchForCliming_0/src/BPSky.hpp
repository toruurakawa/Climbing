//
//  BPSky.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/14/15.
//
//

#pragma once 
#include "BPStar.hpp"

class BPSky {
    ofVec2f size;
    vector<BPStar> stars;
    ofXml xml;
    
public:
    void setupFromXml(string filename) {
        size = ofVec2f(ofGetWidth(), ofGetHeight());
        if (xml.load(filename)) {
            xml.setTo("STAR[0]");
            do {
                xml.setTo("POSITION");
                int x = xml.getValue<float>("X");
                int y = xml.getValue<float>("Y");
                xml.setToParent();
                int m = xml.getValue<int>("MAGNITUDE");
                
                BPStar s;
                s.setPosition(x, y);
                s.setMagnitude(m);
                stars.push_back(s);
            }while( xml.setToSibling() ); // go to next STAR
        } else {
            
        }
    }
    
    void setup() {
        size = ofVec2f(ofGetWidth(), ofGetHeight());
        for (int i = 0; i < 400; i++) {
            ofVec2f p = ofVec2f(ofRandom(size.x), ofRandom(size.y));
            BPStar s;
            s.setPosition(p);
            s.setMagnitude(ofRandom(5));
            stars.push_back(s);
        }
    }
    
    void update();
    
    void draw() {
        ofPushStyle();
        ofFill();
        ofSetColor(0);
        ofRect(0, 0, size.x, size.y);
        ofSetColor(255);
        for (auto it =stars.begin(); it != stars.end(); it++) {
            it->draw();
        }
        ofPopStyle();
    }
    
    vector<BPStar>* getStars(){
        return &stars;
    }
    
    BPStar* getStar(int i){
        return &stars[i];
    }
    
    void saveToXML() {
        xml.clear();
        xml.addChild("SKY");
        xml.setTo("SKY");
        
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
        xml.save("mySettings.xml");
    }
};
