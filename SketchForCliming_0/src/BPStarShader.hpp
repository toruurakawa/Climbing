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
    ofShader initPosShader;
    ofFbo posFbo;
    ofShader magnitudeShader;
    ofImage magnitudeImg;
    vector< BPStar >stars;
    int i, x, y;
    
public:
    void addVertex(ofVec2f v) {
        x = i % 20;
        y = i / 20;
        cout << v << endl;
        mesh.addVertex(ofVec2f(v.x, v.y));
        mesh.addTexCoord(ofVec2f(v.x, v.y));
        i++;
    }
    
    void addStar(BPStar s) {
        stars.push_back(s);
        addVertex(s.getPosition());
    }
    
    void setInitialPos() {
        string fragmentShaderForInit = GLSL120(
                                               void main() {
                                                   vec2 st = gl_TexCoord[0].st;
                                                   gl_FragColor = vec4(st, 0.0, 1.0);
                                               }
                                               );
        initPosShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderForInit);
        initPosShader.bindDefaults();
        initPosShader.linkProgram();
        
        ofMesh quad;
        quad.getVertices().resize(4);
        quad.getTexCoords().resize(4);
        quad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

        int _width = ofGetWidth(); int _height = ofGetHeight();
        
        ofFbo::Settings mySettings;
        mySettings.width = _width;
        mySettings.height = _height;
        mySettings.internalformat = GL_RGBA32F;
        mySettings.maxFilter = GL_NEAREST;
        mySettings.minFilter = GL_NEAREST;
        posFbo.allocate(mySettings);
        posFbo.begin();
        initPosShader.begin();
        quad.setVertex(0, ofVec3f(0,0,0));
        quad.setVertex(1, ofVec3f(_width,0,0));
        quad.setVertex(2, ofVec3f(_width,_height,0));
        quad.setVertex(3, ofVec3f(0,_height,0));
        
        quad.setTexCoord(0, ofVec2f(0,0));
        quad.setTexCoord(1, ofVec2f(_width,0));
        quad.setTexCoord(2, ofVec2f(_width,_height));
        quad.setTexCoord(3, ofVec2f(0,_height));
        
        quad.draw();
        shader.end();
        posFbo.end();
        
        // maginitude
        magnitudeImg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
        int i = 0;
        for (auto it = stars.begin(); it != stars.end(); it++ ) {
            i++;
            ofColor c = ofColor(it->getMagnitude() / 5. * 255);
            magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
        }
        magnitudeImg.update();

    }
    
    void setup() {
        vertexShaderString = GLSL120(
                                       uniform sampler2DRect positionTexture;
                                       uniform sampler2DRect magnitudeTexture;
                                       void main(){
//                                           gl_Position = ftransform();  // 座標変換するだけ
                                           vec2 st = gl_Vertex.xy;
                                           vec2 texPos = texture2DRect(positionTexture, st).xy;
                                           vec2 magnitude = texture2DRect(magnitudeTexture, st).xy;
                                           gl_Position = gl_ModelViewProjectionMatrix * vec4(texPos, 0.0, 1.0);
                                           gl_PointSize = magnitude.r * 200;  // 点の大きさを変更する
                                       }
                                       );

        fragmentShaderString = GLSL120(
                                       void main()
                                       {
                                           vec3 n;
                                           n.xy = gl_PointCoord * 2.0 - 1.0;  // 座標値を [0, 1] → [-1, 1] に変換する
                                           float d = dot(n.xy, n.xy);
                                           float r = sqrt(d);
                                           gl_FragColor = vec4(1., 1., 1., 1. - pow(r, .35));  // 白色を描くだけ
                                       }
                                       );
        shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderString);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderString);
        shader.bindDefaults();
        shader.linkProgram();
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        
    }
    
    void draw(int w, int h){
        int i = 0;
        for (auto it = stars.begin(); it != stars.end(); it++ ) {
            i++;
            if (i == 100) {
                ofColor c = ofColor((1 + sin(ofGetElapsedTimef())) / 2.* 100  / 5. * 255);
                magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
            } else {
                ofColor c = ofColor(ofNoise(ofGetElapsedTimef() / 5., it->getPosition().x, it->getPosition().y) * it->getMagnitude() / 5. * 255);
                magnitudeImg.setColor(it->getPosition().x, it->getPosition().y, c);
            }
        }
        magnitudeImg.update();

        shader.begin();
        shader.setUniformTexture("positionTexture", posFbo.getTextureReference(), 1);
        shader.setUniformTexture("magnitudeTexture", magnitudeImg.getTextureReference(), 2);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_POINT_SPRITE);
        mesh.draw();
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
        shader.end();
        
//        magnitudeImg.draw(0, 0);
    }

};