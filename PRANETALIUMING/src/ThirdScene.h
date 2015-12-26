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
#include "ofxCenteredTrueTypeFont.h"

#include "Constants.h"

class ThirdScene : public ofxScene {
public:
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
    
    void keyReleased(int key);
    
    BPConstellation c;
    BPStarShader starShader;
    
    void success();
    bool isSucceed;
    int succeedTime;
    void fail();
    bool isFailed;
    void skip();
    int failTime;
    int nextShootFrame;
    int shootingStarNum;
    
    void sendEvent();
    
    string str;
    ofxCenteredTrueTypeFont font;
    float dstFontAlpha, fontAlpha;
    ofVec2f dstFontPos, fontPos;
};

#endif /* defined(__example_Simple__ThirdScene__) */
