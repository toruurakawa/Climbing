//
//  PLConstellationsSelector.hpp
//  SketchForCliming_StageSelect
//
//  Created by TORU URAKAWA on 11/27/15.
//
//

#ifndef PLConstellationsSelector_hpp
#define PLConstellationsSelector_hpp

#include "ofMain.h"
#include "BPStarShader.hpp"
#include "PLConstellations.hpp"

class PLConstellationsSelector {
    PLConstellations cs;
    int currentIndex;
    int nextIndex;
    BPStarShader starShader;
    bool isChanging;
    float changingTime;

public:
    void setup();
    void update();
    void draw();
    void nextConstellation();
    void prevConstellation();
    
    const string currentConstellationXML();
};

#endif /* PLConstellationsSelector_hpp */
