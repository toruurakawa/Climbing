#pragma once

#include "ofMain.h"
#include "BPStar.hpp"
#include "BPNode.hpp"
#include "BPSky.cpp"
#include "BPDrawing.hpp"
#include "BPConstellation.hpp"
#include "ofxQuadWarp.h"
#include "PLConstellationsSelector.hpp"
typedef enum DrawMode {
    Constellation,
    Edge,
    Star,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
} DrawMode;

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    BPSky sky;
    ofxQuadWarp warper;
    
    PLConstellationsSelector c;
};
