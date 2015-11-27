//
//  PLConstellationsSelector.cpp
//  SketchForCliming_StageSelect
//
//  Created by TORU URAKAWA on 11/27/15.
//
//

#include "PLConstellationsSelector.hpp"

//--------------------------------------------------------------
void PLConstellationsSelector::setup() {
    starShader.setup();
    nextIndex = currentIndex = 0;    
    cs.load();
    starShader.stars = (*cs.getConstellations())[currentIndex].getStars();
    
    changingTime = ofGetElapsedTimef();
    isChanging = false;
}

//--------------------------------------------------------------
void PLConstellationsSelector::update() {
    (*cs.getConstellations())[currentIndex].update();
    starShader.update();
    
    if (isChanging && ofGetElapsedTimef() - changingTime > .75) {
        currentIndex = nextIndex;
        isChanging = false;
        cs.reloadAtIndex(currentIndex);
        starShader.setup();
        starShader.stars = (*cs.getConstellations())[currentIndex].getStars();
    }

}

//--------------------------------------------------------------
void PLConstellationsSelector::draw() {
    // Stars
    starShader.draw();    
    // Constellations
    (*cs.getConstellations())[currentIndex].draw();

}

//--------------------------------------------------------------
void PLConstellationsSelector::nextConstellation() {
    nextIndex = (currentIndex + 1) % cs.size();
    if ((*cs.getConstellations()).size()) {
        (*cs.getConstellations())[currentIndex].isShooting = true;
        for (auto it = (*cs.getConstellations())[currentIndex].getStars()->begin();
             it != (*cs.getConstellations())[currentIndex].getStars()->end(); it++) {
            it->shoot();
        }
        isChanging = true;
        changingTime = ofGetElapsedTimef();
    }
}

//--------------------------------------------------------------
void PLConstellationsSelector::prevConstellation() {
    nextIndex = (currentIndex - 1);
    if (nextIndex < 0) {
        nextIndex = cs.size() - 1;
    }
    if ((*cs.getConstellations()).size()) {
        (*cs.getConstellations())[currentIndex].isShooting = true;
        for (auto it = (*cs.getConstellations())[currentIndex].getStars()->begin();
             it != (*cs.getConstellations())[currentIndex].getStars()->end(); it++) {
            it->shoot();
        }
        isChanging = true;
        changingTime = ofGetElapsedTimef();
    }
}
