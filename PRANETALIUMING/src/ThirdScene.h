//
//  ThirdScene.h
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_Simple__ThirdScene__
#define __example_Simple__ThirdScene__

#include "ofxScene.h"
#include "BPStarShader.hpp"
#include "BPConstellation.hpp"

class ThirdScene : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
    
    BPConstellation c;
    BPStarShader starShader;
};

#endif /* defined(__example_Simple__ThirdScene__) */
