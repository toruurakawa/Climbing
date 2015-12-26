//
//  ThirdScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "ThirdScene.h"
#include "TitleScene.h"
#include "FirstScene.h"
#include "SecondScene.h"

void ThirdScene::setup(ofPtr<ofxScene> previousScene) {
    SecondScene* scene = dynamic_cast<SecondScene *>(previousScene.get());
    c.clear();
    c.loadFromXml(scene->cs.currentConstellationXML());
    
    c.dstAlpha = 255;
    c.dstDrawingAlpha = 255;
    c.isPlaying = true;
    
    starShader.setup();
    starShader.stars = c.getStars();
    
    isSucceed = false;
    isFailed = false;
    
    font.loadFont("fonts/DINNextLTPro-UltraLight.otf", FONT_CONST_RESULT);
    
    dstFontAlpha = fontAlpha = 0;
    dstFontPos = fontPos = ofVec2f(ofGetWidth() / 2., ofGetHeight() / 2.);
    
    nextShootFrame = 100;
    shootingStarNum = 1;
}

void ThirdScene::update() {
    if (ofGetFrameNum() % nextShootFrame == 0) {
        for (int i = 0; i < shootingStarNum; i++) {
            BPStar star;
            star.setPosition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
            star.isBackgroundStar = true;
            if (isSucceed) {
                star.isShootingStar = false;
                nextShootFrame = (int)ofRandom(1, 2);
                shootingStarNum = (int)ofRandom(1, (ofGetElapsedTimef() - succeedTime) * (ofGetElapsedTimef() - succeedTime)  + 1);
            }
            else if (isFailed) {
                nextShootFrame = (int)ofRandom(5, 10);
                shootingStarNum = (int)ofRandom(10, (ofGetElapsedTimef() - failTime) * (ofGetElapsedTimef() - failTime)  + 10);
                star.isShootingStar = true;
            } else {
                nextShootFrame = (int)ofRandom(10, 1000);
                shootingStarNum = (int)ofRandom(1, 2);
                star.isShootingStar = true;
            }
            if (c.getStars()->size() < 95) {
                c.getStars()->push_back(star);
            }
        }
    }

    starShader.update();
    c.update();
    
    if (isFailed && ofGetElapsedTimef() - failTime > 5.) {
        isFailed = false;
        sendEvent();
    }
    
    if (isSucceed && ofGetElapsedTimef() - succeedTime > 5.) {
        isSucceed = false;
        sendEvent();
    }
    
    fontAlpha += (dstFontAlpha - fontAlpha) / 50.;
    fontPos += (dstFontPos - fontPos) / 50.;
}

void ThirdScene::draw() {
    ofBackground(0);
    starShader.draw();
    c.draw();
    
    ofPushStyle();
    ofSetColor(255, fontAlpha);
    font.drawStringCentered(str, fontPos.x, fontPos.y);
    ofPopStyle();
}

void ThirdScene::fail() {
    c.isShooting = true;
    for (auto it = c.getStars()->begin(); it != c.getStars()->end(); it++) {
        it->shoot();
    }
    isFailed = true;
    c.isPlaying = false;
    nextShootFrame = 1;
    failTime = ofGetElapsedTimef();
    c.dstAlpha = 0;
    c.dstDrawingAlpha = 0;
    
    str = "FALL";
    dstFontAlpha = 255;
    dstFontPos.y = ofGetHeight() / 2. - ofGetHeight() / 10.;
}

void ThirdScene::success() {
    isSucceed = true;
    c.isPlaying = false;
    nextShootFrame = 1;
    succeedTime = ofGetElapsedTimef();
    c.dstAlpha = 255;
    c.dstDrawingAlpha = 255;

    str = "SUCCESS";
    dstFontAlpha = 255;
    dstFontPos.y = ofGetHeight() / 2. - ofGetHeight() / 10.;
}

void ThirdScene::skip() {
    sendEvent();
}

void ThirdScene::sendEvent() {
    int i = 0;
    ofNotifyEvent(notify, i, this);
}

void ThirdScene::keyReleased(int key) {
    switch (key) {
        case 'f':
            fail();
            break;
        case 's':
            success();
            break;
        case '0':
            skip();
            break;
        default:
            break;
    }
}