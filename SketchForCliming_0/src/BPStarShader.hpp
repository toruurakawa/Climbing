//
//  BPStarShader.hpp
//  SketchForCliming_0
//
//  Created by TORU URAKAWA on 10/19/15.
//
//

#pragma once
#include "BPShader.hpp"
class BPStarShader : BPShader {
    ofVboMesh mesh;
    ofShader initPosShader;
    ofFbo posFbo;
    int i, x, y;
    
public:
    void addVertex(ofVec2f v){
        x = i % 20;
        y = i / 20;
        cout << v << endl;
        mesh.addVertex(ofVec2f(v.x, v.y));
        mesh.addTexCoord(ofVec2f(v.x, v.y));
        i++;
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
    }
    
    void setup() {
        vertexShaderString = GLSL120(
                               uniform sampler2DRect positionTexture;
                               void main(){
//                                   gl_Position = ftransform();  // 座標変換するだけ
                                   vec2 st = gl_Vertex.xy;
                                   vec2 texPos = texture2DRect(positionTexture, st).xy;
                                   gl_Position = gl_ModelViewProjectionMatrix * vec4(texPos, 0.0, 1.0);
                                   gl_PointSize = texPos.x / 10.;  // 点の大きさを変更する
                               }
                               );

        fragmentShaderString = GLSL120(
                                       void main()
                                       {
                                           vec3 n;
                                           
                                           n.xy = gl_PointCoord * 2.0 - 1.0;  // 座標値を [0, 1] → [-1, 1] に変換する
                                           float d = dot(n.xy, n.xy);
                                           float r = sqrt(d);
                                           float md = mix(0.3, 0.8, r/0.9);
                                           gl_FragColor = vec4(1., 1., 1.0, 1.0 - pow(r, .05));  // 白色を描くだけ
                                       }
                                       );
        shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShaderString);
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShaderString);
        shader.bindDefaults();
        shader.linkProgram();
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    void draw(int w, int h){
        shader.begin();
        shader.setUniformTexture("positionTexture", posFbo.getTextureReference(), 1);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_POINT_SPRITE);
        mesh.draw();
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_POINT_SPRITE);
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
        shader.end();
        
//        posFbo.draw(0, 0, 100, 100);
    }

};