//
//  SecondScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "SecondScene.h"
#include "FirstScene.h"

void SecondScene::setup(ofPtr<ofxScene> previousScene) {
    FirstScene* scene = dynamic_cast<FirstScene *>(previousScene.get());
    
    cs.setup();
    font.loadFont("fonts/AxisCondStd-Medium.otf", FONT_CONSTNAME);
}

void SecondScene::update() {
    cs.update();
}

void SecondScene::draw() {
    ofBackground(0);
    
//    // Arrow
//    ofSetColor(255);
//    
//    //  Left
//    ofLine(ofGetWidth() / 15., ofGetHeight() / 2.,
//           ofGetWidth() * 1.25 / 15., ofGetHeight() / 2. - ofGetHeight() / 10.);
//    ofLine(ofGetWidth() / 15., ofGetHeight() / 2.,
//           ofGetWidth() * 1.25 / 15., ofGetHeight() / 2. + ofGetHeight() / 10.);
//    //  Right
//    ofLine(ofGetWidth() * 14 / 15., ofGetHeight() / 2.,
//           ofGetWidth() * (14 - .25) / 15., ofGetHeight() / 2. - ofGetHeight() / 10.);
//    ofLine(ofGetWidth()  * 14 / 15., ofGetHeight() / 2.,
//           ofGetWidth() * (14 - .25) / 15., ofGetHeight() / 2. + ofGetHeight() / 10.);
//    
//    cs.draw();
//    
//    font.drawString(cs.currentConstellationName(), 100, 100);
    
}

void SecondScene::keyReleased(int key) {
    switch (key) {
        case 'x':
            cs.nextConstellation();
            break;
        case 'z':
            cs.prevConstellation();
            break;
            
        default:
            break;
    }
}