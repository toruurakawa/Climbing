//
//  TitleScene.h
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_Simple__TitleScene__
#define __example_Simple__TitleScene__

#include "ofxScene.h"
#include "BPStarShader.hpp"
#include "BPConstellation.hpp"

class TitleScene : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
    
    BPConstellation c;
};

#endif /* defined(__example_Simple__TitleScene__) */
