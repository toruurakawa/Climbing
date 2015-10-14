#pragma once

#include "ofMain.h"
#include "BPStar.hpp"
#include "BPNode.hpp"
#include "BPSky.cpp"

typedef enum DrawMode {
    Constellation,
    Edge,
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

    vector< vector<ofVec2f> > ptss;
    vector<ofVec2f> pts;
    BPSky sky;
    vector<BPStar> selectedStars;
    vector<BPNode> nodes;
    BPStar* selected;
    bool isFirst;
    DrawMode mode;
};
