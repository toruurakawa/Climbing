//
//  PLConstellations.cpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 11/26/15.
//
//

#include "PLConstellations.hpp"

void PLConstellations::load() {
    ofDirectory dir("Constellations/");
    dir.allowExt("xml");
    dir.listDir();
 
    //go through and print out all the paths
    for(int i = 0; i < dir.size(); i++){
        ofLogNotice(dir.getPath(i));
        
        BPConstellation c;
        c.loadFromXml(dir.getPath(i));
        constellations.push_back(c);
    }
}