//
//  FirstScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "FirstScene.h"

void FirstScene::setup() {
    logoImg.loadImage("Images/logo.png");
}

void FirstScene::update() {
    
}

void FirstScene::draw() {
    ofBackground(0);
    ofSetColor(255);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    float w = ofGetWidth() * 0.8;
    float coef = w / logoImg.getWidth();
    logoImg.draw(ofGetWidth() / 2., ofGetHeight() / 2., w, logoImg.getHeight() * coef);
    ofPopStyle();
}

void FirstScene::willFadeIn() {

}

void FirstScene::willDraw() {

}

void FirstScene::willFadeOut() {

}

void FirstScene::willExit() {
    
}