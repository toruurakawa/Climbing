//
//  PLConstellations.cpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 11/26/15.
//
//

#include "PLConstellations.hpp"

void PLConstellations::load() {
    currentIndex = 0;
    
    dir.open("Constellations/");
    dir.allowExt("xml");
    dir.listDir();
 
    for(int i = 0; i < dir.size(); i++){
        ofLogNotice(dir.getPath(i));
        
        BPConstellation c;
        c.loadFromXml(dir.getPath(i));
        constellations.push_back(c);
    }
}

void PLConstellations::reloadAtIndex(int i) {
    BPConstellation c;
    c.loadFromXml(dir.getPath(i));
    constellations[i] = c;
}

vector<BPConstellation>* PLConstellations::getConstellations() {
    return &constellations;
}

const int PLConstellations::size() {
    return constellations.size();
}