//
//  SecondScene.h
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_Simple__SecondScene__
#define __example_Simple__SecondScene__

#include "ofxScene.h"
#include "PLConstellationsSelector.hpp"
#include "ofxTrueTypeFontUC.h"
#include "Constants.h"

class SecondScene : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
    
    void keyReleased(int key);
    
    PLConstellationsSelector cs;
    ofxTrueTypeFontUC font;
};

#endif /* defined(__example_Simple__SecondScene__) */
