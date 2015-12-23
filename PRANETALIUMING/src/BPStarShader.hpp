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
    ofImage positionImg, positionImgL;
    ofFloatImage positionImgFloat;
public:
    vector< BPStar >* stars;
    bool isDrawingMesh, isDrawingShader;

    void setup() {
        string fragmentShaderForStar = GLSL120(uniform float time;
                                               uniform float size;
                                               uniform vec2 resolution;
                                               uniform sampler2DRect positionTexture_S;
                                               uniform sampler2DRect positionTexture_L;
                                               void main( void ) {
                                                   float c;
                                                   vec2 p = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;//-1~+1の座標系
                                                   float s = sin(time * 2.75 + p.x * 10. * p.y);
                                                   float ratio = resolution.x / resolution.y;
                                                   float halfRatio = ratio / 2.;
                                                   for(int i = 0; i < size; i++){
                                                       vec4 o_s = texture2DRect(positionTexture_S, vec2(i + .5, 0.));
                                                       vec4 o_l = texture2DRect(positionTexture_L, vec2(i + .5, 0.));
                                                       vec4 o = vec4(vec2(o_s.xy + o_l.xy) / 2., o_s.z, o_s.w);
                                                       o.x = o.x * ratio - halfRatio;
                                                       o.y = (o.y - 0.5);
                                                       float mag = o.z * 10.;
                                                       c += o_l.w * (10. * o.z * o_s.w + 1) * 0.005 * 5./*mag*/ * (0.5 + 0.1 * s)  / length(p - o.xy);//dot(p - o.xy, p - o.xy);
                                                   }
                                                   gl_FragColor = vec4(c, c, c, c);
                                               });
        starShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForStar);
        starShader.bindDefaults();
        starShader.linkProgram();
        
        positionImgFloat.allocate(200, 1, OF_IMAGE_COLOR_ALPHA);
        positionImg.allocate(200, 1, OF_IMAGE_COLOR_ALPHA);
        positionImgL.allocate(200, 1, OF_IMAGE_COLOR_ALPHA);
    }
    
    void update() {
//        int j = 0;
//        for (auto it = stars->begin(); it != stars->end(); it++ ) {
//            ofColor c_s, c_l;
//            ofVec2f p = it->getPosition();
//            float x_s, x_l, y_s, y_l;
//            float halfW = ofGetWidth() / 2.;
//            float halfH = ofGetHeight() / 2.;
//            if (p.x >= halfW) {
//                x_s = 1.;
//                x_l = (p.x - halfW) / halfW;
//            } else {
//                x_s = p.x / halfW;
//                x_l = 0;
//            }
//            float x = it->getPosition().x / (float)ofGetWidth();
//            float y = it->getPosition().y / (float)ofGetHeight();
//            
//            if (p.y >= halfH) {
//                y_s = 1.;
//                y_l = (p.y - halfH) / halfH;
//            } else {
//                y_s = p.y / halfH;
//                y_l = 0.;
//            }
//            
//            c_s = ofFloatColor(x_s,
//                               y_s,
//                               (it->getMagnitude() + 1) / 10.,
//                               it->isShootingStar);
//            c_l = ofFloatColor(x_l,
//                               y_l,
//                               (it->getMagnitude() + 1) / 10.,
//                               it->isShootingStar);
//            
//            positionImg.setColor(j, 0, c_s);
//            j++;
//        }
//        positionImg.reloadTexture();
        
//        j = 0;
//        for (auto it = stars->begin(); it != stars->end(); it++ ) {
//            ofColor c_s, c_l;
//            ofVec2f p = it->getPosition();
//            float x_s, x_l, y_s, y_l;
//            float halfW = ofGetWidth() / 2.;
//            float halfH = ofGetHeight() / 2.;
//            if (p.x >= halfW) {
//                x_s = 1.;
//                x_l = (p.x - halfW) / halfW;
//            } else {
//                x_s = p.x / halfW;
//                x_l = 0;
//            }
//            float x = it->getPosition().x / (float)ofGetWidth();
//            float y = it->getPosition().y / (float)ofGetHeight();
//            
//            if (p.y >= halfH) {
//                y_s = 1.;
//                y_l = (p.y - halfH) / halfH;
//            } else {
//                y_s = p.y / halfH;
//                y_l = 0.;
//            }
//            
//            c_l = ofFloatColor(x_l,
//                               y_l,
//                               (it->getMagnitude() + 1) / 10.,
//                               it->isShootingStar);
//            
//            positionImgL.setColor(j, 0, c_l);
//            j++;
//        }
//        positionImgL.reloadTexture();
        
//        int j = 0;
//        for (auto it = stars->begin(); it != stars->end(); it++ ) {
//            ofColor c_s, c_l;
//            ofVec2f p = it->getPosition();
//            float x = it->getPosition().x / (float)ofGetWidth();
//            float y = it->getPosition().y / (float)ofGetHeight();
//            c_s = ofFloatColor(x,
//                               y,
//                               (it->getMagnitude() + 1) / 10.,
//                               it->isShootingStar);
//            positionImg.setColor(j, 0, c_s);
//            j++;
//        }
        
        int x = 0;
        unsigned char * pixels_s = positionImg.getPixels();
        unsigned char * pixels_l = positionImgL.getPixels();
 
        int w = positionImg.getWidth();
        int h = positionImg.getHeight();
        for (auto it = stars->begin(); it != stars->end(); it++ ) {
            int i = 0 * w + (x * 4);
            float px = it->getPosition().x / (float)ofGetWidth();
            float py = it->getPosition().y / (float)ofGetHeight();

            ofColor c_s, c_l;
            ofVec2f p = it->getPosition();
            float x_s, x_l, y_s, y_l;
            float halfW = ofGetWidth() / 2.;
            float halfH = ofGetHeight() / 2.;
            if (p.x >= halfW) {
                x_s = 1.;
                x_l = (p.x - halfW) / halfW;
            } else {
                x_s = p.x / halfW;
                x_l = 0;
            }
            if (p.y >= halfH) {
                y_s = 1.;
                y_l = (p.y - halfH) / halfH;
            } else {
                y_s = p.y / halfH;
                y_l = 0.;
            }

            pixels_s[i] = 255 * x_s;
            pixels_s[i + 1] = 255 * y_s;
            pixels_s[i + 2] = 255 * (it->getMagnitude() + 1) / 5.; // magnitude = -1 ~ 4
            pixels_s[i + 3] = 255 * it->isShootingStar;
            
            pixels_l[i] = 255 * x_l;
            pixels_l[i + 1] = 255 * y_l;
            pixels_l[i + 2] = 100;
            pixels_l[i + 3] = 255 * !it->isFinished;
            x++;
        }
        positionImg.update();
        positionImgL.update();
    }
    
    void draw() {
        starShader.begin();
        starShader.setUniform1f("size", stars->size());
        starShader.setUniformTexture("positionTexture_S", positionImg.getTextureReference(), 1);
        starShader.setUniformTexture("positionTexture_L", positionImgL.getTextureReference(), 2);
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

    void reloadShader() {
        starShader.unload();
        string fragmentShaderForStar = GLSL120(uniform float time;
                                               uniform float size;
                                               uniform vec2 resolution;
                                               uniform sampler2DRect positionTexture_S;
                                               uniform sampler2DRect positionTexture_L;
                                               void main( void ) {
                                                   float c;
                                                   vec2 p = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;//-1~+1の座標系
                                                   float s = sin(time * 2.5 + p.x * 10. * p.y);
                                                   float ratio = resolution.x / resolution.y;
                                                   float halfRatio = ratio / 2.;
                                                   for(int i = 0; i < size; i++){
                                                       vec4 o_s = texture2DRect(positionTexture_S, vec2(i + .5, 0.));
                                                       vec4 o_l = texture2DRect(positionTexture_L, vec2(i + .5, 0.));
                                                       vec4 o = vec4(vec2(o_s.xy + o_l.xy) / 2., o_s.z, o_s.w);
                                                       o.x = o.x * ratio - halfRatio;
                                                       o.y = (o.y - 0.5);
                                                       float mag = o.z * 10.;
                                                       c += (1. + 4. * o.w) * 0.001 * mag * (0.9 + 0.1 * s)  / length(p - o.xy);//dot(p - o.xy, p - o.xy);
                                                   }
                                                   gl_FragColor = vec4(c);
                                               });
        starShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForStar);
        starShader.bindDefaults();
        starShader.linkProgram();
    }
    
};