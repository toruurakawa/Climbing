//
//  TitleScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "TitleScene.h"
#include "SecondScene.h"
#include "FirstScene.h"

void TitleScene::setup(ofPtr<ofxScene> previousScene) {
    SecondScene* scene = dynamic_cast<SecondScene *>(previousScene.get());
    c.clear();
    c.loadFromXml(scene->cs.currentConstellationXML());
}

void TitleScene::update() {
}

void TitleScene::draw() {
    ofBackground(0);
    ofSetColor(255);
    ofDrawBitmapString(c.getFilename(), ofVec2f(ofGetWidth() / 2., ofGetHeight() / 2.));
}
