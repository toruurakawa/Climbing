//
//  BPNode.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/8/15.
//
//

#pragma once
#include "ofMain.h"
#include "BPStar.cpp"

class BPNode {
//    BPStar* startingStar;
//    BPStar* endStar;
//public:
//    // SETTER
//    void setStartingStar(BPStar* _startingStar) {
//        startingStar = _startingStar;
//    }
//    void setEndStar(BPStar* _endStar) {
//        endStar = _endStar;
//    }
//
//    // GETTER
//    BPStar* getStartingStar() {
//        return startingStar;
//    }
//    BPStar* getEndStar() {
//        return endStar;
//    }
//
//    // UPDATE
//    
//    // DRAWING
//    void draw() {
//        ofVec2f s = startingStar->getPosition();
//        ofVec2f e = endStar->getPosition();
//        ofLine(s.x, s.y, e.x, e.y);
//    }

    BPStar startingStar;
    BPStar endStar;
public:
    // SETTER
    void setStartingStar(BPStar _startingStar) {
        startingStar = _startingStar;
    }
    void setEndStar(BPStar _endStar) {
        endStar = _endStar;
    }
    
    // GETTER
    BPStar getStartingStar() {
        return startingStar;
    }
    BPStar getEndStar() {
        return endStar;
    }
    
    // UPDATE
    
    // DRAWING
    void draw() {
        ofVec2f s = startingStar.getPosition();
        ofVec2f e = endStar.getPosition();
        ofLine(s.x, s.y, e.x, e.y);
    }
};
