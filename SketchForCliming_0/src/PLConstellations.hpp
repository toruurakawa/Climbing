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
    vector<BPConstellation> constellations;
    
public:
    void load();
    
};

#endif /* PLConstellations_hpp */
