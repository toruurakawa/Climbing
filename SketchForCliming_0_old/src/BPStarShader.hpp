//
//  BPStarShader.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/19/15.
//
//

#pragma once
#include "BPShader.hpp"
#include "BPStar.hpp"

class BPStarShader : BPShader {
    ofVboMesh mesh;
    ofShader starShader;
    ofImage positionImg;
    
public:
    vector< BPStar >* stars;
    bool isDrawingMesh, isDrawingShader;

    void setup() {
        string fragmentShaderForStar = GLSL120(uniform float time;
                                               uniform vec2 resolution;
                                               uniform sampler2DRect positionTexture;
                                               void main( void ) {
                                                   float c;
                                                   vec2 p = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;//-1~+1の座標系
                                                   float s = sin(time * 2.5 + p.x * 10. * p.y);
                                                   float ratio = resolution.x / resolution.y;
                                                   float halfRatio = ratio / 2.;
                                                   for(int i = 0; i < 100; i++){
                                                       vec4 o = texture2DRect(positionTexture, vec2(i + .5, 0.));
                                                       o.x = o.x * ratio - halfRatio;
                                                       o.y = (o.y - 0.5);
                                                       float mag = o.z * 10.;
                                                       c += (1. + 2. * o.w) * 0.00075 * mag * (0.8 + 0.2 * s)  / length(p - o.xy);//dot(p - o.xy, p - o.xy);
                                                   }
                                                   gl_FragColor = vec4(c);
                                               });
        starShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForStar);
        starShader.bindDefaults();
        starShader.linkProgram();
        
        positionImg.allocate(200, 1, OF_IMAGE_COLOR_ALPHA);
    }
    
    void draw(){
        int j = 0;
        for (auto it = stars->begin(); it != stars->end(); it++ ) {
            ofColor c;
            float x = it->getPosition().x / (float)ofGetWidth();
            float y = it->getPosition().y / (float)ofGetHeight();
            c = ofFloatColor(x,
                             y,
                             (it->getMagnitude() + 1) / 10.,
                             it->isShootingStar);
            positionImg.setColor(j, 0, c);
            j++;
        }
        positionImg.update();
        starShader.begin();
        shader.setUniformTexture("positionTexture", positionImg.getTextureReference(), 1);
        starShader.setUniform1f("time", ofGetElapsedTimef());
        starShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
        ofMesh quad;
        quad.getVertices().resize(4);
        quad.getTexCoords().resize(4);
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        int _width = ofGetWidth(); int _height = ofGetHeight();
        quad.setVertex(0, ofVec3f(0,0,0));
        quad.setVertex(1, ofVec3f(_width,0,0));
        quad.setVertex(2, ofVec3f(_width,_height,0));
        quad.setVertex(3, ofVec3f(0,_height,0));
        quad.setTexCoord(0, ofVec2f(0,0));
        quad.setTexCoord(1, ofVec2f(_width,0));
        quad.setTexCoord(2, ofVec2f(_width,_height));
        quad.setTexCoord(3, ofVec2f(0,_height));
        quad.draw();
        starShader.end();
    }

    
};