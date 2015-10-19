//
//  BPShader.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/19/15.
//
//

#pragma once 
#include "ofMain.h"
#define GLSL120(shader)  "#version 120 \n #extension GL_ARB_texture_rectangle : enable \n" #shader
#define GLSL150(shader)  "#version 150 \n" #shader

class BPShader {
protected:
    ofMesh quad;
    
    ofShader shader;
    string fragmentShaderString;
    string vertexShaderString;
    
public:
    BPShader() {
        vertexShaderString = GLSL120(
                                     void main() {
                                         gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                                         gl_FrontColor = gl_Color;
                                     }
                                     );
        
        fragmentShaderString = GLSL120(
                                       void main()
                                       {
                                           gl_FragColor = vec4(0.0,1.0,0.0,1.0);
                                       }
                                       );
        
        quad.getVertices().resize(4);
        quad.getTexCoords().resize(4);
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    }
    
    ~BPShader() {shader.unload();};
    
protected:
    
    void renderFrame(float _width, float _height){
        quad.setVertex(0, ofVec3f(0,0,0));
        quad.setVertex(1, ofVec3f(_width,0,0));
        quad.setVertex(2, ofVec3f(_width,_height,0));
        quad.setVertex(3, ofVec3f(0,_height,0));
        
        quad.setTexCoord(0, ofVec2f(0,0));
        quad.setTexCoord(1, ofVec2f(_width,0));
        quad.setTexCoord(2, ofVec2f(_width,_height));
        quad.setTexCoord(3, ofVec2f(0,_height));
        
        quad.draw();
    }
    
    void renderNormalizedFrame(float _width, float _height){
        quad.setVertex(0, ofVec3f(0,0,0));
        quad.setVertex(1, ofVec3f(_width,0,0));
        quad.setVertex(2, ofVec3f(_width,_height,0));
        quad.setVertex(3, ofVec3f(0,_height,0));
        
        quad.setTexCoord(0, ofVec2f(0,0));
        quad.setTexCoord(1, ofVec2f(1,0));
        quad.setTexCoord(2, ofVec2f(1,1));
        quad.setTexCoord(3, ofVec2f(0,1));
        
        quad.draw();
    }

};