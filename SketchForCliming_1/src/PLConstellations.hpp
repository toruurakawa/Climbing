//
//  PLConstellations.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 11/26/15.
//
//

#ifndef PLConstellations_hpp
#define PLConstellations_hpp

#include <stdio.h>
#include "ofMain.h"
#include "BPConstellation.hpp"

class PLConstellations {
    ofDirectory dir;
    vector<BPConstellation> constellations;
    int currentIndex;
    string currentXMLFilename;
public:
    void load();
    void reloadAtIndex(int i);
    void update();
    const int size();
    
    vector<BPConstellation>* getConstellations();
    const string getCurrentXMLFilename();
};

#endif /* PLConstellations_hpp */
